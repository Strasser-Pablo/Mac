/**
 * @file UpdateDeleteCell.tpp
 * @brief
 * Implementation file for class UpdateDeleteCell.
 **/
 
template <class TypeWorld>
UpdateDeleteCell<TypeWorld>::UpdateDeleteCell(TypeWorld &world):m_world(world)
{
	
}


template <class TypeWorld>
void UpdateDeleteCell<TypeWorld>::Update()
{
	typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();
	while(it!=m_world.m_mac_grid.end())
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==-1){
			typename TypeWorld::type_keytable::iterator it2=it++;
			m_world.m_mac_grid.erase(it2);
			}
			else{
				++it;
			}
	}
}

