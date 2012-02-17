#ifndef FunctionTest_H
#define FunctionTest_H

/**
 * @file FunctionTest.h
 * @brief
 * Declaration file for class FunctionTest
 **/

/**
 * @brief
 * Simple Functor to test. That use double.
 **/
class FunctionTest{
	
public:
/**
 * @brief
 * Function retourning double with one double as parameter.
 * @param data First parameter
 * @return return value.
 **/
	inline double operator()(double data);
};
#include "FunctionTest.tpp"
#endif