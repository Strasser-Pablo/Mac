/**
 * @file UpdateCellToInitialLayer.tpp
 * @brief
 * Implementation file for class UpdateCellToInitialLayer.
 **/
 
template <class TypeWorld>
UpdateCellToInitialLayer<TypeWorld>::UpdateCellToInitialLayer(TypeWorld & world):m_world(world)
{
	
}

template <class TypeWorld>
void UpdateCellToInitialLayer<TypeWorld>::Update()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		it.data().SetLayer(-1);
	}
}