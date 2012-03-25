#include "ODEFirstOrderTimeIndependent.h"
#ifndef Euler_H
#define Euler_H

/**
 * @file Euler.h 
 * @brief
 * Declaration file for class Euler.
 **/
 
 /**
  * @ingroup GR_ODE_Method
  * @brief
  * Implementation to Solve ODE independent on time with Euler method.
  * To be used as last template argument of ODEFirstOrderTimeIndependent.
  * 
  * \f[ x_h=x_0+h*f(x) \f]
  *
  * \tparam TypeData Type of the data.
  * \tparam TypeFunctor Type of the Functor.
  * \tparam TypeTime Type of the time.
  **/
template<class TypeData,class TypeFunctor,class TypeTime>
class Euler
{
public:
	/**
	 * @brief
	 * Default constructor, make nothing.
	 **/
	inline Euler();
	/**
	 * @brief
	 * Destructor that make nothing.
	 **/
	virtual inline ~Euler();
	/**
	 * @brief
	 * Calculate an Euler step.
	 * @param data0 Initial condition.
	 * @param functor Function to use.
	 * @param timeStep Time step to calculate.
	 * @param dataResult Reference where result will be put. Can be the same that data0.
	 * 
	 * And euler step consist to:
	 * \f[x_h=x_0+f(x_0)dt \f]
	 **/
	virtual inline void Calculate(TypeData &data0, TypeFunctor &functor,TypeTime &timeStep,TypeData &dataResult);
};

#include "Euler.tpp"
#endif

