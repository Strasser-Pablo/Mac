/**
 * @file UpdateCellFluid.tpp
 * @brief
 * Implementation file for class UpdateCellFluid.
 **/
template <class TypeWorld,class TypeStagPos>
UpdateCellFluid<TypeWorld,TypeStagPos>::UpdateCellFluid(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,type_cell& fluid,TypeStagPos & stag_pos):m_world(world),m_to_key(_1_h,h),m_fluid(fluid),m_stag_pos(stag_pos)
{
	
}

template <class TypeWorld,class TypeStagPos>
void UpdateCellFluid<TypeWorld,TypeStagPos>::Update()
{
	typename TypeWorld::type_key tempkey;
	for(typename TypeWorld::type_tablecontainer::iterator it= m_world.m_particle_list.begin();it!=m_world.m_particle_list.end();++it)
	{
		tempkey=m_to_key.ToKey(*it);
		if(type_dim==3)
		{
			if(tempkey.Get(2)<-5)
			{
				it=m_world.m_particle_list.erase(it);
				continue;
			}
		}
		m_world.m_mac_grid[tempkey].SetLayer(0);
		m_world.m_mac_grid[tempkey].SetCellType(m_fluid);
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell fluid;
		it.data().GetCellType(fluid);
		if(fluid!=m_fluid)
		{
			//Test if one component is constant speed.
			bool b=false;
			for(int i=1;i<=type_dim;++i)
			{
				bool b2;
			it.data().GetConstSpeed(i,b2);
				b=b||b2;
			}
			//ok one component is constant speed.
			if(b)
			{
				//create particle at center and set layer and fluid type.
				 m_world.m_particle_list.push_back(type_particle(m_to_key.FromKey(it.key())));
				 m_world.m_mac_grid[it.key()].SetLayer(0);
				 m_world.m_mac_grid[it.key()].SetCellType(m_fluid);
				 
				 for(int i=1;i<=type_dim;++i)
				 {
					 //Test witch direction is constant.
					 bool b2;
					it.data().GetConstSpeed(i,b2);
					b2=false;
					if(b2)
					{
					 //Created particle at the two opposing edge.
						m_world.m_particle_list.push_back(type_particle(m_stag_pos.Get(it.key(),i)));
					    typename TypeWorld::type_key tempkey2=it.key();
						tempkey2.GetRef(i)+=1;
						m_world.m_particle_list.push_back(type_particle(m_stag_pos.Get(tempkey2,i)));
					}
				 }
				
				}
			}
			 
		}
	}