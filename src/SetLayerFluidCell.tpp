/**
 * @file SetLayerFluidCell.tpp
 * @brief
 * Implementation file for class SetLayerFluidCell.
 **/

template <class TypeWorld,class TypeGetCellType>
SetLayerFluidCell<TypeWorld,TypeGetCellType>::SetLayerFluidCell(TypeWorld & world,TypeGetCellType &GetCellType):m_world(world),m_GetCellType(GetCellType)
{
	
}

template <class TypeWorld,class TypeGetCellType>
void SetLayerFluidCell<TypeWorld,TypeGetCellType>::Calculate()
{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(!m_GetCellType.GetIsAir(type))
		{
			it.data().SetLayer(0);
		}
		else
		{
			it.data().SetLayer(-1);
		}
	}
}
