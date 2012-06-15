#ifndef Inversible_Value_Vect_H
#define Inversible_Value_Vect_H
#include "Inversible_Value.h"
#include "Physvector.h"
template <class Data,int dim>
class Inversible_Value<Physvector<dim,Data> >:public Inversible_Value_Base<Physvector<dim,Data>,Inversible_Value<Physvector<dim,Data> > >
{
	public:
	Physvector<dim,Data> Inverse(const Physvector<dim,Data> & data)
	{
		Physvector<dim,Data> result;
		for(int i=1;i<=dim;++i)
		{
			result.GetRef(i)=1/data.Get(i);
		}
		return result;
	}
	Inversible_Value()
	{
	}
	Inversible_Value(const Physvector<dim,Data> & data):Inversible_Value_Base<Physvector<dim,Data>,Inversible_Value<Physvector<dim,Data> > >(data)
	{
	}
};

#endif
