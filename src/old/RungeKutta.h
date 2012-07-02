#include "ODEFirstOrderTimeIndependent.h"
#ifndef RungeKutta_H
#define RungeKutta_H

/**
 * @file RungeKutta.h 
 * @brief
 * Declaration file for class RungeKutta.
 **/
 
 /**
  * @ingroup GR_ODE_Method
  * @brief
  * Implementation to Solve ODE independent on time with RungeKutta method.
  * To be used as last template argument of ODEFirstOrderTimeIndependent.
  * 
  * \tparam TypeData Type of the data.
  * \tparam TypeFunctor Type of the Functor.
  * \tparam TypeTime Type of the time.
  * 
  * \f[k_1=f(x_0) \f]
  * \f[k_2=f\left(x_0+\frac{dt}{2}k_1\right) \f]
  * \f[k_3=f\left(x_0+\frac{dt}{2}k_2\right) \f]
  * \f[k_4=f\left(x_0+dtk_3\right) \f]
  * \f[x_h=x_0+\frac{dt}{6}\left(k_1+2k_2+2k_3+k_4\right) \f]
  **/
template<class TypeData,class TypeFunctor,class TypeTime>
class RungeKutta
{
public:
	/**
	 * @brief
	 * Default constructor. Make nothing
	 **/
	inline RungeKutta();
	/**
	 * @brief
	 * Destructor that make nothing.
	 **/
	virtual inline ~RungeKutta();
	/**
	 * @brief
	 * Calculate an Runge Kutta step.
	 * @param data0 Initial condition.
	 * @param functor Function to use.
	 * @param timeStep Time step to calculate.
	 * @param dataResult Reference where result will be put. Can be the same that data0.
	 **/
	virtual inline void Calculate(TypeData &data0, TypeFunctor &functor,TypeTime &timeStep,TypeData &dataResult);
};

#include "RungeKutta.tpp"
#endif

