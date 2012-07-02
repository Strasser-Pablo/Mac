#ifndef Data_Operation_Vector_Arithmetic_H
#define Data_Operation_Vector_Arithmetic_H

/**
 * @ingroup GR_Data_Operation
 * @brief
 * Class to be derived to add vector arithmetic. Witch an Set and Get Method to acess operation that can be used in arithmetic operation.
 * @tparam Implementation Vector that we are implementing.
 * @tparam TypeData Scalar type.
 * @tparam ClassGet Class that has the Set and Get operation for vector. We static cast to ClassGet from an Implementation instance.
 **/
template <typename Implementation,typename ClassGet,typename TypeData>
class Data_Operation_Vector_Arithmetic
{
	/**
	 * @brief
	 * Vector addition operation.
	 * @param a lhs vector.
	 * @param b rhs vector.
	 * @return Vector result.
	 **/
	friend auto operator+(const Implementation & a,const Implementation & b)-> Implementation 
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Vector soustraction operation.
	 * @param a lhs vector.
	 * @param b rhs vector.
	 * @return Vector result.
	 **/
	friend auto operator-(const Implementation & a,const Implementation & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
	}
	/**
	 * @brief
	 * Vector multiplication with an scalar.
	 * @param a lhs vector.
	 * @param b rhs scalar value.
	 * @return Vector result.
	 **/
	friend auto operator*(const Implementation & a,const TypeData & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*b);
	}
	/**
	 * @brief
	 * Vector multiplication operation.
	 * @param a lhs scalar value.
	 * @param b rhs vector.
	 * @return Vector result.
	 **/
	friend auto operator*(const TypeData & b,const Implementation & a)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*b);
	}
	/**
	 * @brief
	 * Vector division operation.
	 * @param a lhs vector.
	 * @param b rhs scalar value.
	 * @return Vector result.
	 **/
	friend auto operator/(const Implementation & a,const TypeData & b)-> Implementation
	{
		return Implementation(static_cast<const ClassGet&>(a).Get()*(1/b));
	}
	/**
	 * @brief
	 * Vector addition and set operation.
	 * @param a lhs vector.
	 * @param b rhs vector.
	 * @return Vector result.
	 **/
	friend auto operator+=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()+static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	/**
	 * @brief
	 * Vector soustraction and set operation.
	 * @param a lhs vector.
	 * @param b rhs vector.
	 * @return Vector result.
	 **/
	friend auto operator-=(Implementation & a,const Implementation & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()-static_cast<const ClassGet&>(b).Get());
		 return a;
	}
	/**
	 * @brief
	 * Vector multiplication and set operation.
	 * @param a lhs vector.
	 * @param b rhs scalar value.
	 * @return Vector result.
	 **/
	friend auto operator*=(Implementation & a,const TypeData & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*b);
		 return a;
	}
	/**
	 * @brief
	 * Vector division and set operation.
	 * @param a lhs vector.
	 * @param b rhs scalar value.
	 * @return Vector result.
	 **/
	friend auto operator/=(Implementation & a,const TypeData & b)-> Implementation&
	{
		 static_cast<ClassGet&>(a).Set(static_cast<ClassGet&>(a).Get()*(1/b));
		 return a;
	}
};

#endif
