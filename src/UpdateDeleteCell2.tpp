/**
 * @file UpdateDeleteCell2.tpp
 * @brief
 * Implementation file for class UpdateDeleteCell.
 **/
 
template <class TypeWorld>
UpdateDeleteCell2<TypeWorld>::UpdateDeleteCell2(TypeWorld &world,TypeGetCellType& GetCellType):m_world(world),m_GetCellType(GetCellType)
{
	
}


template <class TypeWorld>
void UpdateDeleteCell2<TypeWorld>::Update()
{
	typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();
	while(it!=m_world.m_mac_grid.end())
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==-1&&m_GetCellType.GetIsFluide(it.key()))
		{
			
			typename TypeWorld::type_keytable::iterator it2=it++;
			m_world.m_mac_grid.erase(it2);
		}
		else
		{
			++it;
			
		}
	}
}

