#ifndef Data_Base_Dim_Type_H
#define Data_Base_Dim_Type_H
#include "Physvector.h"
#include "Inversible_Value.h"

template<typename Data_Base,typename InheritedWith> 
class Data_Base_Dim_Type_Base;

template <typename TypeData,int Dim>
class Data_Base_Dim_Type
{
	public:
		static const int type_dim=Dim;
		typedef TypeData type_data_value;
		typedef Physvector<type_dim,type_data_value> type_data_vector;
		template<typename Data_Base,typename InheritedWith> 
		using type_base_base=Data_Base_Dim_Type_Base<Data_Base, InheritedWith>;
};

template<typename Data_Base,typename InheritedWith> 
class Data_Base_Dim_Type_Base : public InheritedWith
{
	public:
		static const int type_dim=Data_Base::Dim;
		typedef typename Data_Base::type_data_value type_data_value;
		typedef typename Data_Base::type_data_vector type_data_vector;
		Data_Base_Dim_Type_Base(const Data_Base &base,const InheritedWith & in) : InheritedWith(in)
		{
		}
};
#endif
