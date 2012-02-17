/**
 * @file MacApplyViscosity.tpp
 * @brief
 * Implementation file for class MacApplyViscosity.
 **/

template<class TypeWorld>
MacApplyViscosity<TypeWorld>::MacApplyViscosity(TypeWorld &world,const type_data &viscosity, const type_data & dt,const Physvector<type_dim,type_data> & _1_h,const type_cell fluid):m_world(world),m_viscosity(viscosity),m_dt(dt),m_lap(m_world,_1_h),m_fluid(fluid)
{
	
}

template<class TypeWorld>
void MacApplyViscosity<TypeWorld>::Calculate()
{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid){
		Physvector<type_dim,type_data> temp;
		m_lap.Calculate(it.key(),temp);
		it.data().SetTempSpeed(temp);
		}
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid){
			NeighborsPhysvector<int,type_dim> Neigh(it.key());
			Physvector<type_dim,int> NeighV;
			bool b=false;
			while(Neigh.GetNext(NeighV))
			{
				if(!m_world.m_mac_grid.Exist(NeighV))
				{
					b=true; break;
				}
			}
			if(b)
			{
				continue;
			}
		Physvector<type_dim,type_data> temp;
		it.data().GetTempSpeed(temp);
		Physvector<type_dim,type_data> speed;
		it.data().GetSpeed(speed);
		speed+=m_viscosity*m_dt*temp;
		it.data().SetSpeed(speed);
		}
	}
}