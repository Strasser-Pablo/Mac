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
	 * Type pointing to the base type without additional inheritance.
	 * Because after addition of additional base class we are of this class but with another template value, we need this type to know the type.
	 **/
	typedef Data_Grid_Base_Spacing<typename DataBase::type_SubInherite_Base> type_SubInherite_Base;
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
