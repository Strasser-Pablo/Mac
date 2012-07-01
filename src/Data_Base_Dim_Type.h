#ifndef Data_Base_Dim_Type_H
#define Data_Base_Dim_Type_H
#include "Physvector.h"
#include "Inversible_Value.h"

template<typename Data_Base,typename InheritedWith>
class Data_Base_Dim_Type_Base;

/**
 * @ingroup GR_DataBase_Base
 *
 * @brief
 * Define typedef and static constant for type used in other class.
 * The following type are used:
 * - Physvector for vector.
 *
 * This class is mean to serve as base class and is mean to be derivated to add additional information.
 *
 * @tparam TypeData Base type used for numeric floating point calculation. Expected to be a type like double or float.
 * @tparam Dim A value template that is the dimension of the problem.
 **/
template <typename TypeData,int Dim>
class Data_Base_Dim_Type
{
	public:
		/**
		 * @brief
		 * Dimension of the Problem.
		 **/
		static const int type_dim=Dim;
		/**
		 * @brief
		 * Basic Type for floating point calculation.
		 * Expected to be a type like double or float.
		 **/
		typedef TypeData type_data_value;
		/**
		 * @brief
		 * Vector of size type_dim and type type_data_value.
		 * This vector has method for setting and getting value. And arithmetic operation.
		 **/
		typedef Physvector<type_dim,type_data_value> type_data_vector;
		/**
		 * @brief
		 * Type where the base class of this class has as new base InheritedWith
		 * @tparam InheritedWith Class to inherit with.
		 **/
		template <typename InheritedWith>
		using type_DataBase_SubInherite=Data_Base_Dim_Type_Base<Data_Base_Dim_Type<TypeData,Dim>,InheritedWith>;
		/**
		 * @brief
		 * Type pointing to the base type without additional inheritance.
		 * This has the same type.
		 **/
		typedef  Data_Base_Dim_Type<type_data_value,type_dim> type_SubInherite_Base;
};

/**
 * @ingroup GR_DataBase_Base
 *
 * @brief
 * Class created by Data_Base_Dim_Type type_DataBase_SubInherite to give the same fonctionality but with another base class.
 *
 * The reason of this is to give more priority for typedef and method to this class as InheritedWith.
 * The following type are used:
 *
 * @tparam Data_Base Data_Base_Dim_Type object used to created this one.
 * @tparam InheritedWith class with which we inherit.
 **/
template<typename Data_Base,typename InheritedWith>
class Data_Base_Dim_Type_Base : public InheritedWith
{
	public:
		/**
		 * @brief
		 * Dimension of the Problem.
		 **/
		static const int type_dim=Data_Base::type_dim;
		/**
		 * @brief
		 * Basic Type for floating point calculation.
		 * Expected to be a type like double or float.
		 **/
		typedef typename Data_Base::type_data_value type_data_value;
		/**
		 * @brief
		 * Vector of size type_dim and type type_data_value.
		 * This vector has method for setting and getting value. And arithmetic operation.
		 **/
		typedef typename Data_Base::type_data_vector type_data_vector;
		/**
		 * @brief
		 * Type where the base class of this class has as new base InheritedWith
		 * Equivalent to this type.
		 * @tparam InheritedWith2 Class to inherit with.
		 **/
		template <typename InheritedWith2>
		using type_DataBase_SubInherite=Data_Base_Dim_Type_Base<Data_Base_Dim_Type<type_data_value,type_dim>,InheritedWith2>;
		/**
		 * @brief
		 * Type pointing to the base type without additional inheritance.
		 * This has the same type as Data_Base.
		 **/
		typedef  Data_Base_Dim_Type<type_data_value,type_dim> type_SubInherite_Base;
		Data_Base_Dim_Type_Base(const type_SubInherite_Base& base __attribute__ ((unused)), const InheritedWith& in): InheritedWith(in)
		{
		}
};
#endif
