/**
 * @file MacConvectSpeed.tpp
 * @brief
 * Implementation file for class MacConvectSpeed and MacConvectSpeedFunctor.
 **/


template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::MacConvectSpeed(TypeWorld & world,TypeMethod &method,TypeGetSpeed & GetSpeed,TypeGetStagSpeedPos &GetStagPos,type_data &dt,GetTypeCell& getTypeCell):m_world(world),m_ode(m_speed,m_functor,0,method),m_stag_pos(GetStagPos),m_dt(dt),m_functor(GetSpeed),m_GetSpeed(GetSpeed),m_GetTypeCell(getTypeCell)
{
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout)
{
	for(int i=1;i<=type_dim;++i){
	m_speed=m_stag_pos.Get(key,i);
	m_ode.Calculate(m_dt);
	vout.Set(i,m_GetSpeed.Get(m_speed).Get(i));
	}
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout,int comp)
{
	m_speed=m_stag_pos.Get(key,comp);
	m_ode.Calculate(m_dt);
	m_world.m_mac_grid[key].GetSpeed(vout);
	vout.Set(comp,m_GetSpeed.Get(m_speed).Get(comp));
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
void MacConvectSpeed<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::Calculate()
{
			
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		bool b=false;
		for(int i=1;i<=type_dim;++i)
		{
			b=b||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air_Boundary;
		}
		if(b)
		{
			Physvector<type_dim,type_data> temp;
			TracePart(it.key(),temp);
			it.data().SetTempSpeed(temp);
		}
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		for(int i=1;i<=type_dim;++i)
		{
			if(m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air_Boundary)
			{
				it.data().TempToSpeed();
				type_data d;
				it.data().GetInterTempSpeed(i,d);
				it.data().SetInterTempSpeed(i,d);
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
