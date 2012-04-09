/**
 * @file UpdateCellTypeAndLayer3.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer3.
 **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres,const Physvector<type_dim,type_data>& h,const Physvector<type_dim,type_data>& _1_h):m_level(level),m_GetCellType(GetCellType),m_world(world),m_func_pres(func_pres),m_bound_set(m_O),m_delete_cell(world),m_stat_out("top_res.txt",fstream::out),m_to_key(_1_h,h),m_h(h)
{
	m_i_out=0;	
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Update()
{
	++m_i_out;
	CalculateAirNeighbour();
	CleanSet();
	 std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> key)
	 {
		 // Erase Bound_Set so that we can find remaining air boundary (the Lateral one).
		m_bound_set.erase(key);
		for(int i=1;i<=type_dim;++i)
		{
			int cor=0;
			if(key.GetRef(i)%2==-1)
			{
				cor=-1;
			}
			key.GetRef(i)=key.GetRef(i)/2+cor;
		}
		int layer;
		m_world.m_mac_grid[key].GetLayer(layer);
		if(layer==-1)
		{	
			if(type_dim==2)
			{
				Physvector<type_dim,type_data> keytemp=m_to_key.FromKey(key);
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
				m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetFluid());
				m_world.m_mac_grid[key].SetLayer(0);
			}
		}
	 };
	for(iterator_map it=m_set.begin();it!=m_set.end();++it)
	{
		it->second.FillSet(f);
	}
	CreateLayer();
	//clean temp data.
	m_set.clear();
	m_bound_set.clear();
	m_nb_comp_con=0;
	m_delete_cell.Update();
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CalculateAirNeighbour()
{
	m_nb_comp_con=1;
	typename TypeWorld::type_keytable::iterator it;
	 std::function<void(Physvector<type_dim,int>,int,int)> f=[&](Physvector<type_dim,int> key,int i,int negsign)
	 {
		int layer;
		m_world.m_mac_grid[key].GetLayer(layer);
		if(layer==-1)
		{
			Physvector<type_dim,int> small_key=2*key;
			small_key.GetRef(i)+=negsign;
			if(m_bound_set.count(small_key)>0)
			{
				return;
			}
			m_bound_set.insert(small_key);
			if(i==type_dim)
			{
				// Insert Min, Max consistently.
				if(negsign==1)
				{
					m_set[m_nb_comp_con].InsertMin(small_key);
				}
				else
				{
					m_set[m_nb_comp_con].InsertMax(small_key);
				}
			}
			this->Follow(small_key,m_nb_comp_con);
			++this->m_nb_comp_con;
		}
	 };
	for(it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==0)
		{
			Physvector<type_dim,int> m_neigh=it.key();
			for(int i=1;i<=type_dim;++i)
			{
				m_neigh.GetRef(i)-=1;
				f(m_neigh,i,1);
				m_neigh.GetRef(i)+=2;
				f(m_neigh,i,0);
				m_neigh.GetRef(i)-=1;
			}
		}
	}
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Follow(Physvector<type_dim,int> & key,int id)
{
	stack<Physvector<type_dim,int> > m_stack;
	m_stack.push(key);
	Physvector<type_dim,int> m_act;
	while(!m_stack.empty())
	{
		m_act=m_stack.top();
		m_stack.pop();
		Physvector<type_dim,int> m_neigh;
		for(int i=1;i<=type_dim;++i)
		{
			m_neigh.GetRef(i)=m_act.GetRef(i)/2;
			// Correct the problem with negatif cell number (-1/2=0 --> we want -1)
			if(m_act.GetRef(i)<0&&(m_act.GetRef(i)%2!=0))
			{
				--m_neigh.GetRef(i);
			}
		}
		for(int i=1;i<=type_dim;++i)
		{
			int save_neigh=m_neigh.GetRef(i);
			int v_small=m_act.GetRef(i);
			int v_mod=v_small%2;
			if(v_mod==0)
			{
				m_neigh.GetRef(i)-=1;
			}
			else
			{
				m_neigh.GetRef(i)+=1;
			}
			int layer;
			m_world.m_mac_grid[m_neigh].GetLayer(layer);
			m_neigh.GetRef(i)=save_neigh;
			if(layer==0)
			{
				// We are at a Min/Max wall.
				if(i==type_dim)
				{
					if(v_mod==0)
					{	
						m_set[id].InsertMax(m_act);
					}
					else
					{
						m_set[id].InsertMin(m_act);
					}
				}
				// Consider other direction for lateral move.
				//
				// This consist to the following shematic:
				// A are Air cell.
				// F are Fluid cell.
				// CC is the current cell.
				// We move to the xx cell, because it maintain contact with the Fluid Cell.
				//
				//
				// 	     AAA
				//	xx|CCAAA
				//	FFFFF
				// 	FFFFF
				for(int j=1;j<=type_dim;++j)
				{
					if(j==i)
					{
						continue;
					}
					int save_j=m_act.GetRef(j);
					// Give the opposite sub cell in the lateral direction.
					// Because we have the two following case:
					//	abs(m_act.GetRef(j)%2)		correction
					//
					//	0				1	
					//	1				0
					m_act.GetRef(j)-=(2*abs(m_act.GetRef(j)%2)-1);
					if(m_bound_set.count(m_act)==0)
					{
						m_stack.push(m_act);
						m_bound_set.insert(m_act);
					};
					// Restore m_act
					m_act.GetRef(j)=save_j;	
				}	
			}
			//We have Air, We can move Forward.
			// This consist to the following shematic:
			// A are Air cell.
			// F are Fluid cell.
			// CC is the current cell.
			// We move to the xx cell, because we have air in it.
			//
			//
			// 	     AAA
			//	  |CCxxx
			//	FFFFF
			// 	FFFFF
		 	else
			{
				int save_i=m_act.GetRef(i);
				m_act.GetRef(i)+=(2*abs(m_act.GetRef(i)%2)-1);
				if(m_bound_set.count(m_act)==0)
				{
					m_stack.push(m_act);
					m_bound_set.insert(m_act);
				};	
				m_act.GetRef(i)=save_i;	
			}
			
		}
	}
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::EraseIfIn(iterator_map & it)
{
	for(iterator_map it2=m_set.begin();it2!=m_set.end();++it2)
	{
		if(it2==it)
		{
			continue;
		}
		if(it->second.IsIn(it2->second)==Rel_Ensemble::A_In_B)
		{
			m_set.erase(it);
			break;
		}
	}
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CleanSet()
{
	iterator_map it=m_set.begin();
	while(it!=m_set.end())
	{
		iterator_map it2=it;
		++it;
		EraseIfIn(it2);
	}
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CreateLayer()
{	
	 stack<Physvector<type_dim,int> > m_layer_stack;
	 std::function<void(Physvector<type_dim,int>)> g=[&](Physvector<type_dim,int> key)
	 {
		 m_bound_set.erase(key);
	 };
	 std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> key)
	 {
		 g(key);
		for(int i=1;i<=type_dim;++i)
		{
			int cor=0;
			if(key.GetRef(i)%2==-1)
			{
				cor=-1;
			}
			key.GetRef(i)=key.GetRef(i)/2+cor;
		}
			m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetAir());
			m_world.m_mac_grid[key].SetLayer(1);
			m_world.m_mac_grid[key].SetPressure(m_func_pres(key));
			m_layer_stack.push(key);
	 };
	for(iterator_map it=m_set.begin();it!=m_set.end();++it)
	{
		it->second.FillBoundary(f);	
	}
	g=[&](Physvector<type_dim,int> key)
	 {
	 };
	for(iterator_set it=m_bound_set.begin();it!=m_bound_set.end();++it)
	{
		f(*it);
	}
	stack<Physvector<type_dim,int> > m_layer_stack2;
	for(int i=2;i<=m_level;++i){
		Physvector<type_dim,int> m_key;
	while(!m_layer_stack.empty())
	{
		m_key=m_layer_stack.top();
		m_layer_stack.pop();
		int layer;
		m_world.m_mac_grid[m_key].GetLayer(layer);
		if(layer==i-1)
		{
			NeighborsPhysvector<typename TypeWorld::type_key::type_data, TypeWorld::type_dim> N(m_key);
			typename TypeWorld::type_key neigh;
			while(N.GetNext(neigh))
			{
				m_world.m_mac_grid[neigh].GetLayer(layer);
				if(layer==-1)
				{
					m_world.m_mac_grid[neigh].SetCellType(m_GetCellType.GetAir());
					m_world.m_mac_grid[neigh].SetLayer(i);
					m_world.m_mac_grid[neigh].SetPressure(m_func_pres(neigh));
					m_layer_stack2.push(neigh);
				}
			}
		}
	}
		m_layer_stack2.swap(m_layer_stack);
	}
}
