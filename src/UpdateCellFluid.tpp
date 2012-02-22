/**
 * @file UpdateCellFluid.tpp
 * @brief
 * Implementation file for class UpdateCellFluid.
 **/
template <class TypeWorld,class TypeStagPos,class TypeGetCellType>
UpdateCellFluid<TypeWorld,TypeStagPos,TypeGetCellType>::UpdateCellFluid(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos):m_world(world),m_to_key(_1_h,h),m_stag_pos(stag_pos),m_h(h),m_GetCellType(GetCellType)
{
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType>
void UpdateCellFluid<TypeWorld,TypeStagPos,TypeGetCellType>::Update()
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
		m_world.m_mac_grid[tempkey].SetCellType(m_GetCellType.GetFluid());
	}
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell fluid;
		it.data().GetCellType(fluid);
		if(!m_GetCellType.GetIsFluid(fluid))
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
				 m_world.m_mac_grid[it.key()].SetCellType(m_GetCellType.GetFluid());
				 
				 for(int i=1;i<=type_dim;++i)
				 {
					 //Test witch direction is constant.
					 bool b2;
					it.data().GetConstSpeed(i,b2);
					if(type_dim==2)
					{
						Physvector<type_dim,type_data> keytemp=m_to_key.FromKey(it.key());
						keytemp.GetRef(1)+=0.25*m_h.Get(1);
						m_world.m_particle_list.push_back(type_particle(keytemp));
						keytemp.GetRef(1)-=0.5*m_h.Get(1);
						m_world.m_particle_list.push_back(type_particle(keytemp));
						keytemp.GetRef(2)+=0.25*m_h.Get(2);
						m_world.m_particle_list.push_back(type_particle(keytemp));
						keytemp.GetRef(2)-=0.5*m_h.Get(2);
						m_world.m_particle_list.push_back(type_particle(keytemp));
						keytemp.GetRef(1)+=0.5*m_h.Get(1);
						m_world.m_particle_list.push_back(type_particle(keytemp));
						keytemp.GetRef(2)+=0.5*m_h.Get(2);
						m_world.m_particle_list.push_back(type_particle(keytemp));
					}
					if(b2)
					{
					 //Created particle at the two opposing edge.
						m_world.m_particle_list.push_back(type_particle(m_stag_pos.Get(it.key(),i)));
					    typename TypeWorld::type_key tempkey2=it.key();
						tempkey2.GetRef(i)+=1;
						//m_world.m_particle_list.push_back(type_particle(m_stag_pos.Get(tempkey2,i)));
					}
				 }
						
				}
			}
			 
		}
	}