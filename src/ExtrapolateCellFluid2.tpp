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
void ExtrapolateCellFluid2<TypeWorld,TypeGetCellType>::Calculate(bool b)
{
	cout<<"in extrapo "<<endl;
	m_layer_fluid.Calculate();
	for(int i=1;i<=m_level+1;++i)
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
					if(new_speed.GetRef(1)!=0.00)
					{
						cout<<"speed non 0 "<<it.key()<<" "<<new_speed<<endl;
					}
					it.data().SetSpeed(new_speed);
					it.data().SetLayer(i);
					}
				}
			}
		}

for(int j=0;j<=m_level+1;++j)
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		bool b=true;
		if(j==0)
		{
			for(int i=1;i<=type_dim;++i)
			{
				//Test if contact with air.
				if(m_GetCellType.GetInter(it.key(),i)==Type_Inter::Fluid_Air||m_GetCellType.GetInter(it.key(),i,1)==Type_Inter::Fluid_Air)
				{
					b=false;
					break;
				}
			}
			if(b)
			{
				continue;
			}
		}
			//if not good layer exit.
			int lay;
			it.data().GetLayer(lay);
			if(lay!=j)
			{
				continue;
			}
			type_data div=0;
			//calculate divergence below.
			for(int i=1;i<=type_dim;++i)
			{
				type_data temp;
				it.data().GetInterSpeed(i,temp);
				div-=temp;
			}
			Physvector<type_dim,int> key=it.key();
			b=true;
			int n=0;
			for(int i=1;i<=type_dim;++i)
			{
				key.GetRef(i)+=1;
				if(m_world.m_mac_grid.Exist(key))
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(i,temp);
					div+=temp;
					int templay;
					m_world.m_mac_grid[key].GetLayer(templay);
					if(templay==lay+1)
					{
						++n;
					}
				}
				else
				{
					b=false;
					break;
				}
				key.GetRef(i)-=1;
			}
			if(!b)
			{
				continue;
			}
			for(int i=1;i<=type_dim;++i)
			{
				key.GetRef(i)-=1;
				if(m_world.m_mac_grid.Exist(key))
				{
					int templay;
					m_world.m_mac_grid[key].GetLayer(templay);
					if(templay==lay+1)
					{
						++n;
					}
				}
				key.GetRef(i)+=1;
			}
			if(n==0)
			{
				continue;
			}
			type_data dist=div/n;
			if(dist!=0)
			{
				cout<<"div "<<div<<endl;
				cout<<"dist non 0 "<<endl;
			}
			for(int i=1;i<=type_dim;++i)
			{
				key.GetRef(i)+=1;
				int templay;
				m_world.m_mac_grid[key].GetLayer(templay);
				if(templay==lay+1)
				{
					type_data temp;
					m_world.m_mac_grid[key].GetInterSpeed(i,temp);
					temp-=dist;
					m_world.m_mac_grid[key].SetInterSpeed(i,temp);
				}
				key.GetRef(i)-=1;
			}
			for(int i=1;i<=type_dim;++i)
			{
				key.GetRef(i)-=1;
				if(m_world.m_mac_grid.Exist(key))
				{
					int templay;
					m_world.m_mac_grid[key].GetLayer(templay);
					if(templay==lay+1)
					{
						type_data temp;
						m_world.m_mac_grid[it.key()].GetInterSpeed(i,temp);
						temp+=dist;
						m_world.m_mac_grid[it.key()].SetInterSpeed(i,temp);
					}
				}
				key.GetRef(i)+=1;
			}
				
	}
}

}
