template<int DIM,class TypeData>
void Math_Set<DIM,TypeData>::Insert(Physvector<DIM,TypeData> & key)
{
	m_data[key.Get(1)].Insert(key,2);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set<DIM,TypeData>::Insert(Physvector<DIM2,TypeData> & key,int i)
{
	m_data[key.Get(i)].Insert(key,i+1);
}

template<int DIM,class TypeData>
void Math_Set<DIM,TypeData>::Get(Physvector<DIM-1,TypeData> & key,set<TypeData> &result)
{
	m_data[key.Get(1)].Get(key,2,result);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set<DIM,TypeData>::Get(Physvector<DIM2,TypeData> & key,int i,set<TypeData> &result)
{
	m_data[key.Get(i)].Get(key,i+1,result);
}

template<int DIM,class TypeData>
Rel_Ensemble Math_Set<DIM,TypeData>::IsIn(Math_Set<DIM,TypeData> & B)
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
	for(typename map<TypeData,Math_Set<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
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
Math_Set<1,TypeData>::Math_Set()
{
}

template<class TypeData>
void Math_Set<1,TypeData>::Insert(Physvector<1,TypeData> & key)
{
	Insert(key,1);
}

template<class TypeData>
template<int DIM2>
void Math_Set<1,TypeData>::Insert(Physvector<DIM2,TypeData> & key,int i)
{
	TypeData value=key.Get(i);
	if(m_interval.count(value+1)>0&&m_interval.count(value+2))
	{
		m_interval.erase(value+1);
		m_interval.insert(value);
	}
	else if(m_interval.count(value-1)>0&&m_interval.count(value-2))
	{
		m_interval.erase(value-1);
		m_interval.insert(value);
	}
	else if(m_interval.count(value+1)>0&&m_interval.count(value+2) &&m_interval.count(value-1)>0&&m_interval.count(value-2))
	{
		m_interval.erase(value+1);
		m_interval.erase(value-1);
	}
	else
	{
		m_interval.insert(value);
	}
}

template<class TypeData>
void Math_Set<1,TypeData>::Get(Physvector<1,TypeData> & key,set<TypeData> &result)
{
	result=m_interval;
}

template<class TypeData>
template<int DIM2>
void Math_Set<1,TypeData>::Get(Physvector<DIM2,TypeData> & key,int i,set<TypeData> &result)
{
	result=m_interval;
}


template<class TypeData>
Rel_Ensemble Math_Set<1,TypeData>::IsIn(Math_Set<1,TypeData> & B)
{
	if(m_interval.empty()&&B.m_interval.empty())
	{
		return Rel_Ensemble::Both_Empty;
	}
	if(m_interval.empty())
	{
		return Rel_Ensemble::A_Empty;
	}
	if(B.m_interval.empty())
	{
		return Rel_Ensemble::B_Empty;
	}
	if(B.m_interval.size()<=1||m_interval.size()<=1)
	{
		iterator it=B.m_interval.begin();
		throw logic_error("Is surface closed?");
	}
	iterator it=B.m_interval.begin();
	TypeData m_1=*it;
	++it;
	TypeData m_2=*it;
	int i=0;
	for(it=m_interval.begin();it!=m_interval.end();++it)
	{
		if(*it>m_1)
		{
			break;
		}
		++i;
	}
	if(it==m_interval.end())
	{
		return Rel_Ensemble::NONE;
	}
	if(i%2==0)
	{
		if(*it>m_2)
		{
			return Rel_Ensemble::NONE;
		}
		else
		{
			return Rel_Ensemble::A_In_B;
		}
	}
	else
	{
		return Rel_Ensemble::B_In_A;
	}
}
