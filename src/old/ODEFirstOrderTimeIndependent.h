#ifndef ODEFirstOrderTimeIndependent_H
#define ODEFirstOrderTimeIndependent_H
/**
 * @file ODEFirstOrderTimeIndependent.h
 * @brief 
 * File where Class ODEFirstOrderTimeIndependent is Declared.
**/

/**
 * @ingroup GR_ODE_Solver
 * @brief  Class for solving first order ODE without time dependence.
 *
 * This class represent an ODE of form:
 * \f[ \frac{dx}{dt}=f(x) \f]
 *
 * \tparam TypeData Type used for the unknow (double for 1d).
 * \tparam TypeFunctor Type used for the functor used to evaluate value at a givent point.
 * \tparam TypeTime Type used for time(normaly double).
 * \tparam TypeMethod Type used for method.
 * 
 * The following operation need to be define.
 * - Addition of TypeData (normally element by element)
 * - Multiplication of TypeData and TypeTime returning a TypeData, so that
 * \f[ x_h=x_0+dt*dx \f]
 * - The Functor need to be called with TypeData as argument.
 * - The method need to define a function calculate with the following prototype:
 * \code
 * void Calculate(TypeData &data0, TypeFunctor &functor,TypeTime &time,TypeData &dataResult)
 * \endcode
 * where data0 and dataResult can be posibly be the same.
 * 
 * For example for the euler implementation we need to do:
 * 
 * \code
 * x+=dt*f(x);
 * \endcode
 *
 * No storage is done for Data. We only use reference to Data.
 * 
**/ 
template<class TypeData,class TypeFunctor,class TypeTime,class TypeMethod>
class ODEFirstOrderTimeIndependent{
protected:
	/**
	 * @brief
	 * Reference to current value of the differential equation
	**/
	TypeData& m_data;
	/**
	 * @brief
	 * Functor that give the derivatif.
	 **/
	TypeFunctor& m_functor;
	/**
	 * @brief
	 * Default time step.
	 **/
	TypeTime m_time;
	/**
	 * @brief Reference to the method used to calculate.
	 **/
	TypeMethod & m_method;
public:
	/**
	 * @brief 
	 * Constructor initializing data.
	 * 
	 * @param data Reference to data. Will be stored in m_data.
	 * @param functor Functor representing the function to solve.
	 * will be stored in m_functor.
	 * @param time Represent the default timeStep. Will be stored in m_time.
	 * @param method Method used to solve the ode. It need to define a function calculate.
	 **/
	inline ODEFirstOrderTimeIndependent(TypeData & data,TypeFunctor & functor,TypeTime  time, TypeMethod & method);
	/**
	 * This destructor don't destroy the data in the reference given.
	 * It's user responsability.
	 **/
	virtual inline ~ODEFirstOrderTimeIndependent();
	/**
	 * This function calculate the next time step with the default time step.
	 **/
	virtual inline void Calculate();
	/**
	* This function calculate the next time step with the time step given as argument.
	* 
	* @param timeStep Next TimeStep.
	**/
	 virtual inline void Calculate(TypeTime timeStep);
};

#include "ODEFirstOrderTimeIndependent.tpp"

#endif
