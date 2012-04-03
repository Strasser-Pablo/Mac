/**
 * @file ExtrapolateCellFluid2.tpp
 * @brief
 * Implementation file for class ExtrapolateCellFluid.
 **/

	template <class TypeWorld,class TypeGetCellType>
ExtrapolateCellFluid2<TypeWorld,TypeGetCellType>::ExtrapolateCellFluid2(TypeWorld & world, TypeGetCellType & GetCellType,int level):m_world(world),m_level(level),m_layer_fluid(world,GetCellType),m_GetCellType(GetCellType)
{

}


	template <class TypeWorld,class TypeGetCellType>
void ExtrapolateCellFluid2<TypeWorld,TypeGetCellType>::Calculate(bool bconst)
{
	cout<<"in extrapo "<<endl;
	m_layer_fluid.Calculate();
	bool bcont=true;
	int i=0;
	while(bcont)
	{
		bcont=false;
		//Phase d to jump in first iteration.
		if(i>=1)
		{
			for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
			{

				int lay;
				it.data().GetLayer(lay);
				if(lay==-1)
				{
					bcont=true;
					for(int j=1;j<=type_dim;++j)
					{
						Physvector<type_dim,int> neigh=it.key();
						neigh.GetRef(j)+=1;
						if(m_world.m_mac_grid.Exist(neigh))
						{
						m_world.m_mac_grid[neigh].GetLayer(lay);
						if(lay==i-1)
						{
							NeighborsPhysvector<int,type_dim> Nv(it.key());
							type_data new_speed=0;
							int nb=0;
							while(Nv.GetNext(neigh))
							{
								if(m_world.m_mac_grid.Exist(neigh))
								{
									m_world.m_mac_grid[neigh].GetLayer(lay);
									if(lay==i-1)
									{
										type_data temp;
										m_world.m_mac_grid[neigh].GetInterSpeed(j,temp);
										new_speed+=temp;
										++nb;
									}
								}
							}
							if(nb!=0)
							{
								new_speed*=(1.0/nb);
								cout<<"new speed "<<it.key()<<" "<<new_speed<<endl;
								it.data().SetInterSpeed(j,new_speed);
							}
							it.data().SetLayer(i);
						}
					}
					}
				}
			}
		}
		++i;
		{

			for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
			{

				int lay;
				it.data().GetLayer(lay);
				if(lay==-1)
				{
					bcont=true;
					for(int j=1;j<=type_dim;++j)
					{
						Physvector<type_dim,int> neigh=it.key();
						neigh.GetRef(j)-=1;
						if(m_world.m_mac_grid.Exist(neigh))
						{
						m_world.m_mac_grid[neigh].GetLayer(lay);
						if(lay==i-1)
						{
							int nb=0;
							type_data new_speed;
							cout<<"bconst "<<bconst<<" "<<i<<endl;
						 	if((i==1&&bconst)||i!=1)
							{
								cout<<"var "<<endl;
								new_speed=0;
							NeighborsPhysvector<int,type_dim> Nv(it.key());
							while(Nv.GetNext(neigh))
							{
								if(m_world.m_mac_grid.Exist(neigh))
								{
									m_world.m_mac_grid[neigh].GetLayer(lay);
									if(lay==i-1)
									{
										type_data temp;
										m_world.m_mac_grid[neigh].GetInterSpeed(j,temp);
										new_speed+=temp;
										++nb;
									}
								}
							}
							}
							if(nb!=0)
							{
								cout<<"new speed "<<endl;
								new_speed*=(1.0/nb);
								cout<<"new speed "<<it.key()<<" "<<new_speed<<endl;
								it.data().SetInterSpeed(j,new_speed);
							}
							it.data().SetLayer(i);
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
			if(lay!=i-1)
			{
				continue;
			}
			if(m_GetCellType.GetIsBoundaryFluid(it.key()))
			{
				continue;
			}
			cout<<"it key "<<it.key()<<endl;
			type_data div=0;
			Physvector<type_dim,int> key=it.key();
			for(int j=1;j<=type_dim;++j)
			{
				type_data temp;
				it.data().GetInterSpeed(j,temp);
				cout<<"temp01 "<<temp<<" "<<it.key()<<endl;
				div-=temp;
			}
			bool b=false;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)+=1;
				if(m_world.m_mac_grid.Exist(key))
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					cout<<"temp02 "<<temp<<" "<<key<<endl;
					div+=temp;
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
			cout<<"div0 "<<div<<endl;
			if(div==0)
			{
				continue;
			}
			b=false;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)-=1;
				if(!m_world.m_mac_grid.Exist(key))
				{
					b=true;
					break;
				}
				key.GetRef(j)+=1;
			}
			if(b)
			{
				continue;
			}
			int nop=0;
			int ndouble=0;
			int nnone=0;
			for(int j=1;j<=type_dim;++j)
			{
				cout<<"key "<<key<<endl;
				key.GetRef(j)+=1;
				m_world.m_mac_grid[key].GetLayer(lay);
				key.GetRef(j)-=2;
				int lay2;
				m_world.m_mac_grid[key].GetLayer(lay2);
				int k=-1;
				key.GetRef(j)+=1;
				cout<<"i "<<i<<endl;
				cout<<"lay "<<lay<<" "<<lay2<<endl;
				if(lay==i-1)
				{
					k=0;
				}
				if(lay2==i-1)
				{
					k=1;
				}
				if(k==-1)
				{
					++ndouble;
				}
				if(k==0)
				{
					if(lay2!=-1)
					{
						++nnone;
						k=-1;
					}
					else
					{
						++nop;
					}
				}
				if(k==1)
				{
					if(lay!=i-2)
					{
						++nnone;
						k=-1;
					}
					else
					{
						++nop;
					}
				}
				if(k==0)
				{
					cout<<"oppppp "<<endl;
					type_data temp;
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					key.GetRef(j)-=1;
					cout<<"new speed "<<key<<" "<<temp<<endl;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
				}
				else if(k==1)
				{
					cout<<"oppppp "<<endl;
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					cout<<"new speed "<<key<<" "<<temp<<endl;
					key.GetRef(j)-=1;
				}
			}
			cout<<"it key "<<it.key()<<endl;
			cout<<"nnone "<<nnone<<endl;
			cout<<"ndouble "<<ndouble<<endl;
			cout<<"nop "<<nop<<endl;
			if(ndouble==0&&nnone==0)
			{
				continue;
			}
			div=0;
			for(int j=1;j<=type_dim;++j)
			{
				type_data temp;
				it.data().GetInterSpeed(j,temp);
				cout<<"temp "<<temp<<" "<<it.key()<<endl;
				div-=temp;
			}
			b=false;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)+=1;
				type_data temp;
				m_world.m_mac_grid[key].GetInterSpeed(j,temp);
				cout<<"temp "<<temp<<" "<<key<<endl;
				div+=temp;
				key.GetRef(j)-=1;
			}
			int n=2*ndouble+nop;
			type_data dist=div/n;
			cout<<"dist "<<dist<<endl;
			for(int j=1;j<=type_dim;++j)
			{
				key.GetRef(j)+=1;
				m_world.m_mac_grid[key].GetLayer(lay);
				key.GetRef(j)-=2;
				int lay2;
				m_world.m_mac_grid[key].GetLayer(lay2);
				int k=-1;
				key.GetRef(j)+=1;
				if(lay==i-1)
				{
					cout<<"k0"<<endl;
					k=0;
				}
				if(lay2==i-1)
				{
					cout<<"k1"<<endl;
					k=1;
				}
				if(k==0)
				{
					if(lay2!=-1)
					{
						k=3;
					}
				}
				if(k==1)
				{
					if(lay!=i-2)
					{
						k=3;
					}
				}
				if(k==0)
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp+=dist;
					cout<<"set speed "<<key<<" "<<temp<<endl;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
				}
				else if(k==1)
				{
					type_data temp;
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					temp-=dist;
					cout<<"set speed "<<key<<" "<<temp<<endl;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)-=1;
				}
				else if(k==-1)
				{
					cout<<"key222222 "<<key<<endl;
					type_data temp;
					cout<<"it key22222 "<<it.key()<<endl;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					cout<<"temp1 "<<temp<<endl;
					temp+=dist;
					cout<<"set speed "<<key<<" "<<temp<<endl;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)+=1;
					m_world.m_mac_grid[key].GetInterSpeed(j,temp);
					cout<<"temp2 "<<temp<<endl;
					temp-=dist;
					cout<<"set speed "<<key<<" "<<temp<<endl;
					m_world.m_mac_grid[key].SetInterSpeed(j,temp);
					key.GetRef(j)-=1;
				}
			}
		}
		cout<<"i "<<i<<endl;
	}
}
