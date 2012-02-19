/**
 * @file UpdateCellTypeAndLayer.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer.
 **/
template <class TypeWorld>
UpdateCellTypeAndLayer<TypeWorld>::UpdateCellTypeAndLayer(TypeWorld & world,type_cell& fluid, type_cell& air,int level):m_level(level),m_air(air),m_fluid(fluid),m_world(world){
	
}

template <class TypeWorld>
void UpdateCellTypeAndLayer<TypeWorld>::Update()
{
	
	for(int i=1;i<=m_level;++i){
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==i-1){
			NeighborsPhysvector<typename TypeWorld::type_key::type_data, TypeWorld::type_dim> N(it.key());
			typename TypeWorld::type_key neigh;
			while(N.GetNext(neigh)){
				m_world.m_mac_grid[neigh].GetLayer(layer);
				if(layer==-1)
				{
					m_world.m_mac_grid[neigh].SetCellType(m_air);
					m_world.m_mac_grid[neigh].SetLayer(i);
					cout<<"key lay "<<it.key().Get(1)<<" "<<it.key().Get(2)<<" "<<it.key().Get(3)<<endl;
					cout<<"neigh lay "<<neigh.Get(1)<<" "<<neigh.Get(2)<<" "<<neigh.Get(3)<<endl;
					cout<<"layer "<<i<<endl;
				}
			}
		}
	}
	}
}


template <class TypeWorld>
void UpdateCellTypeAndLayer<TypeWorld>::PrepareConstSpeed()
{

		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
						for(int i=1;i<=type_dim;++i)
						{
							bool b;
							it.data().GetConstSpeed(i,b);
							if(b)
							{
							Physvector<type_dim,int> tempkey=it.key();
								tempkey.GetRef(i)+=1;
									Physvector<type_dim,type_data> temp;
									it.data().GetSpeed(temp);
									m_world.m_mac_grid[tempkey].SetSpeed(temp);
									m_world.m_mac_grid[tempkey].SetCellType(m_air);
							}
						}
		}
}