#ifndef Math_Set_H
#include <map>
#include "Physvector.h"
#include <deque>
#include <iostream>
#include <set>
using namespace std;

enum class Rel_Ensemble{A_In_B,B_In_A,A_Empty,B_Empty,Both_Empty,NONE};

template<int DIM,class TypeData>
class Math_Set
{
	map<TypeData,Math_Set<DIM-1,TypeData> > m_data;
public:
	Math_Set()=default;
	void Insert(Physvector<DIM,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	void Get(Physvector<DIM-1,TypeData> & key,set<TypeData> &result);
	template<int DIM2>
	void Get(Physvector<DIM2,TypeData> & key,int i,set<TypeData> &result);
	Rel_Ensemble IsIn(Math_Set<DIM,TypeData> & B);
}
;



template<class TypeData>
class Math_Set<1,TypeData>
{
	set<TypeData > m_interval;
	typedef typename set<TypeData >::iterator iterator;
	void merge(int dir);
public:
	Math_Set();
	void Insert(Physvector<1,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	void Get(Physvector<1,TypeData> & key,set<TypeData> &result);
	template<int DIM2>
	void Get(Physvector<DIM2,TypeData> & key,int i,set<TypeData> &result);
	Rel_Ensemble IsIn(Math_Set<1,TypeData> & B);
}
;

#include "Math_Set.tpp"

#endif