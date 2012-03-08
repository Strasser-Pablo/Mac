/**
 * @file UpdateCellTypeAndLayer3.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer3.
 **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres):m_level(level),m_GetCellType(GetCellType),m_world(world),m_func_pres(func_pres),m_bound_set(m_O){
	
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Update()
{
	CalculateAirNeighbour();
	CleanSet();
	
	 std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> key)
	 {
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
			m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetAir());
		}
	 };
	for(iterator_map it=m_set.begin();it!=m_set.end();++it)
	{
		it->second.FillSet(f);
	}
	CreateLayer();
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::PrepareConstSpeed()
{

	CalculateAirNeighbour();
	CleanSet();
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CalculateAirNeighbour()
{
	m_nb_comp_con=1;
	typename TypeWorld::type_keytable::iterator it;
	 std::function<void(Physvector<type_dim,int>,int,int)> f=[&,&m_nb_comp_con](Physvector<type_dim,int> key,int i,int negsign)
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
			++m_nb_comp_con;
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
				for(int j=1;j<=type_dim;++j)
				{
					if(j==i)
					{
						continue;
					}
					int save_j=m_act.GetRef(j);
					m_act.GetRef(j)-=(2*abs(m_act.GetRef(j)%2)-1);
					if(m_bound_set.count(m_act)==0)
					{
						m_stack.push(m_act);
						m_bound_set.insert(m_act);
					};
					m_act.GetRef(j)=save_j;	
				}	
			}
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
		EraseIfIn(it2);
		++it;
	}
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CreateLayer()
{  
	 std::function<void(Physvector<type_dim,int>)> g=[&](Physvector<type_dim,int> key)
	 {
		 m_bound_set.erase(key);
	 };
	 std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> key)
	 {
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
			m_world.m_mac_grid[key].SetCellType(m_GetCellType.GetAirBoundary());
			m_world.m_mac_grid[key].SetLayer(1);
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
	for(int i=2;i<=m_level;++i){
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==i-1){
			NeighborsPhysvector<typename TypeWorld::type_key::type_data, TypeWorld::type_dim> N(it.key());
			typename TypeWorld::type_key neigh;
			while(N.GetNext(neigh)){
				m_world.m_mac_grid[neigh].GetLayer(layer);
				if(layer==-1)
				{
					m_world.m_mac_grid[neigh].SetCellType(m_GetCellType.GetAirBoundary());
					m_world.m_mac_grid[neigh].SetLayer(i);
					m_world.m_mac_grid[neigh].SetPressure(m_func_pres(neigh));
				}
			}
		}
	}
	}
}
