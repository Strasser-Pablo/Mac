#ifndef Inversible_Value_H
#define Inversible_Value_H
#include "Inversible_Value_Base.h"
template <class Data>
class Inversible_Value:public Inversible_Value_Base<Data,Inversible_Value<Data> >
{
	public:
	Data Inverse(const Data & data)
	{
		return 1/data;
	}
	Inversible_Value()
	{
	}
	Inversible_Value(const Data & data):Inversible_Value_Base<Data,Inversible_Value<Data> >(data)
	{
	}
};

#endif
