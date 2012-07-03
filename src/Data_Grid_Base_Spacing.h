#ifndef Data_Grid_Base_Spacing_H
#define Data_Grid_Base_Spacing_H
#include "Inversible_Value.h"
#include "Physvector.h"

#include "Inversible_Value_Vect.h"

/**
 * @ingroup GR_DataBase
 * @brief
 * Class where the spacing of the grid is stored.
 **/
template <typename DataBase>
class Data_Grid_Base_Spacing : public DataBase
{
	public:
	/**
	 * @brief
	 * Type of vector.
	 **/
	typedef typename DataBase::type_data_vector type_data_vector;
	/**
	 * @brief
	 * Spacing of the vector.
	 **/
	Inversible_Value<type_data_vector> m_h;
	/**
	 * @brief
	 * Type where the base class of this class has as new base InheritedWith
	 * @tparam InheritedWith Class to inherit with.
	 **/
	template <typename InheritedWith>
	using type_DataBase_SubInherite=Data_Grid_Base_Spacing<typename DataBase::template type_DataBase_SubInherite<InheritedWith> >;
	/**
	 * @brief
	 * Type pointing to the base type without additional inheritance.
	 * Because after addition of additional base class we are of this class but with another template value, we need this type to know the type.
	 **/
	typedef Data_Grid_Base_Spacing<typename DataBase::type_SubInherite_Base> type_SubInherite_Base;
	/**
	 * @brief
	 * Constructor to create a derived DataBase
	 **/
	template<typename InheritedWith> 
	Data_Grid_Base_Spacing(const  type_SubInherite_Base& base, const InheritedWith& in): DataBase(base,in)
	{
	}
	/**
	 * @brief
	 * Defualt Constructor
	 **/
	Data_Grid_Base_Spacing()
	{
	}
	Data_Grid_Base_Spacing(const DataBase &base):DataBase(base)
	{
	}
};
#endif
