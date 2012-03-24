#ifndef PhysvectorKeyOrder_H
#define PhysvectorKeyOrder_H
#include "Physvector.h"

/**
 * @file PhysvectorKeyOrder.h
 * @brief
 * Declaration file for class PhysvectorKeyOrder.
 **/
 
 /**
  * @ingroup GR_Map
  * @brief
  * Ordering class that order physvector as key.
  * Ordering by the first element of the vector and in case of equality use the next.
  * For exemple (1,2,3)<(2,1,1)
  **/
template<int Dim,class TypeData>
class PhysvectorKeyOrder{
public:
	/**
	 * @brief
	 * Function call returning true if smaller in numerical order.
	 * @param A First vector to compare.
	 * @param B Second vector to compare.
	 **/
	bool operator()(const Physvector<Dim,TypeData> &A,const Physvector<Dim,TypeData> &B )const;
};

#include "PhysvectorKeyOrder.tpp"

#endif
