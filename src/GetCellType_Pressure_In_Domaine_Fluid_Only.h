#ifndef GetCellType_Pressure_In_Domaine_Fluid_Only_H
#define GetCellType_Pressure_In_Domaine_Fluid_Only_H
#include "GetCellType_Pressure_In_Domaine_Base.h"

template <class TypeWorld,class Base>
class GetCellType_Pressure_In_Domaine_Fluid_Only : public GetCellType_Pressure_In_Domaine_Base<TypeWorld,Base,GetCellType_Pressure_In_Domaine_Fluid_Only<TypeWorld,Base> >
{
	public:
	typedef typename Base::type_input_struct type_input_struct;
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	public:
	GetCellType_Pressure_In_Domaine_Fluid_Only(type_input_struct in);
	bool GetIsPressureInDomaine_Implementation(const type_cell& c);
	auto GetRhoPressureInDomaine()->const Inversible_Value<type_data>;
};
#include "GetCellType_Pressure_In_Domaine_Fluid_Only.tpp"
#endif
