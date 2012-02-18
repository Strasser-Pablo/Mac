/**
 * @file SolvePressureUmfpack.tpp
 * @brief
 * Implementation file for class SolvePressureUmfpack.
 **/

template<class TypeWorld>
SolvePressureUmfpack<TypeWorld>::SolvePressureUmfpack(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h,const type_cell& fluid):m_world(world),m_fluid(fluid),m_1_h(_1_h),m_key_to_num(m_o)
{
	
}


template<class TypeWorld>
void SolvePressureUmfpack<TypeWorld>::Calculate()
{
	int n=m_world.m_mac_grid.size();
	int nEntry=(2*type_dim+1)*n;
	m_offset=new int[n+1];
	m_indice=new int[nEntry];
	m_val=new type_data[nEntry];
	m_b=new type_data[n];
	    m_iid=0;
	int inumb=0;
	m_offset[0]=0;
	int m_iid0=0;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		bool b;
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid)
			{
				if(m_key_to_num.Exist(it.key()))
					{
						for(int i2=m_iid0;i2<m_iid;++i2)
						{
							CalculateB(i2,m_num_to_key[i2]);
							CalculateAColumn(i2,inumb,m_num_to_key[i2]);
						}
						m_iid0=m_iid;
					}
				else
					{
						m_key_to_num[it.key()]=m_iid;
						m_num_to_key[m_iid]=it.key();
						++m_iid;
						CalculateB(m_iid0,it.key());
						CalculateAColumn(m_iid0,inumb,it.key());
						++m_iid0;
					}
			}

	}
	n=m_iid;
	m_p=new type_data[n];
	if(n>0)
	{
	type_data *null = (type_data *) NULL ;
    void *Symbolic, *Numeric ;
	
    (void) umfpack_di_symbolic (n, n, m_offset, m_indice, m_val, &Symbolic, null, null) ;
    (void) umfpack_di_numeric (m_offset,m_indice,m_val, Symbolic, &Numeric, null, null) ;
    umfpack_di_free_symbolic (&Symbolic) ;
    (void) umfpack_di_solve (UMFPACK_A,m_offset, m_indice,m_val,m_p,m_b, Numeric, null, null) ;
    umfpack_di_free_numeric (&Numeric) ;
	
	for(typename type_to_key::iterator it= m_key_to_num.begin();it!=m_key_to_num.end();++it)
	{
		m_world.m_mac_grid[it.key()].SetPressure(m_p[it.data()]);
	}
	SetSpeed();
	}
	delete[] m_offset;
	delete[] m_p;
	delete[] m_indice;
	delete[] m_val;
	delete[] m_b;
}


template<class TypeWorld>
void SolvePressureUmfpack<TypeWorld>::SetSpeed()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_data p;
		Physvector<type_dim,type_data> speed;
		Physvector<type_dim,int>ktemp=it.key();
		it.data().GetSpeed(speed);
		for(int i=1;i<=type_dim;++i)
		{
			it.data().GetPressure(p);
			ktemp.GetRef(i)-=1;
			if(m_world.m_mac_grid.Exist(ktemp))
			{
			speed.GetRef(i)-=p*m_1_h.Get(i);
			m_world.m_mac_grid[ktemp].GetPressure(p);
			speed.GetRef(i)+=p*m_1_h.Get(i);
			}
			ktemp.GetRef(i)+=1;
		}
		it.data().SetSpeed(speed);
	}
}

template<class TypeWorld>
void SolvePressureUmfpack<TypeWorld>::CalculateB(int iline,Physvector<type_dim,int> key)
{
	type_data ret=0;
	for(int i=1;i<=type_dim;++i)
	{
		Physvector<type_dim,type_data> temp;
		m_world.m_mac_grid[key].GetSpeed(temp);
		ret-=temp.Get(i)*m_1_h.Get(i);
	}
	for(int i=1;i<=type_dim;++i)
	{
		Physvector<type_dim,type_data> temp;
		key.GetRef(i)+=1;
		m_world.m_mac_grid[key].GetSpeed(temp);
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		if(c!=m_fluid)
		{
		type_data p;
		m_world.m_mac_grid[key].GetPressure(p);
		ret-=p*m_1_h.Get(i);
		}
		key.GetRef(i)-=1;
		ret+=temp.Get(i)*m_1_h.Get(i);
	}
	m_b[iline]=ret;
}

template<class TypeWorld>
void SolvePressureUmfpack<TypeWorld>::CalculateAColumn(int icol,int& inumb,	Physvector<type_dim,int> key)
{
	int inumb0=inumb;
	++inumb;
	int nboffset=1;
	double diagval=0;
	int n=0;
	for(int i=1;i<=type_dim;++i)
	{
		bool b;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		key.GetRef(i)-=1;
		if(m_key_to_num.Exist(key))
		{
			m_indice[inumb]=m_key_to_num[key];
			m_val[inumb]=m_1_h.Get(i);
			diagval-=m_1_h.Get(i);
			++inumb;
			++nboffset;
		}
		else
		{
			type_cell c;
			m_world.m_mac_grid[key].GetCellType(c);
			if(!b)
			{
				diagval-=m_1_h.Get(i);
			}
			if(c==m_fluid)
			{
				m_key_to_num[key]=m_iid;
				m_num_to_key[m_iid]=key;
				m_indice[inumb]=m_iid;
				m_val[inumb]=m_1_h.Get(i);
				++m_iid;
				++inumb;
				++nboffset;
			}
		}
		key.GetRef(i)+=2;
		if(m_key_to_num.Exist(key))
		{
			m_indice[inumb]=m_key_to_num[key];
			m_val[inumb]=m_1_h.Get(i);
			diagval-=m_1_h.Get(i);
			++inumb;
			++nboffset;
		}
		else
		{
			m_world.m_mac_grid[key].GetConstSpeed(i,b);
			if(!b)
			{
				diagval-=m_1_h.Get(i);
			}
			type_cell c;
			m_world.m_mac_grid[key].GetCellType(c);
			if(c==m_fluid)
			{
				m_key_to_num[key]=m_iid;
				m_num_to_key[m_iid]=key;
				m_indice[inumb]=m_iid;
				m_val[inumb]=m_1_h.Get(i);
				++m_iid;
				++inumb;
				++nboffset;
			}
		}
		key.GetRef(i)-=1;
	}
	m_indice[inumb0]=icol;
	m_val[inumb0]=diagval;
	m_offset[icol+1]=m_offset[icol]+nboffset;
	bool b=true;
	while(b)
	{
		b=false;
		for(int i=inumb0;i<inumb-1;++i)
		{
			if(m_indice[i]>m_indice[i+1])
			{
				int temp=m_indice[i];
				m_indice[i]=m_indice[i+1];
				m_indice[i+1]=temp;
				double dtemp=m_val[i];
				m_val[i]=m_val[i+1];
				m_val[i+1]=dtemp;
				b=true;
			}
		}
	}
}
