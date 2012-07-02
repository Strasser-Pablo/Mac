#ifndef ApplyToEveryPhysvectorData_H
#define ApplyToEveryPhysvectorData_H

#include "Physvector.h"

/**
 * @file ApplyToEveryPhysvectorData.h
 * @brief
 * Declaration file for class ApplyToEveryPhysvectorData.
 **/
/**
 * @brief 
 * This class apply an operation to element of a vector.
 * Element by Element, and return another value posibly of another type.
 * \tparam TypeDataIn Type of the input Physvector.
 * \tparam TypeDataOut Type of the output Physvector.
 * \tparam TypeFunctor Type of the functor to use.
 * \tparam Dim Dimension of the Physvector.
 **/
template <class TypeDataIn,class TypeDataOut,class TypeFunctor,int DIM>
class  ApplyToEveryPhysvectorData
{
public:
	/**
	 * Apply the change element by element applying the functor to all element and storing the returned value.
	 * @param vin In vector, will be used as source to the transform.
	 * @param vout Out vector, where the result of the Functor is stored.
	 * @param func Functor that need to have a () taking as argument TypeDataIn and as return value TypeDataOut
	 **/
	void Transform(const Physvector<DIM,TypeDataIn> & vin,Physvector<DIM,TypeDataOut> & vout,TypeFunctor & func);
};

#include "ApplyToEveryPhysvectorData.tpp"
#endif