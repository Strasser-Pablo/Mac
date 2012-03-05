/**
 * @file UpdateCellTypeAndLayer3.tpp
 * @brief
 * Implementation file for class UpdateCellTypeAndLayer.
 **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres):m_level(level),m_GetCellType(GetCellType),m_world(world),m_func_pres(func_pres),m_bound_set(m_O){
	
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Update()
{
	CalculateAirNeighbour();
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::PrepareConstSpeed()
{

	CalculateAirNeighbour();
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::CalculateAirNeighbour()
{
	m_nb_comp_con=1;
	Physvector<type_dim,int> neigh;
	neigh.SetAll(0);
	typename TypeWorld::type_keytable::iterator it;
	std::function<void(Physvector<type_dim,int>)> f=[&,&m_nb_comp_con,this](Physvector<type_dim,int> k)
	{
		Physvector<type_dim,int> key=it.key()+k;
		this->Follow(key,m_nb_comp_con);
		++m_nb_comp_con;
	};
	int max=1;
	NDFor<std::function<void(Physvector<type_dim,int>)>,int,type_dim> m_For(neigh,max,f);
	for(it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		int layer;
		it.data().GetLayer(layer);
		if(layer==0)
		{
			m_For.Calculate();
		}
	}
	cout<<m_nb_comp_con<<endl;
	cout<<m_set.size()<<endl;
}

template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
void UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::Follow(Physvector<type_dim,int> & key,int id)
{
	cout<<"enter "<<endl;
	stack<Physvector<type_dim,int> > m_stack;
	m_stack.push(key);
	Physvector<type_dim,int> m_act;
	while(!m_stack.empty())
	{
		m_act=m_stack.top();
		m_stack.pop();
		cout<<"m_act "<<m_act<<endl;
		Physvector<type_dim,int> m_neigh;
		NeighborsPhysvector<int,type_dim> NV(m_act);
		while(NV.GetNext(m_neigh))
		{
			cout<<"neigh to test "<<m_neigh<<endl;
			if(IsConnected(m_act,m_neigh))
			{
				cout<<"con "<<endl;
				m_set[id].Insert(m_neigh);
				if(m_bound_set.count(m_neigh)==0)
				{
					cout<<"ok don't exist"<<endl;
					m_stack.push(m_neigh);
					m_bound_set.insert(m_neigh);
				}
			}
		}
	}
	cout<<"end "<<endl;
}


template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
bool UpdateCellTypeAndLayer3<TypeWorld,TypeGetCellType,TypeFunctionPressure>::IsConnected(Physvector<type_dim,int> & keyA,Physvector<type_dim,int> & keyB)
{
	Physvector<type_dim,int> dist=keyB-keyA;
	int i;
	bool bpos=true;
	for(i=1;i<=type_dim;++i)
	{
		if(dist.Get(i)!=0)
		{
			if(dist.Get(i)<0)
			{
				bpos=false;
			}
			break;
		}
	}
	cout<<"bpos "<<bpos<<endl;
	Physvector<type_dim,int>&  keycomp=bpos ? keyA : keyB ;
	cout<<"i "<<i<<endl;
	Physvector<type_dim,int> m_neigh;
	m_neigh.SetAll(0);
	bool b=false;
	bool b2=true;
	std::function<void(Physvector<type_dim,int>)> f=[&](Physvector<type_dim,int> k)
	{
		if(k.Get(i)==0)
		{
			int layer;
			m_world.m_mac_grid[keycomp+k].GetLayer(layer);
			Physvector<type_dim,int> temp=keycomp+k;
			cout<<"k "<<k<<endl;
			cout<<"kcomp "<<keycomp<<endl;
			cout<<"key+k "<<temp<<" "<<layer<<endl;
			b=b||(layer==-1);
			b2=b2&&(layer==-1);
		}
		else
		{
			cout<<"i skip"<<endl;
		}
	};
	int min=-1;
	NDForMin<std::function<void(Physvector<type_dim,int>)>,int,type_dim> m_For(m_neigh,min,f);
	m_For.Calculate();
	cout<<"b "<<b<<endl;
	cout<<"b2 "<<b2<<endl;
	return b&&!b2;
}