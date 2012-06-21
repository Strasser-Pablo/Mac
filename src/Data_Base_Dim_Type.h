#ifndef Data_Base_Dim_Type_H
#define Data_Base_Dim_Type_H

template <typename TypeData,int Dim>
class Data_Base_Dim_Type
{
	public:
		static const int type_dim=Dim;
		typedef TypeData type_data_value;
};

#endif
