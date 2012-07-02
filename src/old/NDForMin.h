#ifndef NDForMin_H
#include "Physvector.h"
#include <iostream>

using namespace std;
/**
 * @brief
 * A NDimensional for function.
 * It allow to calculate all possible vector (in a square) with given minimal and maximal value.
 * This version make the calculation from high value to low value.
 * And call the function in argument with the given vector.
 * @tparam Function Function type to call.
 * @tparam TypeData Type of data of the vector.
 * @tparam DIM Dimension of the vector.
 * @tparam dact Value used for recursion.
 **/
template <class Function,class TypeData,int DIM,int dact=0>
class NDForMin
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_min;
	Function& m_f;
	TypeData m_save;
	NDForMin<Function,TypeData,DIM,dact+1> m_for;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param init Initial vector.
	 * @param min Minimal value for all vector component.
	 * @parram f Function to call.
	 **/
	NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f);
	/**
	 * @brief
	 * Do the loop calculation.
	 **/
	void Calculate();
};

/**
 * @brief
 * A NDimensional for function.
 * It allow to calculate all possible vector (in a square) with given minimal and maximal value.
 * This version make the calculation from high value to low value.
 * And call the function in argument with the given vector.
 * @tparam Function Function type to call.
 * @tparam TypeData Type of data of the vector.
 * @tparam DIM Dimension of the vector.
 * @tparam dact Value used for recursion.
 **/
template <class Function,class TypeData,int DIM>
class NDForMin<Function,TypeData,DIM,DIM>
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_min;
	Function& m_f;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param init Initial vector.
	 * @param min Minimal value for all vector component.
	 * @parram f Function to call.
	 **/
	NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f);
	/**
	 * @brief
	 * Do the loop calculation.
	 **/
	void Calculate();
};
#include "NDForMin.tpp"
#endif
