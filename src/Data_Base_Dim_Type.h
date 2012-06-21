#ifndef Data_Base_Dim_Type_H
#define Data_Base_Dim_Type_H
#include "Physvector.h"
#include "Inversible_Value.h"

template <typename TypeData,int Dim>
class Data_Base_Dim_Type
{
	public:
		static const int type_dim=Dim;
		typedef TypeData type_data_value;
		typedef Physvector<type_dim,type_data_value> type_data_vector;
};

#endif
