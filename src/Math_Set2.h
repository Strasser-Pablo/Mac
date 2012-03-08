#ifndef Math_Set2_H
#include <map>
#include "Physvector.h"
#include <deque>
#include <iostream>
#include <set>
#include <cassert>
#include <stdexcept>
using namespace std;

enum class Rel_Ensemble{A_In_B,B_In_A,A_Empty,B_Empty,Both_Empty,NONE};

template<int DIM,class TypeData>
class Math_Set2
{
	map<TypeData,Math_Set2<DIM-1,TypeData> > m_data;
public:
	Math_Set2()=default;
	void Insert(Physvector<DIM,TypeData> & key);
	void InsertMax(Physvector<DIM,TypeData> & key);
	void InsertMin(Physvector<DIM,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	Rel_Ensemble IsIn(Math_Set2<DIM,TypeData> & B);
	void CoutDebInfo();
	template<class func,int DIM2>
	void FillSet(func f,Physvector<DIM2,TypeData> &key,int i)
	{
  	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		key.GetRef(i)=it->first;
		it->second.FillSet(f,key,i+1);
	}
	}
	template<class func>
	void FillSet(func &f)
	{

	Physvector<DIM,TypeData> key;
	FillSet(f,key,1);
	}
	
	template<class func,int DIM2>
	void FillBoundary(func f,Physvector<DIM2,TypeData> &key,int i)
	{

  	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		key.GetRef(i)=it->first;
		it->second.FillBoundary(f,key,i+1);
	}
	}
	template<class func>
	void FillBoundary(func &f)
	{

	Physvector<DIM,TypeData> key;
	FillBoundary(f,key,1);
	}
};

template<class TypeData>
class Math_Set2<1,TypeData>
{
	set<TypeData> m_inter_min;
	set<TypeData> m_inter_max;
	typedef typename set<TypeData>::iterator iterator;
	void merge(int dir);
public:
	Math_Set2();
	void Insert(Physvector<1,TypeData> & key);
	void InsertMax(Physvector<1,TypeData> & key);
	void InsertMin(Physvector<1,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	Rel_Ensemble IsIn(Math_Set2<1,TypeData> & B);
	void CoutDebInfo();
	template<class func,int DIM2>
	void FillSet(func &f,Physvector<DIM2,TypeData> &key,int i)
	{

	if(m_inter_max.empty()&&m_inter_min.empty())
	{
		return; 
	}
	// Ok we are not empty, test if we need to swap min,max.
	if(*m_inter_min.begin()>*m_inter_max.begin())
	{
		m_inter_min.swap(m_inter_max);
	}
	
	iterator it=m_inter_min.begin();
	iterator it2=m_inter_max.begin();
	while(it!=m_inter_min.end())
	{
		for(int j=*it+1;j<=*it2-1;++j)
		{
			key.GetRef(i)=j;
			f(key);
		}	
		++it;
		++it2;
	}
	}
	template<class func>
	void FillSet(func &f)
	{

	Physvector<1,TypeData> key;
	FillSet(f,key,1);
	}
	
	template<class func,int DIM2>
	void FillBoundary(func &f,Physvector<DIM2,TypeData> &key,int i)
	{
	iterator it=m_inter_min.begin();
	iterator it2=m_inter_max.begin();
	while(it!=m_inter_min.end())
	{
		key.GetRef(i)=*it;
		f(key);
		key.GetRef(i)=*it2;
		f(key);	
		++it;
		++it2;
	}
	}
	template<class func>
	void FillBoundary(func &f)
	{

	Physvector<1,TypeData> key;
	FillBoundary(f,key,1);
	}
};
#include "Math_Set2.tpp"
#endif
