#ifndef GetCellType_Rho_H
#define GetCellType_Rho_H
#include "GetCellType_Rho_Base.h"
template <class TypeWorld,class Base>
class GetCellType_Rho : public GetCellType_Rho_Base<TypeWorld,Base,GetCellType_Rho<TypeWorld,Base> >
{
	typedef typename TypeWorld::type_cell type_cell;
	public:
	typedef typename Base::type_input_struct type_input_struct;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	GetCellType_Rho(type_input_struct in);
	auto GetRho_Implementation(const type_cell& c)->const Inversible_Value<type_data>;
};
#include "GetCellType_Rho.tpp"
#endif
