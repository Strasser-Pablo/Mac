/**
 * @file ExtrapolateCellFluid.tpp
 * @brief
 * Implementation file for class ExtrapolateCellFluid.
 **/

template <class TypeWorld>
ExtrapolateCellFluid<TypeWorld>::ExtrapolateCellFluid(TypeWorld & world, type_cell fluid,int level,NeighborsVelocity<type_dim,int>& neighv):m_world(world),m_fluid(fluid),m_level(level),m_layer_fluid(world,fluid),m_neighv(neighv)
{
	
}


template <class TypeWorld>
void ExtrapolateCellFluid<TypeWorld>::Calculate()
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
					Physvector<type_dim,type_data> new_speed2;
					it.data().GetSpeed(new_speed2);
					for(int comp=1;comp<=type_dim;++comp)
					{
						if(i<=1)
						{
							Physvector<type_dim,int> ntemp;
							if(m_neighv.Get(comp,ntemp))
							{
								Physvector<type_dim,int> ntemp2=it.key()-ntemp;
								m_world.m_mac_grid[ntemp2].GetLayer(lay);
								if(lay==0)
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


template <class TypeWorld>
void ExtrapolateCellFluid<TypeWorld>::Calculate2()
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

					it.data().SetSpeed(new_speed);
					it.data().SetLayer(i);
					}
				}

			}
		}
}

