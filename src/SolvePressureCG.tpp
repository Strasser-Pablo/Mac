/**
 * @file SolvePressureCG.tpp
 * @brief
 * Implementation file for class SolvePressureCG.
 **/

template<class TypeWorld,class TypeGetCellType>
SolvePressureCG<TypeWorld,TypeGetCellType>::SolvePressureCG(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h,TypeGetCellType & GetCellType):m_world(world),m_r(m_o),m_p(m_o),m_1_h(_1_h),m_vois(m_o),m_GetCellType(GetCellType)
,m_stat_out("cg_stat.csv", fstream::out)
{
	
}


template<class TypeWorld,class TypeGetCellType>
void SolvePressureCG<TypeWorld,TypeGetCellType>::Calculate()
{
	m_r.clear();
	m_vois.clear();
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(m_GetCellType.GetIsFluid(type)){
		m_r[it.key()]=CalculateDivergence(it.key());
		m_r[it.key()]-=CalculateLaplacienInCell(it.key());
		}
	}
	m_p=m_r;
	m_stat_out<<"beg "<<m_p.size()<<endl;
	type_data rsquarebef=numeric_limits<type_data>::max();
	while(true)
	{
	type_data num=CalculateSquare();
	type_data denom=CalculateAScalar();
	m_stat_out<<"num "<<num<<" denom "<<denom;
	type_data alpha=num/denom;
	if(std::isnan(alpha)||std::isinf(alpha))
	{
		SetSpeed();
		m_stat_out<<endl;
		return;
	}
	m_stat_out<<" alpha "<<alpha;
	for(typename temp_map::iterator it= m_p.begin();it!=m_p.end();++it)
	{
		type_data p;
		m_world.m_mac_grid[it.key()].GetPressure(p);
		p+=alpha*m_p[it.key()];
		m_world.m_mac_grid[it.key()].SetPressure(p);
	}
	for(typename temp_map::iterator it=m_r.begin();it!=m_r.end();++it)
	{

		it.data()-=alpha*CalculateLaplacien(it.key());
	}
	type_data rsquare=CalculateSquare();
	m_stat_out<<" r2 "<<rsquare;
	type_data beta=rsquare/num;
	m_stat_out<<" beta "<<beta<<endl;
	
	if(rsquarebef<rsquare||std::isnan(beta)||rsquare==0)
	{
		SetSpeed();
		m_stat_out<<endl;
		return;
	}
	rsquarebef=rsquare;
	for(typename temp_map::iterator it=m_p.begin();it!=m_p.end();++it)
	{
		it.data()=m_r[it.key()]+beta*m_p[it.key()];
	}
	}
}

template<class TypeWorld,class TypeGetCellType>
typename SolvePressureCG<TypeWorld,TypeGetCellType>::type_data SolvePressureCG<TypeWorld,TypeGetCellType>::CalculateDivergence( Physvector<type_dim,int> key )
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
typename SolvePressureCG<TypeWorld,TypeGetCellType>::type_data SolvePressureCG<TypeWorld,TypeGetCellType>::CalculateLaplacien( Physvector<type_dim,int> key )
{
	type_data res=0;
	for(int i=1;i<=type_dim;++i)
	{ 
		key.GetRef(i)+=1;
		
		if(m_p.Exist(key))
		{
		res+=m_p[key]*m_1_h.Get(i)*m_1_h.Get(i);
		}
		key.GetRef(i)-=2;
		
		if(m_p.Exist(key))
		{
		res+=m_p[key]*m_1_h.Get(i)*m_1_h.Get(i);
		}
		key.GetRef(i)+=1;
		res-=m_vois[key].Get(i)*m_p[key]*m_1_h.Get(i)*m_1_h.Get(i);
	}
	return res;
}

template<class TypeWorld,class TypeGetCellType>
typename SolvePressureCG<TypeWorld,TypeGetCellType>::type_data SolvePressureCG<TypeWorld,TypeGetCellType>::CalculateLaplacienInCell( Physvector<type_dim,int> key )
{
	type_data res=0;
	for(int i=1;i<=type_dim;++i)
	{ 
		key.GetRef(i)+=1;
		type_data temp;
		bool b;
		int n=0;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		if(!b)
		{
		m_world.m_mac_grid[key].GetPressure(temp);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i);
		++n;
		}
		key.GetRef(i)-=1;
		m_world.m_mac_grid[key].GetConstSpeed(i,b);
		key.GetRef(i)-=1;
		if(!b)
		{
		m_world.m_mac_grid[key].GetPressure(temp);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i);
		++n;
		}
		key.GetRef(i)+=1;
		m_world.m_mac_grid[key].GetPressure(temp);
		res-=n*temp*m_1_h.Get(i)*m_1_h.Get(i);
		m_vois[key].Set(i,n);
	}
	return res;
}

template<class TypeWorld,class TypeGetCellType>
typename SolvePressureCG<TypeWorld,TypeGetCellType>::type_data SolvePressureCG<TypeWorld,TypeGetCellType>::CalculateSquare()
{
	type_data res=0;
	for(typename temp_map::iterator it=m_r.begin();it!=m_r.end();++it)
	{
		res+=it.data()*it.data();
	}
	return res;
}


template<class TypeWorld,class TypeGetCellType>
typename SolvePressureCG<TypeWorld,TypeGetCellType>::type_data SolvePressureCG<TypeWorld,TypeGetCellType>::CalculateAScalar()
{
	type_data res=0;
	for(typename temp_map::iterator it=m_p.begin();it!=m_p.end();++it)
	{
		res+=it.data()*CalculateLaplacien(it.key());
	}
	return res;
}

template<class TypeWorld,class TypeGetCellType>
void SolvePressureCG<TypeWorld,TypeGetCellType>::SetSpeed()
{
	m_stat_out<<"end"<<endl;
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
