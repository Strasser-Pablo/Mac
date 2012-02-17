/**
 * @file TestFunctorConvolution.tpp
 * @brief Implementation file for class TestFunctorConvolution.
 **/

#include <cmath>
double TestFunctorConvolution::operator()(double label,double data){
	if(abs(label)<0.25){
		return data;
	}
	return 0;
} 