/**
 * @file UpdateCellFluid.tpp
 * @brief
 * Implementation file for class UpdateCellFluid.
 **/
template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::UpdateCellFluid3(TypeWorld & world,const Physvector<type_dim,type_data>& _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos,TypeCondPart &condpart):m_world(world),m_to_key(_1_h,h),m_stag_pos(stag_pos),m_h(h),m_GetCellType(GetCellType),m_condpart(condpart),m_trav(30,m_hash),m_plein(30,m_hash),m_key_seg_list(30,m_hash),m_1_h(_1_h)
{
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Update()
{
	m_inter_map.clear();
	m_id_inter_map.clear();
	m_key_seg_list.clear();
	m_set.clear();
	m_trav.clear();
	m_plein.clear();
	struct tms m_time_deb;
	struct tms m_time_end;
	long m_time_ticks_deb;
	long m_time_ticks_end;
	double m_conv_time=double(sysconf(_SC_CLK_TCK));
	m_time_ticks_deb=times(&m_time_deb);
	for(typename type_list_surface::iterator it=m_world.m_list_surface.begin();it!=m_world.m_list_surface.end();++it)
	{
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{
			Physvector<type_dim,type_data> pos;
			(*it2)->GetPos(pos);
			if(m_condpart(m_to_key.ToKey(pos)))
			{
				(*it2)->SetToErase(true);
				it2=it->second.m_list.erase(it2);
			}
		}
	}
	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 1 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
	m_time_ticks_deb=times(&m_time_deb);
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
		Physvector<type_dim,type_data> pos1;
		Physvector<type_dim,type_data> pos2;
		int id= it->first;
		it->second.m_list.back()->GetPos(pos1);
		typename type_list_surface_elem::iterator it3=--it->second.m_list.end();
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{	
			(*it2)->GetPos(pos2);
			AddToSegment(it3,it2,pos1,pos2,id);
			it3=it2;
			pos1=pos2;
		}
	}

	for(type_key_id_list_seg_iterator it=m_key_seg_list.begin();it!=m_key_seg_list.end();++it)
	{
		for(type_id_list_seg_iterator it2=it->second.begin();it2!=it->second.end();++it2)
		{
			int id1=it2->first;
			for(type_id_list_seg_iterator it3=it->second.begin();it3!=it->second.end();++it3)
			{
				int id2=it2->first;
				for(type_list_seg_iterator it4=it2->second.begin();it4!=it2->second.end();++it4)
				{
					for(type_list_seg_iterator it5=id1==id2?it4:it3->second.begin();it5!=it3->second.end();++it5)
					{
						if(it5==it4)
						{
							continue;
						}
						DoElemIntersectProcessing(*it4,*it5,id1,id2);
					}
				}
			}
		}

	}

	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 2 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	for(typename type_list_surface::iterator it=m_world.m_list_surface.begin();it!=m_world.m_list_surface.end();++it)
	{
		Physvector<type_dim,type_data> pos1;
		Physvector<type_dim,type_data> pos2;
		it->second.m_list.back()->GetPos(pos1);
		int mode=2;
		type_data keyx;
		bool bcontend=false;
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{	
			(*it2)->GetPos(pos2);
			CountTrav(pos1,pos2,it->second.m_dir,mode,keyx,bcontend);
			pos1=pos2;
		}
		bcontend=true;
		for(typename type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{	
			(*it2)->GetPos(pos2);
			CountTrav(pos1,pos2,it->second.m_dir,mode,keyx,bcontend);
			if(!bcontend)
			{
				break;
			}
			pos1=pos2;
		}

	}

	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 3 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	bool b=false;
	for(typename unordered_map<Physvector<type_dim,int>, int,Hash>::iterator it=m_trav.begin();it!=m_trav.end();++it)
	{
		switch(it->second)
		{
			case 0:
				if(m_plein[it->first])
				{
					m_set.InsertMin(it->first);
					m_set.InsertMax(it->first);
				}
				break;
			case 1:
					m_set.InsertMin(it->first);
				break;
			case -1:
					m_set.InsertMax(it->first);
				break;
			default:
				cout<<"it second wront value "<<it->second<<endl;
				cout<<"it first "<<it->first<<endl;
				b=true;
				break;
		}
	}
	if(b)
	{
		abort();
	}

	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 4 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
	m_time_ticks_deb=times(&m_time_deb);

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

	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 5 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	//m_set.CoutDebInfo();
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

	m_time_ticks_end=times(&m_time_end);
	cout<<"timing end 6 "<<(m_time_ticks_end-m_time_ticks_deb)/m_conv_time<<endl;
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
	void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::CountTrav(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,dir_exterior dir,int &mode,double &keyx,bool &bcontend)
{

	Physvector<type_dim,int> key1=m_to_key.ToKey(pos1);
	Physvector<type_dim,int> key2=m_to_key.ToKey(pos2);
	type_data posmin=pos1.Get(1);
	type_data posmax=pos2.Get(1);
	type_data eps=0.001*m_h.Get(1);
	if(mode==2)
	{
		keyx=pos1.Get(1);
		mode=3;
	}
		
	if(posmin>posmax)
	{
		swap(posmin,posmax);
	}
	bool b3=true;
	bool b4=true;
	if(mode==3)
	{
		b3=abs(keyx-posmin)>eps;
		b4=abs(keyx-posmax)>eps;
		if(b3||b4)
		{
			mode=0;
		}
	}
	int si=1;
	if(key1.Get(1)>key2.Get(1))
	{
		si=-1;
	}
	type_data lambda_part=1/(pos2.Get(1)-pos1.Get(1));
	for(int i=key1.Get(1);(si==1&&i<=key2.Get(1))||(si==-1&&i>=key2.Get(1));i+=si)
	{
		type_data lambda=(i*m_h.Get(1)-pos1.Get(1))*lambda_part;
		Round<type_data,int> R;
		Physvector<type_dim,type_data> pos=pos1+lambda*(pos2-pos1);
		for(int j=1;j<=2;++j)
		{
			pos.GetRef(j)*=m_1_h.Get(j);
			key1.GetRef(j)=R(pos.GetRef(j));
		}
		//Pass throught the line of width eps. We have no Numerical Analysis Heissenberg incertitude.
		bool b1=b4&&i*m_h.Get(1)-posmin>eps;
		bool b2=b3&&posmax-i*m_h.Get(1)>eps;
		bool b5=b3&&abs(posmin-i*m_h.Get(1))<eps;
		bool b6=b4&&abs(posmax-i*m_h.Get(1))<eps;
		if(b1&&b2&&mode==0)
		{
			if(m_trav.count(key1)==0)
			{
				m_trav[key1]=0;
				m_plein[key1]=false;
			}
			if(pos1.Get(1)<pos2.Get(1))
			{
				switch(dir)
				{
					case dir_exterior::LEFT:
						m_trav[key1]+=1;
						m_plein[key1]=true;
					break;
					case dir_exterior::RIGHT:
						m_trav[key1]-=1;
						m_plein[key1]=true;
					break;
				}
			}
			else if(pos1.Get(1)>pos2.Get(1))
			{
				switch(dir)
				{
					case dir_exterior::LEFT:
						m_trav[key1]-=1;
						m_plein[key1]=true;
					break;
					case dir_exterior::RIGHT:
						m_trav[key1]+=1;
						m_plein[key1]=true;
					break;
				}
			}
			if(bcontend)
			{
				bcontend=false;
				return;
			}
		}
		else if(b5&&b6)
		{
		}
		else if(b6&&mode==0)
		{
			mode=1;
		}
		else if(b5&&mode==0)
		{
			mode=-1;
		}
		else if(b6&&mode==-1)
		{
			if(m_trav.count(key1)==0)
			{
				m_trav[key1]=0;
				m_plein[key1]=false;
			}
			switch(dir)
			{
				case dir_exterior::LEFT:
					m_trav[key1]-=1;
					m_plein[key1]=true;
				break;
				case dir_exterior::RIGHT:
					m_trav[key1]+=1;
					m_plein[key1]=true;
				break;
			}
			mode=0;
			if(bcontend)
			{
				bcontend=false;
				return;
			}
		}
		else if(b5&&mode==1)
		{
			if(m_trav.count(key1)==0)
			{
				m_trav[key1]=0;
				m_plein[key1]=false;
			}
			switch(dir)
			{
				case dir_exterior::LEFT:
					m_trav[key1]+=1;
					m_plein[key1]=true;
				break;
				case dir_exterior::RIGHT:
					m_trav[key1]-=1;
					m_plein[key1]=true;
				break;
			}
			mode=0;
			if(bcontend)
			{
				bcontend=false;
				return;
			}
		}
		else if(b6&&mode==1)
		{
			mode=0;
		}
		else if(b5&&mode==-1)
		{
			mode=0;
		}
		else
		{
		}
	}
	
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
	void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::AddToSet(const typename type_list_surface_elem::iterator & it,type_list_surface_elem & list_surface,dir_exterior dir)
{
	typename type_list_surface_elem::iterator itbef=it;
	typename type_list_surface_elem::iterator itaft=it;
	if(itbef==list_surface.begin())
	{
		itbef=--list_surface.end();
	}
	else
	{
		--itbef;
	}
	++itaft;
	if(itaft==list_surface.end())
	{
		itaft=list_surface.begin();
	}
	Physvector<type_dim,type_data> pos;
	(*it)->GetPos(pos);
	Physvector<type_dim,type_data> posaft;
	(*itaft)->GetPos(posaft);
	Physvector<type_dim,type_data> posbef;
	(*itbef)->GetPos(posbef);
	Physvector<type_dim,int> key=m_to_key.ToKey(pos);
	Physvector<type_dim,int> keyaft=m_to_key.ToKey(posaft);
	Physvector<type_dim,int> keybef=m_to_key.ToKey(posbef);
	Physvector<type_dim,type_data> pos2;
	if((key.Get(1)-keyaft.Get(1))*(keybef.Get(1)-key.Get(1))<0)
	{
		return;
	}
	bool b=false;
	bool b2=false;
	if(key.Get(1)>keyaft.Get(1))
	{
		pos2=posaft;
		b=true;
	}
	if(keybef.Get(1)>key.Get(1))
	{
		pos2=posbef;
		b=true;
	}
	if(key.Get(1)<keyaft.Get(1))
	{
		pos2=posaft;
		b2=true;
	}
	if(keybef.Get(1)<key.Get(1))
	{
		pos2=posbef;
		b2=true;
	}
	type_data lambdapart=1/(pos2.Get(1)-pos.Get(1));
	type_data lambda=lambdapart*(key.Get(1)*m_h.Get(1)-pos.Get(1));
	pos+=lambda*(pos2-pos);	
	if(b)
	{
		switch(dir)
		{
			case dir_exterior::LEFT:
				m_set2.InsertMax(key,pos);
			break;
			case dir_exterior::RIGHT:
				m_set2.InsertMin(key,pos);
			break;
		}
	}
	else if (b2)
	{
		switch(dir)
		{
			case dir_exterior::LEFT:
				m_set2.InsertMin(key,pos);
			break;
			case dir_exterior::RIGHT:
				m_set2.InsertMax(key,pos);
			break;
		}
	}
}

template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
	void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::Rafine(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,typename type_list_surface_elem::iterator &it2,type_list_surface_elem & list_surface)
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
			list_surface.insert(it2,p);
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



template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::AddToSegment(typename type_list_surface_elem::iterator & it1,typename type_list_surface_elem::iterator &it2,const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,int id)
{
	Physvector<type_dim,int> key1=m_to_key.ToKey(pos1);
	Physvector<type_dim,int> key2=m_to_key.ToKey(pos2);
	type_seg seg(it1,it2);
	m_key_seg_list[key1][id].push_back(seg);
	m_key_seg_list[key2][id].push_back(seg);
}


template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
bool UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::CalculateIntersection(const Physvector<type_dim,type_data>&  pos1,const Physvector<type_dim,type_data> & pos2,const Physvector<type_dim,type_data>&  pos3,const Physvector<type_dim,type_data>&  pos4,Physvector<type_dim,type_data> & pos)
{
	type_data r;
	type_data s;
	type_data d;
	type_data _1_d;
	d=(pos2.Get(1)-pos1.Get(1))*(pos4.Get(2)-pos3.Get(2))-(pos2.Get(2)-pos1.Get(2))*(pos4.Get(1)-pos3.Get(1));
	_1_d=1/d;	
	r=_1_d*((pos1.Get(2)-pos3.Get(2))*(pos4.Get(1)-pos3.Get(1))-(pos1.Get(1)-pos3.Get(1))*(pos4.Get(2)-pos3.Get(2)));
	s=_1_d*((pos1.Get(2)-pos3.Get(2))*(pos2.Get(1)-pos1.Get(1))-(pos1.Get(1)-pos3.Get(1))*(pos2.Get(2)-pos1.Get(2)));
	if(r>=1 || s>=1 ||s<=0 || r<=0 ||std::isnan(r)||std::isnan(s))
	{
		return false;
	}
	pos.GetRef(1)=pos1.Get(1)+r*(pos2.Get(1)-pos1.Get(1));
	pos.GetRef(2)=pos1.Get(2)+r*(pos2.Get(2)-pos1.Get(2));
	return true;
}



template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
void UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart>::DoElemIntersectProcessing(type_seg & seg1,type_seg & seg2,int id1,int id2)
{
	Physvector<type_dim,type_data> pos1;
	(*seg1.first)->GetPos(pos1);
	Physvector<type_dim,type_data> pos2;
	(*seg1.second)->GetPos(pos2);
	Physvector<type_dim,type_data> pos3;
	(*seg2.first)->GetPos(pos3);
	Physvector<type_dim,type_data> pos4;
	(*seg2.second)->GetPos(pos4);
	Physvector<type_dim,type_data> pos;
	bool b=CalculateIntersection(pos1,pos2,pos3,pos4,pos);
	if(!b)
	{
		return;
	}

	type_unord_id_pair_to_inter_iterator it=m_inter_map.insert(typename type_unord_id_pair_to_inter::value_type(type_id_pair(id1,id2),type_inter(type_seg_pair(seg1,seg2),pos)));
	Intersection_Iterator_List inter1;
	inter1.m_intersection=it;
	type_intersection_list_iterator it2=m_id_inter_map[id1].insert(m_id_inter_map[id1].end(),inter1);

	Intersection_Iterator_List inter2;
	inter2.m_intersection=it;
	type_intersection_list_iterator it3=m_id_inter_map[id2].insert(m_id_inter_map[id2].end(),inter2);

	it2->m_other=new type_intersection_list_iterator;
	*(it2->m_other)=it3;
	it3->m_other=new type_intersection_list_iterator;
	*(it3->m_other)=it2;
}
