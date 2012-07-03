#ifndef RundingFunction_H
#define RundingFunction_H

#include <cmath>

/**
 * @file RundingFunction.h
 * @brief
 * Declaration and implementation file for class Round, Ceil and Floor.
 **/

/**
 * @brief
 * Round to the neared integer.
 * @tparam TypeFloat Type of Float used.
 * @tparam TypeInt Type of integer used.
 **/
template <class TypeFloat,class TypeInt>
TypeInt round(const TypeFloat);

template <>
int  round<double,int>(const double f)
{
return lround(f);	
}

template <>
long  round<double,long>(const double f)
{
return lround(f);	
}

template <>
int  round<float,int>(const float f)
{
return lroundf(f);	
}

template <>
long  round<float,long>(const float f)
{
return lroundf(f);	
}

template <class TypeFloat,class TypeInt>
class Round
{
	public:
	TypeInt operator()(const TypeFloat f)
	{
		return round<TypeFloat,TypeInt>(f);
	}
};


template <class TypeFloat,class TypeInt>
TypeInt ceil(const TypeFloat);

template<>
int  ceil<double,int>(const double f)
{
return round<double,int>(ceil(f));
}

template<>
long  ceil<double,long>(const double f)
{
return round<double,long>(ceil(f));
}

template<>
int  ceil<float,int>(const float f)
{
return round<float,int>(ceil(f));
}

template<>
long  ceil<float,long>(const float f)
{
return round<float,long>(ceil(f));
}

template <class TypeFloat,class TypeInt>
TypeInt floor(const TypeFloat);

template<>
int  floor<double, int>(const double f)
{
return round<double,int>(floor(f));
}

template<>
long  floor<double, long>(const double f)
{
return round<double,long>(floor(f));
}

template<>
int  floor<float, int>(const float f)
{
return round<float,int>(floor(f));
}

template<>
long  floor<float, long>(const float f)
{
return round<float,long>(floor(f));
}

/**
 * @brief
 * Round to the upper integer.
 * @tparam TypeFloat Type of Float used.
 * @tparam TypeInt Type of integer used.
 **/
template <class TypeFloat,class TypeInt>
class Ceil
{
	public:
	TypeInt operator()(const TypeFloat f)
	{
		return ceil<TypeFloat,TypeInt>(f);
	}
};

/**
 * @brief
 * Round to the down integer.
 * @tparam TypeFloat Type of Float used.
 * @tparam TypeInt Type of integer used.
 **/
template <class TypeFloat,class TypeInt>
class Floor
{
	public:
	TypeInt operator()(const TypeFloat f)
	{
		return floor<TypeFloat,TypeInt>(f);
	}
};

#endif
