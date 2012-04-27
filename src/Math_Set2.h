#ifndef Math_Set2_H
#define Math_Set2_H
#include <map>
#include "Physvector.h"
#include <deque>
#include <iostream>
#include <set>
#include <cassert>
#include <stdexcept>
using namespace std;
/**
 * @brief
 * Enum that contain value for relation between two set.
 **/
enum class Rel_Ensemble{A_In_B,B_In_A,A_Empty,B_Empty,Both_Empty,NONE};

/**
 * @brief
 * Represent a set of integer.
 * Allow opperation as to know if a set is in another.
 * @tparam DIM Dimension of the set.
 * @tparam TypeData Data stored. Assumed to be an integral value.
 **/
template<int DIM,class TypeData>
class Math_Set2
{
	map<TypeData,Math_Set2<DIM-1,TypeData> > m_data;
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	Math_Set2()=default;
	void clear();
	void CleanDouble();
	bool testBounded();
	/**
	 * @deprecated
	 **/
	void Insert(Physvector<DIM,TypeData> & key);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(Physvector<DIM,TypeData> & key);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(Physvector<DIM,TypeData> & key);
	/**
	 * @brief
	 * Deprecated.
	 **/
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Return an Rel_Ensemble enum value of the relation with respect to B.
	 * @param B Set to compare with.
	 **/
	Rel_Ensemble IsIn(Math_Set2<DIM,TypeData> & B);
	/**
	 * @brief
	 * Output the content of the key in standard output.
	 **/
	void CoutDebInfo();
	/**
	 * @brief
	 * Fill the set interior with a call the the given functor.
	 * This function is a function used in recursif implementation.
	 * \param f Functor to call with the key of the position.
	 * \param key Current key to test.
	 * \param i Depth of recursion.
	 **/
	template<class func,int DIM2>
	void FillSet(func f,Physvector<DIM2,TypeData> &key,int i)
	{
  	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		key.GetRef(i)=it->first;
		it->second.FillSet(f,key,i+1);
	}
	}
	/**
	 * @brief
	 * Fill the set interior with a call the the given functor.
	 * \param f Functor to call with the key of the position.
	 **/
	template<class func>
	void FillSet(func &f)
	{

	Physvector<DIM,TypeData> key;
	FillSet(f,key,1);
	}
	
	/**
	 * @brief
	 * Fill the set boundary with a call the the given functor.
	 * This function is a function used in recursif implementation.
	 * \param f Functor to call with the key of the position.
	 * \param key Current key to test.
	 * \param i Depth of recursion.
	 **/
	template<class func,int DIM2>
	void FillBoundary(func f,Physvector<DIM2,TypeData> &key,int i)
	{

  	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		key.GetRef(i)=it->first;
		it->second.FillBoundary(f,key,i+1);
	}
	}
	/**
	 * @brief
	 * Fill the set boundary with a call the the given functor.
	 * \param f Functor to call with the key of the position.
	 **/
	template<class func>
	void FillBoundary(func &f)
	{

	Physvector<DIM,TypeData> key;
	FillBoundary(f,key,1);
	}
};

/**
 * @brief
 * Represent a set of integer.
 * Allow opperation as to know if a set is in another.
 * @tparam TypeData Data stored. Assumed to be an integral value.
 **/
template<class TypeData>
class Math_Set2<1,TypeData>
{
	set<TypeData> m_inter_min;
	set<TypeData> m_inter_max;
	typedef typename set<TypeData>::iterator iterator;
	void merge(int dir);
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	Math_Set2();
	void clear();
	void CleanDouble();
	bool testBounded();
	/**
	 * @deprecated
	 **/
	void Insert(Physvector<1,TypeData> & key);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	void InsertMax(Physvector<1,TypeData> & key);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	void InsertMin(Physvector<1,TypeData> & key);
	/**
	 * @brief
	 * Deprecated.
	 **/
	template<int DIM2>
	void Insert(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Insert a maximal value with a given key.
	 * The notion of maximal say that in the first component direction we are the maximal value in the set.
	 * We can have a minimum to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun.
	 * @param key To add in set. 
	 **/
	template<int DIM2>
	void InsertMax(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Insert a minimal value with a given key.
	 * The notion of minimal say that in the first component direction we are the minimal value in the set.
	 * We can have a maximun to if we make it consistently in all function in the given set.
	 * This is usefull because we normally don't know if it's minimun or maximun 
	 * @param key To add in set. 
	 **/
	template<int DIM2>
	void InsertMin(Physvector<DIM2,TypeData> & key,int i);
	/**
	 * @brief
	 * Return an Rel_Ensemble enum value of the relation with respect to B.
	 * @param B Set to compare with.
	 **/
	Rel_Ensemble IsIn(Math_Set2<1,TypeData> & B);
	/**
	 * @brief
	 * Output the content of the key in standard output.
	 **/
	void CoutDebInfo();
	/**
	 * @brief
	 * Fill the set interior with a call the the given functor.
	 * This function is a function used in recursif implementation.
	 * \param f Functor to call with the key of the position.
	 * \param key Current key to test.
	 * \param i Depth of recursion.
	 **/
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
	/**
	 * @brief
	 * Fill the set interior with a call the the given functor.
	 * \param f Functor to call with the key of the position.
	 **/
	template<class func>
	void FillSet(func &f)
	{

	Physvector<1,TypeData> key;
	FillSet(f,key,1);
	}

	/**
	 * @brief
	 * Fill the set boundary with a call the the given functor.
	 * This function is a function used in recursif implementation.
	 * \param f Functor to call with the key of the position.
	 * \param key Current key to test.
	 * \param i Depth of recursion.
	 **/
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
	/**
	 * @brief
	 * Fill the set boundary with a call the the given functor.
	 * \param f Functor to call with the key of the position.
	 **/
	template<class func>
	void FillBoundary(func &f)
	{

	Physvector<1,TypeData> key;
	FillBoundary(f,key,1);
	}
};
#include "Math_Set2.tpp"
#endif
