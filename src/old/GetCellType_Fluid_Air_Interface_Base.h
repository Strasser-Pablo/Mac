#ifndef GetCellType_Fluid_Air_Interface_Base_H
#define GetCellType_Fluid_Air_Interface_Base_H

template <class TypeWorld,class Base,class Implementation>
class GetCellType_Fluid_Air_Interface_Base : public Base
{
	
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename Base::type_input_struct type_input_Base;
	static const int type_dim=TypeWorld::type_dim;
	public:
	GetCellType_Fluid_Air_Interface_Base(type_input_Base in_base);
	bool GetIsFluidAirInterface(const type_cell& c1,const type_cell& c2);
	bool GetIsFluidAirInterface(const type_key& key1,const type_key& key2);
	bool GetIsFluidAirInterface(const type_key& key,int sign,int dim);
};

#include "GetCellType_Fluid_Air_Interface_Base.tpp"
#endif
