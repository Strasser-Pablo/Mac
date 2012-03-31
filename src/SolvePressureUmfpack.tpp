/**
 * @file SolvePressureUmfpack.tpp
 * @brief
 * Implementation file for class SolvePressureUmfpack.
 **/

template<class TypeWorld,class TypeGetCellType>
SolvePressureUmfpack<TypeWorld,TypeGetCellType>::SolvePressureUmfpack(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h,TypeGetCellType &GetCellType):m_world(world),m_1_h(_1_h),m_key_to_num(m_o),m_GetCellType(GetCellType)
,m_stat_out("umfpack_div.txt",fstream::out){
	
}


template<class TypeWorld,class TypeGetCellType>
void SolvePressureUmfpack<TypeWorld,TypeGetCellType>::Calculate()
{
	int n=m_world.m_mac_grid.size();
	// Because it's a laplacian with 2*dim for of diagonal entry and 1 diagonal entry.
	int nEntry=(2*type_dim+1)*n;
	m_offset=new int[n+1];
	m_indice=new int[nEntry];
	m_val=new type_data[nEntry];
	m_b=new type_data[n];
	//Current index of numbered cell.
	m_iid=0;
	int inumb=0;
	//First ofset need by definition always be 0.
	m_offset[0]=0;
	int m_iid0=0;
	m_key_to_num.clear();
	m_num_to_key.clear();
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		if(m_GetCellType.GetIsFluid(it.key())||m_GetCellType.GetIsBoundaryAir(it.key()))
			{
						for(int i2=m_iid0;i2<m_iid;++i2)
						{
							CalculateB(i2,m_num_to_key[i2]);
							CalculateAColumn(i2,inumb,m_num_to_key[i2]);
						}
						m_iid0=m_iid;
				//Key don't exist, give a number.
				if(!m_key_to_num.Exist(it.key()))
					{
						m_key_to_num[it.key()]=m_iid;
						m_num_to_key[m_iid]=it.key();
						m_iid0=m_iid;
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
	type_data max=0;
	for(typename type_to_key::iterator it= m_key_to_num.begin();it!=m_key_to_num.end();++it)
	{
		type_data temp=abs(CalculateDivergence(it.key()));
		if(temp>max)
		{
			max=temp;
		}
	}
	m_stat_out<<"max div "<<max<<endl;
	}
	else
	{
		cout<<"zero size linear system to solve"<<endl; 
	}
	delete[] m_offset;
	delete[] m_p;
	delete[] m_indice;
	delete[] m_val;
	delete[] m_b;
}


template<class TypeWorld,class TypeGetCellType>
void SolvePressureUmfpack<TypeWorld,TypeGetCellType>::SetSpeed()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_data p;
		Physvector<type_dim,type_data> speed;
		Physvector<type_dim,int>ktemp=it.key();
		it.data().GetSpeed(speed);
		for(int i=1;i<=type_dim;++i)
		{
			type_data _1_rho=m_GetCellType.Get1_RhoInter(it.key(),i);
			it.data().GetPressure(p);
			ktemp.GetRef(i)-=1;
			if(m_world.m_mac_grid.Exist(ktemp))
			{
			speed.GetRef(i)-=p*m_1_h.Get(i)*_1_rho;
			m_world.m_mac_grid[ktemp].GetPressure(p);
			speed.GetRef(i)+=p*m_1_h.Get(i)*_1_rho;
			}
			ktemp.GetRef(i)+=1;
		}
		it.data().SetSpeed(speed);
	}
}

template<class TypeWorld,class TypeGetCellType>
void SolvePressureUmfpack<TypeWorld,TypeGetCellType>::CalculateB(int iline,Physvector<type_dim,int> key)
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
		bool b1;
		m_world.m_mac_grid[key].GetConstSpeed(i,b1);
		key.GetRef(i)+=1;
		bool b2;
		m_world.m_mac_grid[key].GetConstSpeed(i,b2);
		m_world.m_mac_grid[key].GetSpeed(temp);
		if(m_GetCellType.GetIsAirOnly(key)&&!b2)
		{
		type_data p;
		m_world.m_mac_grid[key].GetPressure(p);
		ret-=p*m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,i);
		}
		ret+=temp.Get(i)*m_1_h.Get(i);
		key.GetRef(i)-=2;
		if(m_GetCellType.GetIsAirOnly(key)&&!b1)
		{
		type_data p;
		m_world.m_mac_grid[key].GetPressure(p);
		ret-=p*m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,i,1);
		}
		key.GetRef(i)+=1;
	}
	m_b[iline]=ret;
}

template<class TypeWorld,class TypeGetCellType>
void SolvePressureUmfpack<TypeWorld,TypeGetCellType>::CalculateAColumn(int icol,int& inumb,Physvector<type_dim,int> key)
{
	int inumb0=inumb;
	++inumb;
	int nboffset=1;
	double diagval=0;
	for(int i=1;i<=type_dim;++i)
	{
		bool b;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		// Look cell below (or left).
		key.GetRef(i)-=1;
		// Only fluid cell and boundary air are in key to num. No test needed.
		// But a const speed can be between two fluid cell.
		// In this case make the two cell disjoint.
		if(!b)
		{
			diagval-=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
		}
		if(m_key_to_num.Exist(key)&&!b)
		{
			m_indice[inumb]=m_key_to_num[key];
			m_val[inumb]=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
			++inumb;
			++nboffset;
		}
		else
		{
			if((m_GetCellType.GetIsFluid(key)||m_GetCellType.GetIsBoundaryAir(key))&&!b)
			{
				m_key_to_num[key]=m_iid;
				m_num_to_key[m_iid]=key;
				m_indice[inumb]=m_iid;
				m_val[inumb]=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
				++m_iid;
				++inumb;
				++nboffset;
			}
		}
		// Look cell above or right.
		key.GetRef(i)+=2;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		if(!b)
		{
			diagval-=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
		}
		if(m_key_to_num.Exist(key)&&!b)
		{
			m_indice[inumb]=m_key_to_num[key];
			m_val[inumb]=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
			++inumb;
			++nboffset;
		}
		else
		{
			if((m_GetCellType.GetIsFluid(key)||m_GetCellType.GetIsBoundaryAir(key))&&!b)
			{
				m_key_to_num[key]=m_iid;
				m_num_to_key[m_iid]=key;
				m_indice[inumb]=m_iid;
				m_val[inumb]=m_1_h.Get(i)*m_1_h.Get(i)*m_GetCellType.Get1_RhoInter(key,m_num_to_key[icol]);
				++m_iid;
				++inumb;
				++nboffset;
			}
		}
		// restore key.
		key.GetRef(i)-=1;
	}
	m_indice[inumb0]=icol;
	m_val[inumb0]=diagval;
	m_offset[icol+1]=m_offset[icol]+nboffset;
	//order value and indice from minimun to maximun
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


template<class TypeWorld,class TypeGetCellType>
typename SolvePressureUmfpack<TypeWorld,TypeGetCellType>::type_data SolvePressureUmfpack<TypeWorld,TypeGetCellType>::CalculateDivergence( Physvector<type_dim,int> key )
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
		key.GetRef(i)-=1;
		ret+=temp.Get(i)*m_1_h.Get(i);
	}
	return ret;
}

template<class TypeWorld,class TypeGetCellType>
typename SolvePressureUmfpack<TypeWorld,TypeGetCellType>::type_data SolvePressureUmfpack<TypeWorld,TypeGetCellType>::CalculateLaplacienInCell( Physvector<type_dim,int> key )
{
	type_data res=0;
	Physvector<type_dim,int> key0=key;
	type_data _1_rho;
	type_data p0;
	m_world.m_mac_grid[key].GetPressure(p0);
	for(int i=1;i<=type_dim;++i)
	{ 
		key.GetRef(i)+=1;
		type_data temp;
		bool b;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		if(!b)
		{
		m_world.m_mac_grid[key].GetPressure(temp);
		_1_rho=m_GetCellType.Get1_RhoInter(key0,key);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i)*_1_rho;
		res-=p0*m_1_h.Get(i)*m_1_h.Get(i)*_1_rho;
		}
		key.GetRef(i)-=1;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		key.GetRef(i)-=1;
		if(!b)
		{
		m_world.m_mac_grid[key].GetPressure(temp);
		_1_rho=m_GetCellType.Get1_RhoInter(key0,key);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i)*_1_rho;
		res-=p0*m_1_h.Get(i)*m_1_h.Get(i)*_1_rho;
		}
		key.GetRef(i)+=1;
	}
	return res;
}
