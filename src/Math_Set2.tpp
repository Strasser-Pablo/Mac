template<int DIM,class TypeData>
void Math_Set2<DIM,TypeData>::InsertMax(Physvector<DIM,TypeData> & key)
{
	m_data[key.Get(1)].InsertMax(key,2);
}

template<int DIM,class TypeData>
void Math_Set2<DIM,TypeData>::InsertMin(Physvector<DIM,TypeData> & key)
{
	m_data[key.Get(1)].InsertMax(key,2);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set2<DIM,TypeData>::InsertMax(Physvector<DIM2,TypeData> & key,int i)
{
	m_data[key.Get(i)].InsertMax(key,i+1);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set2<DIM,TypeData>::InsertMin(Physvector<DIM2,TypeData> & key,int i)
{
	m_data[key.Get(i)].InsertMin(key,i+1);
}

template<int DIM,class TypeData>
Rel_Ensemble Math_Set2<DIM,TypeData>::IsIn(Math_Set2<DIM,TypeData> & B)
{
	cout<<"DIM "<<DIM<<endl;
	
	if(m_data.empty()&&B.m_data.empty())
	{
		return Rel_Ensemble::Both_Empty;
	}
	if(m_data.empty())
	{
		return Rel_Ensemble::A_Empty;
	}
	
	if(B.m_data.empty())
	{
		return Rel_Ensemble::B_Empty;
	}
	bool b_A_empty=false;
	bool b_B_empty=false;
	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		Rel_Ensemble res=it->second.IsIn(B.m_data[it->first]);
		switch(res)
		{
			case Rel_Ensemble::A_In_B:
				if(b_B_empty)
				{
					throw logic_error("Is surface closed?");
				}
				return Rel_Ensemble::A_In_B;
			break;
			case Rel_Ensemble::B_In_A:
				if(b_A_empty)
				{
					throw logic_error("Is surface closed?");
				}
				return Rel_Ensemble::B_In_A;
			break;
			case Rel_Ensemble::A_Empty:
				b_A_empty=true;
			break;
			case Rel_Ensemble::B_Empty:
				b_B_empty=true;
			break;
			case Rel_Ensemble::Both_Empty:
				b_A_empty=true;
				b_B_empty=true;
			break;
			case Rel_Ensemble::NONE:
				return Rel_Ensemble::NONE;
			break;
		}
	}
	//Return none because if it is in a set, one of the 1d set
	//will have return the 1d set.
	//if empty will have returned.
	//A none can be there if the projection whith the thirth component,
	//doesn't intersect. Only element of set A will be iterated.
	//And B will always be empty (in the element iterated.
	return Rel_Ensemble::NONE;
}

template<class TypeData>
Math_Set2<1,TypeData>::Math_Set2()
{
}

template<class TypeData>
void Math_Set2<1,TypeData>::InsertMin(Physvector<1,TypeData> & key)
{
	InsertMin(key,1);
}

template<class TypeData>
void Math_Set2<1,TypeData>::InsertMax(Physvector<1,TypeData> & key)
{
	InsertMax(key,1);
}

template<class TypeData>
template<int DIM2>
void Math_Set2<1,TypeData>::InsertMin(Physvector<DIM2,TypeData> & key,int i)
{
	m_inter_min.insert(key.Get(i));
}

template<class TypeData>
template<int DIM2>
void Math_Set2<1,TypeData>::InsertMax(Physvector<DIM2,TypeData> & key,int i)
{
	m_inter_max.insert(key.Get(i));
}

template<class TypeData>
Rel_Ensemble Math_Set2<1,TypeData>::IsIn(Math_Set2<1,TypeData> & B)
{
	if(m_inter_max.empty()&&m_inter_min.empty()&&B.m_inter_max.empty()&&B.m_inter_min.empty())
	{
		return Rel_Ensemble::Both_Empty;
	}
	if(m_inter_max.empty()&&m_inter_min.empty())
	{
		return Rel_Ensemble::A_Empty;
	}
	if(B.m_inter_max.empty()&&B.m_inter_min.empty())
	{
		return Rel_Ensemble::B_Empty;
	}
	iterator it_min=B.m_inter_min.begin();
	iterator it_max=B.m_inter_max.begin();
	iterator it_min_lb=m_inter_min.lower_bound(*it_min);
	iterator it_max_lb=m_inter_min.lower_bound(*it_max);
	if(it_min_lb!=it_max_lb)
	{
		return Rel_Ensemble::A_In_B;
	}
	if(it_min_lb==m_inter_min.begin()&&it_max_lb==m_inter_min.begin())
	{
		iterator it_min_lb2=B.m_inter_min.lower_bound(*it_min_lb);
		iterator it_max_lb2=B.m_inter_max.lower_bound(*it_min_lb);
		if(it_max_lb2==B.m_inter_max.end())
		{
			return Rel_Ensemble::NONE;
		}
		if(it_min_lb2==B.m_inter_min.end())
		{
			return Rel_Ensemble::A_In_B;
		}
		if(*it_max_lb2<*it_min_lb2)
		{
			return Rel_Ensemble::A_In_B;
		}
		return Rel_Ensemble::NONE;
	}
	iterator it_min_up=m_inter_max.lower_bound(*it_min);
	iterator it_max_up=m_inter_max.lower_bound(*it_max);
	if(it_min_lb==m_inter_min.end()&&it_min_up==m_inter_max.end())
	{
		return Rel_Ensemble::NONE;
	}
	if(it_min_lb==m_inter_min.end())
	{
		return Rel_Ensemble::B_In_A;
	}
	assert(it_max_lb!=m_inter_min.end());
	assert(it_min_up!=m_inter_max.end());
	assert(it_max_up!=m_inter_max.end());
	if(it_min_up==m_inter_max.begin()&&*it_min_up>*it_max)
	{
		return Rel_Ensemble::B_In_A;
	}
	if(*it_min_lb>*it_min_up)
	{
		return Rel_Ensemble::B_In_A;
	}
	else
	{
		return Rel_Ensemble::NONE;
	}
	assert(1!=1);
}
