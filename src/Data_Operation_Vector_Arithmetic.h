#ifndef Data_Operation_Vector_Arithmetic_H
#define Data_Operation_Vector_Arithmetic_H

template <typename Implementation,typename ClassGet,typename TypeData>
class Data_Operation_Vector_Arithmetic
{
	friend auto operator+(const Implementation & a,const Implementation & b)-> Implementation 
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator-(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
	}
	friend auto operator*(const Implementation & a,const TypeData & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*b);
	}
	friend auto operator*(const TypeData & b,const Implementation & a)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*b);
	}
	friend auto operator/(const Implementation & a,const TypeData & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*(1/b));
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
	friend auto operator*=(Implementation & a,const TypeData & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*b);
		 return a;
	}
	friend auto operator/=(Implementation & a,const TypeData & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*(1/b));
		 return a;
	}
};

#endif
