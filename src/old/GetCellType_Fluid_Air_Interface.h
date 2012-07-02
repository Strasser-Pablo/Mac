#ifndef GetCellType_Fluid_Air_Interface_H
#define GetCellType_Fluid_Air_Interface_H
#include "GetCellType_Fluid_Air_Interface_Base.h"

using namespace std;

template <class TypeWorld,class Base>
class GetCellType_Fluid_Air_Interface : public GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,GetCellType_Fluid_Air_Interface<TypeWorld,Base> >
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_key type_key;
	typedef typename TypeWorld::type_data type_data;
	typedef typename Base::type_input_struct type_input_struct;
	public:
	GetCellType_Fluid_Air_Interface(type_input_struct in);
	bool GetIsFluidAirInterface_Implementation(const type_cell& c1,const type_cell& c2);
};
#include "GetCellType_Fluid_Air_Interface.tpp"
#endif
