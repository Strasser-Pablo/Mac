/**
 * @file SetLayerFluidCell.tpp
 * @brief
 * Implementation file for class SetLayerFluidCell.
 **/

template <class TypeWorld>
SetLayerFluidCell<TypeWorld>::SetLayerFluidCell(TypeWorld & world,type_cell fluid):m_world(world),m_fluid(fluid)
{
	
}

template <class TypeWorld>
void SetLayerFluidCell<TypeWorld>::Calculate()
{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid)
		{
		it.data().SetLayer(0);
		}
		else
		{
		it.data().SetLayer(-1);
		it.data().SetPressure(0);
		}
	}
}