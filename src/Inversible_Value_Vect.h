#ifndef Inversible_Value_Vect_H
#define Inversible_Value_Vect_H
#include "Inversible_Value.h"
#include "Physvector.h"

/**
 * @ingroup GR_Inversible_Value
 * @brief
 * This class allow to have the value of the vector and it's inverse element by element stored at same time.
 * This allow to not do uneeded calculation.
 * 
 * @tparam Data value type of the vector component.
 * @tparam dim Dimension of the vector.
 **/
template <class Data,int dim>
class Inversible_Value<Physvector<dim,Data> >:public Inversible_Value_Base<Physvector<dim,Data>,Inversible_Value<Physvector<dim,Data> > >
{
	public:
	/**
	 * @brief
	 * Calculate the inverse for the vector element by element.
	 * @param data Value to calculate the inverse from.
	 * @return Inverse element by element.
	 **/
	Physvector<dim,Data> Inverse(const Physvector<dim,Data> & data)
	{
		Physvector<dim,Data> result;
		for(int i=1;i<=dim;++i)
		{
			result.GetRef(i)=1/data.Get(i);
		}
		return result;
	}
	/**
	 * @brief
	 * Default Constructor.
	 **/
	Inversible_Value()
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @param data Initial value for the vector.
	 **/
	Inversible_Value(const Physvector<dim,Data> & data):Inversible_Value_Base<Physvector<dim,Data>,Inversible_Value<Physvector<dim,Data> > >(data)
	{
	}
};

#endif
