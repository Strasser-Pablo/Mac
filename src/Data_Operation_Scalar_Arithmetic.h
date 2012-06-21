#ifndef Data_Operation_Scalar_Arithmetic_H
#define Data_Operation_Scalar_Arithmetic_H

template <typename Implementation,typename ClassGet>
class Data_Operation_Scalar_Arithmetic
{
	friend auto operator+(const Implementation & a,const Implementation & b)-> Implementation 
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator-(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator*(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator/(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()/static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator+=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	friend auto operator-=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	friend auto operator*=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	friend auto operator/=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()/static_cast<const ClassGet&>(b).Get());
		 return a;
	}
};

#endif
