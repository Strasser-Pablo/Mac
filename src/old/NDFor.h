#ifndef NDFor_H
#include "Physvector.h"
#include <iostream>

using namespace std;

/**
 * @brief
 * A NDimensional for function.
 * It allow to calculate all possible vector (in a square) with given minimal and maximal value.
 * And call the function in argument with the given vector.
 * @tparam Function Function type to call.
 * @tparam TypeData Type of data of the vector.
 * @tparam DIM Dimension of the vector.
 * @tparam dact Value used for recursion.
 **/
template <class Function,class TypeData,int DIM,int dact=0>
class NDFor
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_max;
	Function& m_f;
	TypeData m_save;
	NDFor<Function,TypeData,DIM,dact+1> m_for;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param init Initial vector.
	 * @param max Maximal value for all vector component.
	 * @parram f Function to call.
	 **/
	NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f);
	/**
	 * @brief
	 * Calculate the loop
	 **/
	void Calculate();
};

/**
 * @brief
 * A NDimensional for function.
 * It allow to calculate all possible vector (in a square) with given minimal and maximal value.
 * And call the function in argument with the given vector.
 * @tparam Function Function type to call.
 * @tparam TypeData Type of data of the vector.
 * @tparam DIM Dimension of the vector.
 * @tparam dact Value used for recursion.
 **/
template <class Function,class TypeData,int DIM>
class NDFor<Function,TypeData,DIM,DIM>
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_max;
	Function& m_f;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param init Initial vector.
	 * @param max Maximal value for all vector component.
	 * @parram f Function to call.
	 **/
	NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f);
	/**
	 * @brief
	 * Calculate the loop
	 **/
	void Calculate();
};
#include "NDFor.tpp"
#endif
