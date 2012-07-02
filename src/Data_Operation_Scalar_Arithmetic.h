#ifndef Data_Operation_Scalar_Arithmetic_H
#define Data_Operation_Scalar_Arithmetic_H

/**
 * @ingroup Data_Operation
 * @brief
 * Class to be derived to give arithmetique operation with a .Get method called before.
 * @tparam Implementation Class for witch we need to implement operation.
 * @tparam ClassGet Class to cast Implementation to access a Get Method.
 **/
template <typename Implementation,typename ClassGet>
class Data_Operation_Scalar_Arithmetic
{
	/**
	 * @brief
	 * Addition operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the addition.
	 **/
	friend auto operator+(const Implementation & a,const Implementation & b)-> Implementation 
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Soustraction operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the soustraction.
	 **/
	friend auto operator-(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Multiplication operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the multiplication.
	 **/
	friend auto operator*(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Division operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the division.
	 **/
	friend auto operator/(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()/static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Addition and set operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the operation.
	 **/
	friend auto operator+=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	/**
	 * @brief
	 * Soustraction and set operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the operation.
	 **/
	friend auto operator-=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	/**
	 * @brief
	 * Multiplication and set operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the operation.
	 **/
	friend auto operator*=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	/**
	 * @brief
	 * Addition operator.
	 * @param a lhs.
	 * @param b rhs.
	 * @return Result of the addition.
	 **/
	friend auto operator/=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()/static_cast<const ClassGet&>(b).Get());
		 return a;
	}
};

#endif
