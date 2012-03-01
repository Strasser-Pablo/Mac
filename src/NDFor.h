#ifndef NDFor_H
#include "Physvector.h"
#include <iostream>

using namespace std;
template <class Function,class TypeData,int DIM,int dact=0>
class NDFor
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_max;
	Function& m_f;
	TypeData m_save;
	NDFor<Function,TypeData,DIM,dact+1> m_for;
public:
	NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f);
	void Calculate();
};

template <class Function,class TypeData,int DIM>
class NDFor<Function,TypeData,DIM,DIM>
{
	Physvector<DIM,TypeData>& m_init;
	TypeData& m_max;
	Function& m_f;
public:
	NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f);
	void Calculate();
};
#include "NDFor.tpp"
#endif