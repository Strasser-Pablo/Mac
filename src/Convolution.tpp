#include <iostream>
using namespace std;
#include "To0.h"

/**
 * @file Convolution.tpp
 * @brief 
 * Implemetation file for class Convolution.
 **/

template <class TypeKernel, class TypeContainer,class TypeLabel,class TypeData>
Convolution<TypeKernel,TypeContainer,TypeLabel,TypeData>::Convolution()
{	
}

template <class TypeKernel, class TypeContainer,class TypeLabel,class TypeData>
Convolution<TypeKernel,TypeContainer,TypeLabel,TypeData>::~Convolution()
{
}

template <class TypeKernel, class TypeContainer,class TypeLabel,class TypeData>
void Convolution<TypeKernel,TypeContainer,TypeLabel,TypeData>::Calculate(TypeKernel &k,TypeContainer &in,TypeContainer &out){
	out=TypeContainer(in);
	for(typename TypeContainer::iterator it=out.begin();it!=out.end();++it){
		TypeLabel lab=it.GetLabel();
		TypeData sum= To0<TypeData>::value;
	for(typename TypeContainer::iterator it2=in.begin();it2!=in.end();++it2){
		sum+=k(lab-it2.GetLabel(),*it2);
	}
	*it=sum;
}
}