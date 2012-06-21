#ifndef Data_Grid_Base_Spacing_H
#define Data_Grid_Base_Spacing_H
#include "Inversible_Value.h"
#include "Physvector.h"

#include "Inversible_Value_Vect.h"
template <typename DataBase>
class Data_Grid_Base_Spacing : public DataBase
{
	public:
		typedef typename DataBase::type_data_vector type_data_vector;
		Inversible_Value<type_data_vector> m_h;
};
#endif
