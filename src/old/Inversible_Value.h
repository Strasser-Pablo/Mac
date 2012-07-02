#ifndef Inversible_Value_H
#define Inversible_Value_H
#include "Inversible_Value_Base.h"
/**
 * @ingroup GR_Inversible_Value
 * @brief
 * This Class store a value witch can be inversed with a division operator /.
 * The goal of this class is to store at same time the value and his inverse.
 *
 * This allow to not recalculate inverse when not needed.
 *
 * @pre
 * Data need to be inversible by `1/data`.
 * @tparam Data Value to use.
 **/
template <class Data>
class Inversible_Value:public Inversible_Value_Base<Data,Inversible_Value<Data> >
{
	public:
	/**
	 * @brief
	 * Calculate the inverse of argument.
	 * Used in the base class.
	 * @param data Data to inverse.
	 * @return Inverse calculated.
	 **/
	Data Inverse(const Data & data)
	{
		return 1/data;
	}
	/**
	 * @brief
	 * Default constructor.
	 **/
	Inversible_Value()
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @param data Initial value for the value.
	 **/
	Inversible_Value(const Data & data):Inversible_Value_Base<Data,Inversible_Value<Data> >(data)
	{
	}
};

#endif
