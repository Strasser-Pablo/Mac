#ifndef TestFunctorConvolution_H
#define TestFunctorConvolution_H

/**
 * @file TestFunctorConvolution.h
 * @brief Declaration file for class TestFunctorConvolution.
 **/
 
 /**
  * @deprecated
  * @brief
  * TestFunction to test Convolution.
  **/
class TestFunctorConvolution{
public:
	/**
	 * @brief
	 * Test Functor.
	 * @param label Label argument.
	 * @param data Data argument.
	 * @return double Return value.
	 **/
	double operator()(double label,double data);
};
#include "TestFunctorConvolution.tpp"
#endif
