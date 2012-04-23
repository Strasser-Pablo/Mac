/**
 * @file UpdateCellFluid2.tpp
 * @brief
 * Implementation file for class UpdateCellFluid2.
 **/
template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
UpdateCellFluid2<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::UpdateCellFluid2(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos,TypeCondPart &condpart):m_world(world),m_to_key(_1_h,h),m_stag_pos(stag_pos),m_h(h),m_GetCellType(GetCellType),m_condpart(condpart)
{
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid2<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Update()
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
		m_world.m_mac_grid[tempkey].SetCellType(m_GetCellType.GetFluidBoundary());
	}
	stack<Physvector<type_dim,int> > m_key_add;
	stack<Physvector<type_dim,int> > m_key_bound;
	stack<Physvector<type_dim,int> > m_key_bound2;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		Physvector<type_dim,int> m_key;
		int lay;
		it.data().GetLayer(lay);
		if(lay==-1)
		{
			if(m_GetCellType.GetIsFluidOnly(it.key()))
			{
				m_key_add.push(it.key());
			}
			else if(m_GetCellType.GetIsBoundaryFluid(it.key()))
			{
				//Test if one component is constant speed.
				bool b=false;
				bool b3=false;
				Physvector<type_dim,int> temp=it.key();
				for(int i=1;i<=type_dim;++i)
				{
					bool b2;
					it.data().GetConstSpeed(i,b2);
					b3=b3||b2;
					if(b2)
					{
						type_data dtemp;
						it.data().GetInterSpeed(i,dtemp);
						if(dtemp>0)
						{
							temp.GetRef(i)+=1;
							if(m_GetCellType.GetIsFluid(temp))
							{
								b2=false;	
							}
							temp.GetRef(i)-=1;
						}
						else
						{
							temp.GetRef(i)-=1;
							if(m_GetCellType.GetIsFluid(temp))
							{
								b2=false;	
							}
							temp.GetRef(i)+=1;
						}
					}
					b=b||b2;
				}
				//ok one component is constant speed.
				if(b)
				{
					CreatePart(it.key());
				}
				else if(b3)
				{
					it.data().SetLayer(0);
				}
				else if(!b3)
				{
					for(int i=1;i<=type_dim;++i)
					{
						bool b2;
						type_data dtemp;
						it.data().GetInterSpeed(i,dtemp);
						if(dtemp<0)
						{
							temp.GetRef(i)+=1;
							if(m_GetCellType.GetIsFluid(temp))
							{
								b2=true;	
							}
							temp.GetRef(i)-=1;
						}
						else
						{
							temp.GetRef(i)-=1;
							if(m_GetCellType.GetIsFluid(temp))
							{
								b2=true;	
							}
							temp.GetRef(i)+=1;
						}
						b=b||b2;
					}
					if(b)
					{
						CreatePart(it.key());
					}
					else
					{
						m_key_bound2.push(it.key());
					}
				}
			}
		}
		else if(m_GetCellType.GetIsBoundaryFluid(it.key()))
		{
			m_key_bound.push(it.key());
		}

	}
	Physvector<type_dim,int> m_key;
	while(!m_key_add.empty())
	{
		m_key=m_key_add.top();
		m_key_add.pop();
		m_world.m_mac_grid[m_key].SetLayer(0);
		m_world.m_mac_grid[m_key].SetCellType(m_GetCellType.GetFluid());
	}

	while(!m_key_bound.empty())
	{
		m_key=m_key_bound.top();
		m_key_bound.pop();
		NeighborsDiagPhysvector<int,type_dim> neigh(m_key);
		Physvector<type_dim,int> m_neigh;
		bool b=true;
		while(neigh.GetNext(m_neigh))
		{
			if(!m_world.m_mac_grid.Exist(m_neigh))
			{
				b=false;
				break;
			}
			int lay;
			m_world.m_mac_grid[m_neigh].GetLayer(lay);
			if(lay!=0)
			{
				b=false;
				break;
			}
		}
		if(b)
		{
			m_world.m_mac_grid[m_key].SetCellType(m_GetCellType.GetFluid());
			m_world.m_mac_grid[m_key].SetLayer(0);
		}
	}
	while(!m_key_bound2.empty())
	{
		m_key=m_key_bound2.top();
		m_key_bound2.pop();
		NeighborsDiagPhysvector<int,type_dim> neigh(m_key);
		Physvector<type_dim,int> m_neigh;
		bool b=true;
		while(neigh.GetNext(m_neigh))
		{
			if(m_GetCellType.GetIsAir(m_neigh))
			{
				b=false;
				break;
			}
		}
		if(b)
		{
			m_world.m_mac_grid[m_key].SetCellType(m_GetCellType.GetFluid());
			m_world.m_mac_grid[m_key].SetLayer(0);
		}
		else
		{
			m_world.m_mac_grid[m_key].SetCellType(m_GetCellType.GetAir());
			m_world.m_mac_grid[m_key].SetLayer(-1);
		}
	}
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid2<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::CreatePart(const Physvector<type_dim,int> & key)
{
	//Test witch direction is constant.
	if(type_dim==2)
	{
		Physvector<type_dim,type_data> keytemp=m_to_key.FromKey(key);
		m_world.m_particle_list.push_back(type_particle(keytemp));
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
		m_world.m_mac_grid[key].SetLayer(0);
	}
}
