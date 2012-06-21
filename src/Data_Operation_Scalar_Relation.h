#ifndef Data_Operation_Scalar_Relation_H
#define Data_Operation_Scalar_Relation_H

template <typename Implementation,typename ClassGet>
class Data_Operation_Scalar_Relation
{
	friend bool operator==(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()==static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator!=(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()!=static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator<(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()<static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator>(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()>static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator>=(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()>=static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator<=(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()<=static_cast<const ClassGet&>(b).Get();
	}
};

#endif
