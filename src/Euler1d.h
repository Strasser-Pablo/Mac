
#ifndef Euler1d_H
#define Euler1d_H
#include "Euler.h"
/**
 * @file Euler1d.h
 * @brief
 * Declaration file for class Euler1d
 **/
 
 /**
  * @ingroup GR_ODE_Method
  * 
  * @deprecated
  * Not used and serve nothing because dimension is a unknow. 
  *
  * @brief
  * Calculate one dimensional ODE with Euler method.
  * 
  * Where time is a double.
  * Consist on a specialization of Euler.$
  * \tparam TypeFunctor Type of the functor used to evaluate the position.
  **/
template<class TypeFunctor> 
class Euler1d :public Euler<double,TypeFunctor,double>
{
public:
	/**
	 * @brief
	 * Default constructor, make nothing.
	 **/
	inline Euler1d();
	
	/**
	 * @brief
	 * Default destructor make nothing.
	 **/
	virtual inline ~Euler1d();
};
#include "Euler1d.tpp"
#endif
