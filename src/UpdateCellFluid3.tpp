/**
 * @file UpdateCellFluid.tpp
 * @brief
 * Implementation file for class UpdateCellFluid.
 **/
template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::UpdateCellFluid3(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos,TypeCondPart &condpart):m_world(world),m_to_key(_1_h,h),m_stag_pos(stag_pos),m_h(h),m_GetCellType(GetCellType),m_condpart(condpart)
{
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Update()
{
	m_set.clear();
	for(typename type_list_surface::iterator it=m_world.m_list_surface.begin();it!=m_world.m_list_surface.end();++it)
	{
		Physvector<type_dim,type_data> pos1;
		Physvector<type_dim,type_data> pos2;
		it->second.m_list.back()->GetPos(pos1);
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{	
			(*it2)->GetPos(pos2);
			Rafine(pos1,pos2,it2,it->second.m_list);
			pos1=pos2;
		}
	}


	for(typename type_list_surface::iterator it=m_world.m_list_surface.begin();it!=m_world.m_list_surface.end();++it)
	{
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{
			Physvector<type_dim,type_data> pos;
			(*it2)->GetPos(pos);
			Physvector<type_dim,int> key=m_to_key.ToKey(pos);
			m_world.m_mac_grid[key].SetLayer(0);
			m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetFluidBoundary());
		}
	}
	for(typename type_list_surface::iterator it=m_world.m_list_surface.begin();it!=m_world.m_list_surface.end();++it)
	{
		Physvector<type_dim,type_data> pos1;
		Physvector<type_dim,type_data> pos2;
		it->second.m_list.back()->GetPos(pos1);
		dir_exterior dir=it->second.m_dir;
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{
			(*it2)->GetPos(pos2);
			AddToSet(pos1,pos2,dir);
			pos1=pos2;
		}
	}
	assert(m_set.testBounded());
	m_set.CleanDouble();
	std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> key)
	{
		int lay;
		m_world.m_mac_grid[key].GetLayer(lay);
		if(lay==0)
		{
			return;
		}
		m_world.m_mac_grid[key].SetLayer(0);
		m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetFluid());
	};
	m_set.FillSet(f);
}


template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
	void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::AddToSet(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,dir_exterior dir)
{
	Physvector<type_dim,int> key1=m_to_key.ToKey(pos1);
	Physvector<type_dim,int> key2=m_to_key.ToKey(pos2);
	if(key1.Get(1)>key2.Get(1))
	{
		switch(dir)
		{
			case dir_exterior::LEFT:
				m_set.InsertMax(key1);
				m_set.InsertMax(key2);
			break;
			case dir_exterior::RIGHT:
				m_set.InsertMin(key1);
				m_set.InsertMin(key2);
			break;
		}
	}
	else if (key1.Get(1)<key2.Get(1))
	{
		switch(dir)
		{
			case dir_exterior::LEFT:
				m_set.InsertMin(key1);
				m_set.InsertMin(key2);
			break;
			case dir_exterior::RIGHT:
				m_set.InsertMax(key1);
				m_set.InsertMax(key2);
			break;
		}
	}
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
	void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Rafine(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,const typename type_list_surface_elem::iterator &it,type_list_surface_elem & list_surface)
{
	Physvector<type_dim,int> key1=m_to_key.ToKey(pos1);
	Physvector<type_dim,int> key2=m_to_key.ToKey(pos2);
	set<type_data> s;
	for(int i=1;i<=type_dim;++i)
	{
		type_data lambda;
		type_data lambdapart;
		int deb;
		int end;
		int si;
		if(key1.Get(i)>key2.Get(i))
		{
			end=key1.Get(i);
			deb=key2.Get(i);
			si=-1;
		}
		else
		{
			deb=key1.Get(i);
			end=key2.Get(i);
			si=1;
		}
		if(key1.Get(i)==key2.Get(i))
		{
			continue;
		}
		lambdapart=1/(pos2.Get(i)-pos1.Get(i));
		for(int j=deb;j<=end;++j)
		{
			lambda=lambdapart*((j+si*0.5)*m_h.Get(i)-pos1.Get(i));
			s.insert(lambda);
		}
	}
	type_data lambda=0;
	for(type_data lambda2 : s)
	{
		if(lambda!=0&&lambda2<=1)
		{
			Physvector<type_dim,type_data> pos;
			pos=pos1+0.5*(lambda+lambda2)*(pos2-pos1);	
			m_world.m_particle_list.push_back(type_particle(pos));
			type_particle* p=&m_world.m_particle_list.back();
			list_surface.insert(it,p);
		}
		lambda=lambda2;
	}
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::PrepareConst()
{
	int id=0;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int lay;
		it.data().GetLayer(lay);
		if(lay==-1)
		{
			for(int i=1;i<=type_dim;++i)
			{	
				std::function<void( Physvector<type_dim,int>,bool forwards)> f=[&](Physvector<type_dim,int> key,bool forwards)
				{

					int lay;
					m_world.m_mac_grid[key].GetLayer(lay);
					bool b;
					m_world.m_mac_grid[key].GetConstSpeed(i,b);
					int j=1;
					if(i==1)
					{
						j=2;
					}
					if(b)
					{
						if(lay==0&&forwards)
						{
							return;
						}
						if(forwards)
						{
							Physvector<type_dim,type_data> pos=m_stag_pos.Get(key,i);
							pos.GetRef(i)+=0.02*m_h.Get(i);
							m_world.m_particle_const_list.push_back(type_particle(pos));
							m_world.m_list_surface[id].m_list.push_back(&m_world.m_particle_const_list.back());
							m_world.m_mac_grid[key].SetLayer(0);
							m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetFluidBoundary());
							key.GetRef(j)+=1;
							f(key,forwards);
						}
						else
						{
							Physvector<type_dim,type_data> pos=m_stag_pos.Get(key,i);
							pos.GetRef(i)+=m_h.Get(i)*0.5;
							m_world.m_particle_list.push_back(type_particle(pos));
							m_world.m_list_surface[id].m_list.push_back(&m_world.m_particle_list.back());
							m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetFluidBoundary());
							key.GetRef(j)-=1;
							f(key,forwards);
						}
						return;
					}
					if(forwards)
					{
						key.GetRef(j)-=1;
					}
					else
					{
						key.GetRef(j)+=1;
					}
					f(key,!forwards);
				};
				bool b;
				it.data().GetConstSpeed(i,b);
				if(b)
				{
					m_world.m_list_surface[id].m_dir=dir_exterior::LEFT;
					f(it.key(),true);
					++id;
				}
			}
		}
	}
}
