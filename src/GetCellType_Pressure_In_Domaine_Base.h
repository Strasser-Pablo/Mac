#ifndef GetCellType_Pressure_In_Domaine_Fluid_Base_H
#define GetCellType_Pressure_In_Domaine_Fluid_Base_H
#include "Inversible_Value.h"
template <class TypeWorld,class Base,class Implementation>
class GetCellType_Pressure_In_Domaine_Base : public Base
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename Base::type_input_struct type_input_Base;
	public:
	GetCellType_Pressure_In_Domaine_Base(type_input_Base in_base);
	bool GetIsPressureInDomaine(const type_cell& c);
	bool GetIsPressureInDomaine(const type_key& key);
};
#include "GetCellType_Pressure_In_Domaine_Base.tpp"
#endif
