#ifndef NDForMin_H
#include "Physvector.h"
#include <iostream>

using namespace std;
template <class Function,class TypeData,int DIM,int dact=0>
class NDForMin
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_min;
	Function& m_f;
	TypeData m_save;
	NDForMin<Function,TypeData,DIM,dact+1> m_for;
public:
	NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f);
	void Calculate();
};

template <class Function,class TypeData,int DIM>
class NDForMin<Function,TypeData,DIM,DIM>
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_min;
	Function& m_f;
public:
	NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f);
	void Calculate();
};
#include "NDForMin.tpp"
#endif