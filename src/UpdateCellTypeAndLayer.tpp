/**
 * @file UpdateCellTypeAndLayer.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer.
 **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
UpdateCellTypeAndLayer<TypeWorld,TypeGetCellType,TypeFunctionPressure>::UpdateCellTypeAndLayer(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres):m_level(level),m_GetCellType(GetCellType),m_world(world),m_func_pres(func_pres){
	
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Update()
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
					m_world.m_mac_grid[neigh].SetCellType(m_GetCellType.GetAir());
					m_world.m_mac_grid[neigh].SetLayer(i);
					m_world.m_mac_grid[neigh].SetPressure(m_func_pres(neigh));
				}
			}
		}
	}
	}
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer<TypeWorld,TypeGetCellType,TypeFunctionPressure>::PrepareConstSpeed()
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
									m_world.m_mac_grid[tempkey].SetCellType(m_GetCellType.GetAir());
							}
						}
		}
}