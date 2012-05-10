/**
 * @file MacGravity.tpp
 * @brief
 * Implementation file for class MacGravity.
 **/

template <class TypeWorld,class GetCellType>
MacGravity<TypeWorld,GetCellType>::MacGravity( TypeWorld & world,const Physvector<type_dim,type_data>& g,const type_data &dt,const type_cell fluid,GetCellType & getCellType):m_g(g),m_dt(dt),m_fluid(fluid),m_world(world),m_GetCellType(getCellType)
{
}


template <class TypeWorld,class GetCellType>
void MacGravity<TypeWorld,GetCellType>::Calculate()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		for(int i=1;i<=type_dim;++i)
		{
		if(m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Air||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Air_Boundary||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Fluid||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Air_Boundary||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Air_Boundary||m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Boundary_Fluid_Boundary)
		{
			type_data temp;
	 		it.data().GetInterSpeed(i,temp);
			temp+=m_g.Get(i)*m_dt;
			it.data().SetInterSpeed(i,temp);
		}
		}
	}
}
