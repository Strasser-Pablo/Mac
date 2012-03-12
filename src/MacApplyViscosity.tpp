/**
 * @file MacApplyViscosity.tpp
 * @brief
 * Implementation file for class MacApplyViscosity.
 **/

template<class TypeWorld,class GetTypeCell>
MacApplyViscosity<TypeWorld,GetTypeCell>::MacApplyViscosity(TypeWorld &world,const type_data &viscosity, const type_data & dt,const Physvector<type_dim,type_data> & _1_h,GetTypeCell &getTypeCell):m_world(world),m_viscosity(viscosity),m_dt(dt),m_lap(m_world,_1_h),m_GetTypeCell(getTypeCell)
{
	
}

template<class TypeWorld,class GetTypeCell>
void MacApplyViscosity<TypeWorld,GetTypeCell>::Calculate()
{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		bool b=false;
		for(int i=1;i<=type_dim;++i)
		{
			b=b||m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid;
		}
		if(b)
		{
		Physvector<type_dim,type_data> temp;
		m_lap.Calculate(it.key(),temp);
		it.data().SetTempSpeed(temp);
		}
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		for(int i=1;i<=type_dim;++i)
		{
			if(m_GetTypeCell.GetInter(it.key(),i)==Type_Inter::Fluid_Fluid)
			{
				type_data d;
				it.data().GetInterTempSpeed(i,d);
				d*=m_dt*m_viscosity;
				type_data s;
				it.data().GetInterSpeed(i,s);
				s+=d;
				it.data().SetInterSpeed(i,s);
			}
		}
	}
}
