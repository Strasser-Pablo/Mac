/**
 * @file UpdateCellFluid.tpp
 * @brief
 * Implementation file for class UpdateCellFluid.
 **/
template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
UpdateCellFluid<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::UpdateCellFluid(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos,TypeCondPart &condpart):m_world(world),m_to_key(_1_h,h),m_GetCellType(GetCellType),m_stag_pos(stag_pos),m_condpart(condpart),m_h(h)
{
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Update()
{
	typename TypeWorld::type_key tempkey;
	for(typename TypeWorld::type_tablecontainer::iterator it= m_world.m_particle_list.begin();it!=m_world.m_particle_list.end();++it)
	{
		Physvector<type_dim,type_data> pos;
		(*it).GetPos(pos);
		tempkey=m_to_key.ToKey(*it);
		if(m_condpart(tempkey))
		{
			it=m_world.m_particle_list.erase(it);
			continue;
		}
		m_world.m_mac_grid[tempkey].SetLayer(0);
		m_world.m_mac_grid[tempkey].SetCellType(m_GetCellType.GetFluid());
	}
	stack<Physvector<type_dim,int> > m_key_add;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int lay;
		it.data().GetLayer(lay);
		if(lay==-1)
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
				 m_key_add.push(it.key());
				 
				 for(int i=1;i<=type_dim;++i)
				 {
					 //Test witch direction is constant.
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
				 }
						
				}
			}
			 
		}
		Physvector<type_dim,int> m_key;
		while(!m_key_add.empty())
		{
			m_key=m_key_add.top();
			m_key_add.pop();
			m_world.m_particle_list.push_back(type_particle(m_to_key.FromKey(m_key)));
			m_world.m_mac_grid[m_key].SetLayer(0);
			m_world.m_mac_grid[m_key].SetCellType(m_GetCellType.GetFluid());
		}
	}
