#ifndef Math_Set2_H
#include <map>
#include "Physvector.h"
#include <deque>
#include <iostream>
#include <set>
#include <cassert>
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
	void InsertBoth(Physvector<DIM,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertBoth(Physvector<DIM2,TypeData> & key,int i);
	Rel_Ensemble IsIn(Math_Set2<DIM,TypeData> & B);
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
	void InsertBoth(Physvector<1,TypeData> & key);
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	template<int DIM2>
	void InsertBoth(Physvector<DIM2,TypeData> & key,int i);
	Rel_Ensemble IsIn(Math_Set2<1,TypeData> & B);
};
#include "Math_Set2.tpp"
#endif
