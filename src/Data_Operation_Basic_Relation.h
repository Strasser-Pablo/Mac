#ifndef Data_Operation_Basic_Relation
#define Data_Operation_Basic_Relation_H

/**
 * @ingroup Data_Operation
 * @brief
 * Class mean to be derived to give Equality and Inequality operation by mean of an .Get equality and inéquality.
 **/
template <typename Implementation,typename ClassGet>
class Data_Operation_Basic_Relation
{
	/**
	 * @brief
	 * Return true if a and b are equale. Compare with the Get method of the two.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Boolean saying if it's equal.
	 **/
	friend bool operator==(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()==static_cast<const ClassGet&>(b).Get();
	}
	/**
	 * @brief
	 * Return true if a and b are inequal. Compare with the Get method of the two.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Boolean saying if it's inequal.
	 **/
	friend bool operator!=(const Implementation & a,const Implementation & b)
	{
		return static_cast<const ClassGet&>(a).Get()!=static_cast<const ClassGet&>(b).Get();
	}
};

#endif
