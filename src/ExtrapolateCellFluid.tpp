/**
 * @file ExtrapolateCellFluid.tpp
 * @brief
 * Implementation file for class ExtrapolateCellFluid.
 **/

template <class TypeWorld,class TypeGetCellType>
ExtrapolateCellFluid<TypeWorld,TypeGetCellType>::ExtrapolateCellFluid(TypeWorld & world, TypeGetCellType & GetCellType,int level):m_world(world),m_level(level),m_layer_fluid(world,GetCellType),m_GetCellType(GetCellType)
{
	
}


template <class TypeWorld,class TypeGetCellType>
void ExtrapolateCellFluid<TypeWorld,TypeGetCellType>::Calculate(bool b)
{
	m_layer_fluid.Calculate();
	for(int i=1;i<=m_level;++i)
	{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			int lay;
			it.data().GetLayer(lay);
			if(lay==-1)
			{
				NeighborsPhysvector<int,type_dim> Nv(it.key());
				Physvector<type_dim,int> neigh;
				Physvector<type_dim,type_data> new_speed;
				new_speed.SetAll(0);
				int nb=0;
				while(Nv.GetNext(neigh))
				{
					if(m_world.m_mac_grid.Exist(neigh))
					{
						m_world.m_mac_grid[neigh].GetLayer(lay);
						if(lay==i-1)
						{
						for(int comp=1;comp<=type_dim;++comp)
							{
								Physvector<type_dim,type_data> temp;
								m_world.m_mac_grid[neigh].GetSpeed(temp);
								new_speed+=temp;
								++nb;
							}
						}
					}
				}
					if(nb!=0)
					{
					new_speed*=(1.0/nb);
					if(b)
					{
					if(i<=1)
					{
						Physvector<type_dim,type_data> new_speed2;
						it.data().GetSpeed(new_speed2);
						for(int comp=1;comp<=type_dim;++comp)
						{
							if(m_GetCellType.GetInter(it.key(),comp)==Type_Inter::Fluid_Air_Boundary||m_GetCellType.GetInter(it.key(),comp)==Type_Inter::Fluid_Air)
							{
								new_speed.GetRef(comp)=new_speed2.Get(comp);
							}
						}
					}
					}
					it.data().SetSpeed(new_speed);
					it.data().SetLayer(i);
					}
				}
			}
		}
}

