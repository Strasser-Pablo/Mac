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
	m_layer_fluid.Calculate();
	for(int i=1;i<=m_level+1;++i)
	{
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
		{
			int lay;
			it.data().GetLayer(lay);
			if(lay==-1)
			{
				Physvector<type_dim,int> key2=it.key();
				for(int j=1;j<=type_dim;++j)
				{
					key2.GetRef(j)-=1;
					bool b1=false;
					bool b3=false;
					bool b5=false;
					type_data speed1;
					if(m_world.m_mac_grid.Exist(key2))
					{
						m_world.m_mac_grid[key2].GetLayer(lay);
						if(lay==i-1)
						{
							if(i!=1||!b)
							{
								m_world.m_mac_grid[key2].GetInterSpeed(j,speed1);
								b1=true;
							}
							else
							{
								b3=true;
								b1=true;
								m_world.m_mac_grid[key2].GetInterSpeed(j,speed1);
							}
						}
						if(lay==i)
						{
							b5=true;	
							m_world.m_mac_grid[key2].GetInterSpeed(j,speed1);
						}
					}
					key2.GetRef(j)+=2;
					bool b2=false;
					bool b4=false;
					type_data speed2;
					if(m_world.m_mac_grid.Exist(key2))
					{
						m_world.m_mac_grid[key2].GetLayer(lay);
						if(lay==i-1)
						{
							m_world.m_mac_grid[key2].GetInterSpeed(j,speed2);
							b2=true;
						}
						if(b1&&lay==i)
						{
							m_world.m_mac_grid[key2].GetInterSpeed(j,speed2);
							b4=true;
						}
					}
					key2.GetRef(j)-=1;
					type_data speed;
					if(b4)
					{
						speed=0.5*(speed1+speed2);
						m_world.m_mac_grid[it.key()].SetLayer(i);
					}
					else if(b1)
					{
						speed=speed1;
						m_world.m_mac_grid[it.key()].SetLayer(i);
					}
					else if(b2)
					{
						speed=speed2;
						m_world.m_mac_grid[it.key()].SetLayer(i);
					}
					else
					{
						speed=0;
					}
					if(!b3)
					{
						m_world.m_mac_grid[it.key()].SetInterSpeed(j,speed);
					}
					if(b5&&b2)
					{
						key2.GetRef(j)+=2;
						m_world.m_mac_grid[key2].GetInterSpeed(j,speed1);
						speed2=0.5*(speed1+speed);
						m_world.m_mac_grid[key2].SetInterSpeed(j,speed2);
					}
				}
			}
		}
	}
}
