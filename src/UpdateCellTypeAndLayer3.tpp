/**
 * @file UpdateCellTypeAndLayer3.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer.
 **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres):m_level(level),m_GetCellType(GetCellType),m_world(world),m_func_pres(func_pres){
	
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Update()
{
	CalculateAirNeighbour();
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::PrepareConstSpeed()
{

	CalculateAirNeighbour();
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CalculateAirNeighbour()
{
	m_nb_comp_con=1;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==0)
		{
			NeighborsPhysvector<int,type_dim> NV(it.key());
			Physvector<type_dim,int> neigh;
			while(NV.GetNext(neigh))
			{
				DoAir(neigh);
			}
		}
	}
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::DoAir(Physvector<type_dim,int> & key)
{
		int layer;
		m_world.m_mac_grid[key].GetLayer(layer);
		if(layer==-1)
		{
			m_world.m_mac_grid[key].SetLayer(m_nb_comp_con);
			NeighborsPhysvector<int,type_dim> NV(key);
			Physvector<type_dim,int> neigh;
			while(NV.GetNext(neigh))
			{
					NeighborsDiagPhysvector<int,type_dim> NVD(neigh);
					Physvector<type_dim,int> neigh2;
					while(NVD.GetNext(neigh2))
					{
						m_world.m_mac_grid[neigh2].GetLayer(layer);
						if(layer==0)
						{
							DoAir(neigh);
							break;
						}
					}
			}
			++m_nb_comp_con;
		}
}