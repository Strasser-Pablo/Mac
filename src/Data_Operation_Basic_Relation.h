#ifndef Data_Operation_Basic_Relation
#define Data_Operation_Basic_Relation_H

template <typename Implementation,typename ClassGet>
class Data_Operation_Basic_Relation
{
	friend bool operator==(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()==static_cast<const ClassGet&>(b).Get();
	}
	friend bool operator!=(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()!=static_cast<const ClassGet&>(b).Get();
	}
};

#endif
