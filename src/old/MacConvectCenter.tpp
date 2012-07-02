template <class TypeWorld,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::MacConvectCenter(TypeWorld & world,TypeGetSpeed & GetSpeed, TypeGetStagSpeedPos &GetStagPos,type_data & dt,GetTypeCell& getTypeCell,Physvector<type_dim,type_data> & h,Physvector<type_dim,type_data>& _1_h):m_world(world),m_GetSpeed(GetSpeed),m_dt(dt),m_h(h),m_1_h(_1_h),m_stag_pos(GetStagPos),m_GetTypeCell(getTypeCell)
{

}


template <class TypeWorld,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
typename MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::type_data MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::ElementaryUpwind(Physvector<type_dim,int>& key,int i,int j)
{
	type_data U1;
	type_data U2;
        type_data U=m_GetSpeed.Get(m_stag_pos.Get(key,i)).GetRef(j);
	key.GetRef(j)+=1;
	m_world.m_mac_grid[key].GetInterSpeed(i,U1);
	key.GetRef(j)-=2;
	m_world.m_mac_grid[key].GetInterSpeed(i,U2);
	U*=0.5*(U1-U2)*m_1_h.Get(j);
	return U;
}

template <class TypeWorld,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
typename MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::type_data MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::ElementaryUpwind(Physvector<type_dim,int> &&key,int i,int j)
{
	type_data U1;
	type_data U2;
        type_data U=m_GetSpeed.Get(m_stag_pos.Get(key,i)).GetRef(j);
	key.GetRef(j)+=1;
	m_world.m_mac_grid[key].GetInterSpeed(i,U1);
	key.GetRef(j)-=2;
	m_world.m_mac_grid[key].GetInterSpeed(i,U2);
	U*=0.5*(U1-U2)*m_1_h.Get(j);
	key.GetRef(j)+=1;
	return U;
}

template <class TypeWorld,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
void MacConvectCenter<TypeWorld,TypeGetSpeed,TypeGetStagSpeedPos,GetTypeCell>::Calculate()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{	
		it.data().SpeedToTemp();
		for(int i=1;i<=type_dim;++i)
		{
			if(m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Air_Boundary||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Air_Boundary||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Air||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Fluid_Boundary)
			{
				type_data v;
				it.data().GetInterTempSpeed(i,v);
				for(int j=1;j<=type_dim;++j)
				{
					v-=ElementaryUpwind(it.key(),i,j)*m_dt;
				}
				it.data().SetInterTempSpeed(i,v);
			}
		}
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{	
		it.data().TempToSpeed();
	}
}
