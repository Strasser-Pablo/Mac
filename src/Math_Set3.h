#ifndef Math_Set3_H
#define Math_Set3_H
#include <map>
#include "Physvector.h"
#include <deque>
#include <iostream>
#include <set>
#include <cassert>
#include <stdexcept>
#include "Math_Set2.h"
#include "RundingFunction.h"
using namespace std;

/**
 * @brief
 * Represent a set of integer.
 * Allow opperation as to know if a set is in another.
 * @tparam DIM Dimension of the set.
 * @tparam TypeData Data stored. Assumed to be an integral value.
 **/
template<int DIM,class TypeData,class TypeData2,int DIM2=DIM>
class Math_Set3
{
	typedef Math_Set3<DIM-1,TypeData,TypeData2,DIM2> m_math_set; 
	typedef map<TypeData,Math_Set3<DIM-1,TypeData,TypeData2,DIM2> > map_set;
	map_set m_data;
	const Physvector<DIM2,TypeData2> &m_1_h;
	Round<TypeData2,TypeData> m_R;
public:
	void ConvertSub(Physvector<DIM2,TypeData> &key,Math_Set2<DIM2,TypeData> & math_set,int i);
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	Math_Set3(const Physvector<DIM2,TypeData2> &_1_h);
	Math_Set3();
	operator Math_Set2<DIM,TypeData>();
	void clear();
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i);
	/**
	 * @brief
	 * Output the content of the key in standard output.
	 **/
	void CoutDebInfo();
	friend Math_Set3;
};

/**
 * @brief
 * Represent a set of integer.
 * Allow opperation as to know if a set is in another.
 * @tparam TypeData Data stored. Assumed to be an integral value.
 **/
template<class TypeData,class TypeData2,int DIM2>
class Math_Set3<1,TypeData,TypeData2,DIM2>
{
	set<TypeData2> m_inter_min;
	set<TypeData2> m_inter_max;
	Round<TypeData2,TypeData> m_R;
	const Physvector<DIM2,TypeData2> &m_1_h;
	typedef typename set<TypeData2>::iterator iterator;
public:
	void ConvertSub(Physvector<DIM2,TypeData> &key,Math_Set2<DIM2,TypeData> & math_set,int i);
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	Math_Set3(const Physvector<DIM2,TypeData2> &_1_h);
	Math_Set3();
	operator Math_Set2<1,TypeData>();
	void clear();
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(const Physvector<DIM2,TypeData> & key,const Physvector<DIM2,TypeData2> & pos,int i);
	/**
	 * @brief
	 * Output the content of the key in standard output.
	 **/
	void CoutDebInfo();
};
#include "Math_Set3.tpp"
#endif
