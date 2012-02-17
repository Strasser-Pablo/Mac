#ifndef Convolution_H
#define Convoultion_H
/**
 * @file Convolution.h
 * @brief Declaration file for class Convolution.
 **/

/**
 * @brief
 * This class enable to calculate the convolution by direct sum.
 * @tparam TypeKernel Type of the Kernel.
 * @tparam TypeContainer Type of the container containing the data.
 * @tparam TypeLabel Type of the label.
 * @tparam TypeData Type of the data.
 * 
 * TypeKernel need to be a functor return a value of TypeData with an argument of TypeLabel and TypeData.
 * 
 **/
template <class TypeKernel, class TypeContainer,class TypeLabel,class TypeData>
class Convolution{
public:
	/**
	 * @brief 
	 * Default Constructor
	 **/
	Convolution();
	/**
	 * Default Destructor.
	 **/
	~Convolution();
	/**
	 * @brief
	 * Calculate the Convolution.
	 * \param k Kernel to use.
	 * \param in In data.
	 * \param out Out data.
	 **/
void  Calculate(TypeKernel &k,TypeContainer &in,TypeContainer &out);
};

#include "Convolution.tpp"
#endif