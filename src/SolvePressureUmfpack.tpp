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
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		bool b;
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid)
			{
				int tempiid=m_iid;
				if(m_key_to_num.Exist(it.key()))
					{
						tempiid=m_key_to_num[it.key()];
					}
				else
					{
						m_key_to_num[it.key()]=m_iid;
						++m_iid;
					}
				CalculateB(tempiid,it.key());
				CalculateAColumn(tempiid,inumb,it.key());
			}

	}
	n=m_iid;
	m_p=new type_data[n];
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
				m_indice[inumb]=m_iid;
				m_val[inumb]=m_1_h.Get(i);
				diagval-=m_1_h.Get(i);
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
<<<<<<< HEAD
}
=======
}
>>>>>>> d8a6f0c498515a62d6953aa610d1ca77fa526fc0
