#ifndef NLinearInterpolation_H
#define NLinearInterpolation_H

#include "Physvector.h"
#include "RundingFunction.h"
#include "InternalException.h"

#include <iostream>

template <int type_dim,class type_data,int prof,int type_stop,class TypeWorld>
struct SubElement
{
	static type_data Do( Physvector<type_dim,int>& el,const Physvector<type_dim,type_data>& posdelta0scaled,const Physvector<type_dim,int> &key0 ,int ind,TypeWorld &m_world)
	{
		SubElement<type_dim,type_data,prof+1,type_stop-1,TypeWorld> SE;
		el.Set(prof,0);
		type_data a=SE.Do(el,posdelta0scaled,key0,ind,m_world);
		el.Set(prof,1);
		type_data b=SE.Do(el,posdelta0scaled,key0,ind,m_world);
		return a+b;
	}
};

template <int type_dim,class type_data,int prof,class TypeWorld>
struct SubElement<type_dim,type_data,prof,1,TypeWorld>
{
	static type_data Do( Physvector<type_dim,int>& el,const Physvector<type_dim,double>& posdelta0scaled,const Physvector<type_dim,int> &key0 ,int ind,TypeWorld &m_world)
	{
		type_data ret=1;
		for(int i=1;i<=type_dim;++i)
		{
			ret*=(posdelta0scaled.Get(i)-1+el.Get(i) )*(-1+2*el.Get(i));
		}
		Physvector<type_dim,type_data> vtemp;
		if(m_world.m_mac_grid.Exist(key0+el))
		{
		m_world.m_mac_grid[key0+el].GetSpeed(vtemp);
		ret*=vtemp.Get(ind);
		return ret;
		}
		else{
			return 0;
		}
	}
};
/**
 * @file NLinearInterpolation.h
 * @brief
 * Declaration file for class NLinearInterpolation.
 **/

using namespace std;

/**
 * @brief
 * Calculate a N linear interpolation for the ith component of speed.
 * @tparam TypeWorld type of World used.
 **/
template <class TypeWorld>
class NLinearInterpolation
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	TypeWorld &m_world;
	const Physvector<type_dim,type_data> &m_1_h;
	/**
	 * @brief 
	 * Calculate Recursifly the interpolation.
	 * The recursion will be done in dimension of space.
	 * @param el Partial element to calculate, where component after depth are 0.
	 * The element consist of vector of 0 or 1. Depending one witch side component to use.
	 * @param posdelta0scaled Scaled position counted with 0 position at key0.
	 * @param key0 0 key of the interpolation.
	 * @param ind Speed index to use.
	 * @param prof How many term we have calculated. when i=type_dim+1 we have finished.
	 * 
	 * \exception InternalError if prof is bigger than the stop condition.
	 * This cannot normaly happen.
	 **/
public:

/**
 * @brief
 * Constructor.
 * @param world World used.
 * @param _1_h 1 over the cell spacing.
 **/
NLinearInterpolation(TypeWorld &world,const Physvector<type_dim,type_data> &_1_h );
/**
 * @brief 
 * Calculate the interpolation.
 * @param pos Position to calculate.
 * @param ind Speed component to calculate.
 * @return type_data Result for the given speed.
 **/
type_data	Calculate(Physvector<type_dim,type_data> pos,int ind);
};
#include "NLinearInterpolation.tpp"
#endif