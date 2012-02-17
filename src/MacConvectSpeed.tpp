/**
 * @file MacConvectSpeed.tpp
 * @brief
 * Implementation file for class MacConvectSpeed and MacConvectSpeedFunctor.
 **/


template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::MacConvectSpeed(TypeWorld & world,TypeMethod &method,TypeGetSpeed & GetSpeed,TypeGetStagSpeedPos &GetStagPos,type_data &dt,const type_cell & fluid,NeighborsVelocity<type_dim,int> & NV):m_world(world),m_ode(m_speed,m_functor,0,method),m_stag_pos(GetStagPos),m_dt(dt),m_functor(GetSpeed),m_GetSpeed(GetSpeed),m_fluid(fluid),m_NV(NV)
{
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout)
{
	for(int i=1;i<=type_dim;++i){
	m_speed=m_stag_pos.Get(key,i);
	m_ode.Calculate(m_dt);
	vout.Set(i,m_GetSpeed.Get(m_speed).Get(i));
	}
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout,int comp)
{
	m_speed=m_stag_pos.Get(key,comp);
	m_ode.Calculate(m_dt);
	m_world.m_mac_grid[key].GetSpeed(vout);
	vout.Set(comp,m_GetSpeed.Get(m_speed).Get(comp));
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::Calculate()
{
			
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid){
		Physvector<type_dim,type_data> temp;
		TracePart(it.key(),temp);
		it.data().SetTempSpeed(temp);
		}
		else{
			Physvector<type_dim,int> temp;
			Physvector<type_dim,int> v;
			for(int i=1;i<=type_dim;++i)
			{
			if(m_NV.Get(i,temp))
			{
			v=it.key()-temp;
			if(m_world.m_mac_grid.Exist(v))
				{
				m_world.m_mac_grid[v].GetCellType(type);
				if(type==m_fluid)
				{
					Physvector<type_dim,type_data> temp2;
					TracePart(it.key(),temp2,i);
					it.data().SetTempSpeed(temp2);
				}
				}
			}
			}
			}
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid)
			{
		it.data().TempToSpeed();
		}
		else{
			Physvector<type_dim,int> temp;
			Physvector<type_dim,int> v;
			for(int i=1;i<=type_dim;++i)
			{
			if(m_NV.Get(i,temp))
			{
			v=it.key()-temp;
			if(m_world.m_mac_grid.Exist(v))
				{
				m_world.m_mac_grid[v].GetCellType(type);
				if(type==m_fluid)
				{
					it.data().TempToSpeed();
				}
				}
			}
			}
			}
	}
	
}


template <class TypeWorld,class TypeGetSpeed>
MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed>::MacConvectSpeedFunctor(TypeGetSpeed &GetSpeed):m_GetSpeed(GetSpeed)
{
}

template <class TypeWorld,class TypeGetSpeed>
Physvector<MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed>::type_dim,typename MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed>::type_data> MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed>::operator()(const Physvector<type_dim,type_data>& pos)
{
	return m_GetSpeed.Get(pos);
}
