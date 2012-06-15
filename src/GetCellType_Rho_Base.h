#ifndef GetCellType_Rho_Base_H
#define GetCellType_Rho_Base_H
#include "Inversible_Value.h"

template <class TypeWorld,class Base,class Implementation>
class GetCellType_Rho_Base : public Base
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename Base::type_input_struct type_input_Base;
	public:
	GetCellType_Rho_Base(type_input_Base in_base);
	auto GetRho(const type_cell& c)->const Inversible_Value<type_data>;
	auto GetRho(const type_key& key)->const Inversible_Value<type_data>;
};
#include "GetCellType_Rho_Base.tpp"
#endif
