template<int DIM,class TypeData,class TypeData2,int DIM2>
Math_Set3<DIM,TypeData,TypeData2,DIM2>::Math_Set3(const Physvector<DIM2,TypeData2> & _1_h):m_1_h(_1_h)
{

}

template<class TypeData,class TypeData2,int DIM2>
Math_Set3<1,TypeData,TypeData2,DIM2>::Math_Set3(const Physvector<DIM2,TypeData2> & _1_h):m_1_h(_1_h)
{

}

template<int DIM,class TypeData,class TypeData2,int DIM2>
Math_Set3<DIM,TypeData,TypeData2,DIM2>::Math_Set3():m_1_h(Physvector<DIM2,TypeData2>())
{

}

template<class TypeData,class TypeData2,int DIM2>
Math_Set3<1,TypeData,TypeData2,DIM2>::Math_Set3():m_1_h(Physvector<DIM2,TypeData2>())
{

}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::ConvertSub(Physvector<DIM2,TypeData> &key,Math_Set2<DIM2,TypeData> & math_set,int i)
{
	for(typename map_set::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		key.Set(i,it->first);
		cout<<"convertsub "<<it->first<<endl;
		it->second.ConvertSub(key,math_set,i+1);
	}
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::ConvertSub(Physvector<DIM2,TypeData> &key,Math_Set2<DIM2,TypeData> & math_set,int i)
{
	multimap<TypeData,TypeData2> m_inter_min2;
	multimap<TypeData,TypeData2> m_inter_max2;
	set<TypeData> m_inter_min3;
	set<TypeData> m_inter_max3;
	set<TypeData> m_set;
	cout<<"create m_inter_min2"<<endl;
	typedef typename multimap<TypeData,TypeData2>::value_type pair_multi; 
	for(typename set<TypeData2>::iterator it=m_inter_min.begin();it!=m_inter_min.end();++it)
	{
		TypeData2 temp=*it*m_1_h.Get(i);
		m_inter_min2.insert(pair_multi(m_R(temp),*it));
		m_set.insert(m_R(temp));
	}

	cout<<"create m_inter_max2"<<endl;
	for(typename set<TypeData2>::iterator it=m_inter_max.begin();it!=m_inter_max.end();++it)
	{
		TypeData2 temp=*it*m_1_h.Get(i);
		m_inter_max2.insert(pair_multi(m_R(temp),*it));
		m_set.insert(m_R(temp));
	}
cout<<"first part done "<<endl;
	typedef pair<typename multimap<TypeData,TypeData2>::iterator,typename map<TypeData,TypeData2>::iterator> type_pair;

	for(typename set<TypeData>::iterator it=m_set.begin();it!=m_set.end();++it)
	{
		type_pair range_min=m_inter_min2.equal_range(*it);
		type_pair range_max=m_inter_max2.equal_range(*it);
		cout<<"min"<<endl;
		for(typename map<TypeData,TypeData2>::iterator it_deb_1=range_min.first; it_deb_1!=range_min.second;++it_deb_1)
		{
			cout<<it_deb_1->first<<" "<<it_deb_1->second<<endl;
		}
		cout<<"max"<<endl;
		for(typename map<TypeData,TypeData2>::iterator it_deb_2=range_max.first; it_deb_2!=range_max.second;++it_deb_2)
		{
			cout<<it_deb_2->first<<" "<<it_deb_2->second<<endl;
		}
		cout<<"end"<<endl;
		if(range_min.first==range_min.second&&range_max.first!=range_max.second)
		{
			m_inter_max3.insert(*it);
			cout<<"inter_max "<<*it<<endl;
		}
		if(range_max.first==range_max.second&&range_min.first!=range_min.second)
		{
			m_inter_min3.insert(*it);
			cout<<"inter_min "<<*it<<endl;
		}
		if(range_max.first!=range_max.second&&range_min.first!=range_min.second)
		{
			if(*range_min.first<=*range_max.first)
			{
				m_inter_min3.insert(*it);
				cout<<"inter_min "<<*it<<endl;
			}
			if(*--range_min.second<=*--range_max.second)
			{
				m_inter_max3.insert(*it);
				cout<<"inter_max "<<*it<<endl;
			}
		}
	}
	cout<<"end of prepa"<<endl;
	typename set<TypeData>::iterator it=m_inter_min3.begin();
	typename set<TypeData>::iterator it2=m_inter_max3.begin();
	while(it!=m_inter_min3.end()&&it2!=m_inter_max3.end())
	{
		typename set<TypeData>::iterator it3=it;
		while(it3!=m_inter_min3.end()&&*it3<=*it2)
		{
			++it3;
		}
		key.Set(i,*it);
		cout<<"insertmin "<<*it<<endl;
		math_set.InsertMin(key);
		it=it3;
		it3=it2;
		while(it3!=m_inter_max3.end()&&(m_inter_min3.end()==it||*it3<*it))
		{
			it2=it3;
			++it3;
		}
		key.Set(i,*it2);
		cout<<"insertmax "<<*it2<<endl;
		math_set.InsertMax(key);
		it2=it3;
	}
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
Math_Set3<DIM,TypeData,TypeData2,DIM2>::operator Math_Set2<DIM,TypeData>()
{
	Math_Set2<DIM,TypeData> math_set2;
	Physvector<DIM2,TypeData> key;
	ConvertSub(key,math_set2,1);
	return math_set2;
}

template<class TypeData,class TypeData2,int DIM2>
Math_Set3<1,TypeData,TypeData2,DIM2>::operator Math_Set2<1,TypeData>()
{
	Math_Set2<1,TypeData> math_set2;
	Physvector<DIM2,TypeData> key;
	ConvertSub(key,math_set2,1);
	return math_set2;
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::clear()
{
	m_data.clear();
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::clear()
{
	m_inter_min.clear();
	m_inter_max.clear();
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos)
{
	m_data.insert(pair<TypeData,m_math_set>(key.Get(1),m_math_set(m_1_h)));
	m_data[key.Get(1)].InsertMax(key,pos,2);
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos)
{
	m_data.insert(pair<TypeData,m_math_set>(key.Get(1),m_math_set(m_1_h)));
	m_data[key.Get(1)].InsertMin(key,pos,2);
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i)
{
	m_data.insert(pair<TypeData,m_math_set>(key.Get(i),m_math_set(m_1_h)));
	m_data[key.Get(i)].InsertMax(key,pos,i+1);
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i)
{
	m_data.insert(pair<TypeData,m_math_set>(key.Get(i),m_math_set(m_1_h)));
	m_data[key.Get(i)].InsertMin(key,pos,i+1);
}



template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos)
{
	InsertMin(key,pos,1);
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos)
{
	InsertMax(key,pos,1);
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i)
{
	m_inter_min.insert(pos.Get(i));
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i)
{
	m_inter_max.insert(pos.Get(i));
}

template<class TypeData,class TypeData2,int DIM2>
void Math_Set3<1,TypeData,TypeData2,DIM2>::CoutDebInfo()
{
	cout<<"deb min "<<endl;
	for(iterator it=m_inter_min.begin();it!=m_inter_min.end();++it)
	{
		cout<<*it<<endl;
	}
	cout<<"deb max "<<endl;
	for(iterator it=m_inter_max.begin();it!=m_inter_max.end();++it)
	{
		cout<<*it<<endl;
	}
}

template<int DIM,class TypeData,class TypeData2,int DIM2>
void Math_Set3<DIM,TypeData,TypeData2,DIM2>::CoutDebInfo()
{
	for(typename map_set::iterator it=m_data.begin();it!=m_data.end();++it)
	{
	       	cout<<"Dim "<<DIM<<" "<<it->first<<endl;
		it->second.CoutDebInfo();
	}
}

