/**
 * @file ExtrapolateCellFluid2.tpp
 * @brief
 * Implementation file for class ExtrapolateCellFluid.
 **/

	template <class TypeWorld,class TypeGetCellType>
ExtrapolateCellFluid2<TypeWorld,TypeGetCellType>::ExtrapolateCellFluid2(TypeWorld & world, TypeGetCellType & GetCellType,const Physvector<type_dim,type_data>& h,const Physvector<type_dim,type_data>& _1_h):m_world(world),m_layer_fluid(world,GetCellType),m_GetCellType(GetCellType),m_h(h),m_1_h(_1_h)
{

}


	template <class TypeWorld,class TypeGetCellType>
void ExtrapolateCellFluid2<TypeWorld,TypeGetCellType>::Calculate(bool bconst)
{
	m_layer_fluid.Calculate();
	bool bcont=true;
	int i=0;
	while(bcont)
	{
		bcont=false;
		//Phase d to jump in first iteration.
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			int lay;
			it.data().GetLayer(lay);
			if(lay==i)
			{
				bcont=true;
				Physvector<type_dim,int> neigh=it.key();
				for(int j=1;j<=type_dim;++j)
				{
					neigh.GetRef(j)-=1;
					if(m_world.m_mac_grid.Exist(neigh))
					{
						m_world.m_mac_grid[neigh].GetLayer(lay);
						if(lay==-1)
						{
							m_world.m_mac_grid[neigh].SetLayer(i+1);
						}
					}
					else
					{
						lay=-1;
					}
					neigh.GetRef(j)+=1;
					if(lay==i+1||lay==-1||(lay==i&&i>0))
					{
						NeighborsPhysvector<int,type_dim> Nv(neigh);
						Physvector<type_dim,int> neigh2;
						type_data new_speed=0;
						int nb=0;
						if(i>0)
						{
							while(Nv.GetNext(neigh2))
							{
								if(m_world.m_mac_grid.Exist(neigh2))
								{
									m_world.m_mac_grid[neigh2].GetLayer(lay);
									if(lay==i-1)
									{
										type_data temp;
										m_world.m_mac_grid[neigh2].GetInterSpeed(j,temp);
										new_speed+=temp;
										++nb;
									}
								}
							}
							if(nb!=0)
							{
								new_speed*=(1.0/nb);
								m_world.m_mac_grid[neigh].SetInterSpeed(j,new_speed);
							}
						}
					}
				}
				}
			}
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			int lay;
			it.data().GetLayer(lay);
			if(lay==i)
			{
				bcont=true;
				Physvector<type_dim,int> neigh=it.key();
				for(int j=1;j<=type_dim;++j)
				{
					neigh.GetRef(j)+=1;
					if(m_world.m_mac_grid.Exist(neigh))
					{
						m_world.m_mac_grid[neigh].GetLayer(lay);
						if(lay==i+1||lay==-1)
						{
							m_world.m_mac_grid[neigh].SetLayer(i+1);
							NeighborsPhysvector<int,type_dim> Nv(neigh);
							Physvector<type_dim,int> neigh2;
							type_data new_speed=0;
							int nb=0;
							if(i>0||bconst)
							{
								while(Nv.GetNext(neigh2))
								{
									if(m_world.m_mac_grid.Exist(neigh2))
									{
										m_world.m_mac_grid[neigh2].GetLayer(lay);
										if(lay==i)
										{
											type_data temp;
											m_world.m_mac_grid[neigh2].GetInterSpeed(j,temp);
											new_speed+=temp;
											++nb;
										}
									}
								}
								if(nb!=0)
								{
									new_speed*=(1.0/nb);
									m_world.m_mac_grid[neigh].SetInterSpeed(j,new_speed);
								}
							}
						}
					}
					neigh.GetRef(j)-=1;
				}
			}
		}
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			int lay;
			it.data().GetLayer(lay);
			if(lay!=i)
			{
				continue;
			}
			if(m_GetCellType.GetIsBoundaryFluid(it.key()))
			{
				continue;
			}
			type_data div=0;
			Physvector<type_dim,int> key=it.key();
			for(int j=1;j<=type_dim;++j)
			{
				type_data temp;
				it.data().GetInterSpeed(j,temp);
				div-=temp*m_1_h.Get(j);
			}
			bool b=false;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)+=1;
				if(m_world.m_mac_grid.Exist(key))
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					div+=temp*m_1_h.Get(j);
				}
				else
				{
					b=true;
					break;
				}
				key.GetRef(j)-=1;
			}
			if(b)
			{
				continue;
			}
			if(div==0)
			{
				continue;
			}
			int nop=0;
			int ndouble=0;
			int nnone=0;
			type_data nd=0;
			for(int j=1;j<=type_dim;++j)
			{
				bool bext;
				key.GetRef(j)+=1;
				m_world.m_mac_grid[key].GetLayer(lay);
				key.GetRef(j)-=2;
				int lay2;
				if(m_world.m_mac_grid.Exist(key))
				{
					m_world.m_mac_grid[key].GetLayer(lay2);
					bext=true;
				}
				else
				{
					bext=false;
				}
				int k=-1;
				key.GetRef(j)+=1;
				if(lay<=i)
				{
					k=0;
				}
				if(bext&&(lay2<=i))
				{
					k=1;
				}
				if(k==-1)
				{
					nd+=2*m_1_h.Get(j);
					++ndouble;
				}
				if(k==0)
				{
					if(bext&&lay2<=i)
					{
						++nnone;
						k=-1;
					}
					else
					{
						nd+=m_1_h.Get(j);
						++nop;
					}
				}
				if(k==1)
				{
					if(lay<=i)
					{
						++nnone;
						k=-1;
					}
					else
					{
						nd+=m_1_h.Get(j);
						++nop;
					}
				}
				if(k==0)
				{
					type_data temp;
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					key.GetRef(j)-=1;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
				}
				else if(k==1)
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)-=1;
				}
			}
			if(ndouble==0&&nnone==0)
			{
				continue;
			}
			div=0;
			for(int j=1;j<=type_dim;++j)
			{
				type_data temp;
				it.data().GetInterSpeed(j,temp);
				div-=temp*m_1_h.Get(j);
			}
			b=false;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)+=1;
				type_data temp;
				m_world.m_mac_grid[key].GetInterSpeed(j,temp);
				div+=temp*m_1_h.Get(j);
				key.GetRef(j)-=1;
			}
			type_data dist=div/nd;
			for(int j=1;j<=type_dim;++j)
			{
				bool bext;
				key.GetRef(j)+=1;
				m_world.m_mac_grid[key].GetLayer(lay);
				key.GetRef(j)-=2;
				int lay2;
				if(m_world.m_mac_grid.Exist(key))
				{
					m_world.m_mac_grid[key].GetLayer(lay2);
					bext=true;
				}
				else
				{
					bext=false;
				}
				int k=-1;
				key.GetRef(j)+=1;
				if(lay<=i)
				{
					k=0;
				}
				if(bext&&lay2<=i)
				{
					k=1;
				}
				if(k==0)
				{
					if(bext&&lay2<=i)
					{
						k=3;
					}
				}
				if(k==1)
				{
					if(lay<=i)
					{
						k=3;
					}
				}
				if(k==0)
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp+=dist*m_h.Get(j);
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
				}
				else if(k==1)
				{
					type_data temp;
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp-=dist*m_h.Get(j);
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)-=1;
				}
				else if(k==-1)
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp+=dist*m_h.Get(j);
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp-=dist*m_h.Get(j);
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)-=1;
				}
			}
		}
		++i;
	}
		if(bconst)
		{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			it.data().SetDivergence(0);
		}
		}
}
