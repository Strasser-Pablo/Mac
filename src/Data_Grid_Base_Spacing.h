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
template <typename DataBase,typename Type_Data_Vector>
class Data_Grid_Base_Spacing : public DataBase
{
	public:
	/**
	 * @brief
	 * Type of vector.
	 **/
	typedef Type_Data_Vector type_data_vector;
	typedef Inversible_Value<Type_Data_Vector> type_data_inversible_vector;
	/**
	 * @brief
	 * Spacing of the vector.
	 **/
	Inversible_Value<type_data_vector> m_h;
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
