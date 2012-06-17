#ifndef GetCellType_Pressure_Boundary_Base_H
#define GetCellType_Pressure_Boundary_Base_H
template <class TypeWorld,class Base,class Implementation>
class GetCellType_Pressure_Boundary_Base: public Base
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename TypeWorld::type_mac_cell type_mac_cell;
	typedef typename Base::type_input_struct type_input_Base;
	public:
	GetCellType_Pressure_Boundary_Base(type_input_Base in_base);
	bool GetIsPressure_Boundary(const type_key& key1,const type_key& key2);
	bool GetIsPressure_Boundary(const type_key& key,int sign,int dim);
};
#include "GetCellType_Pressure_Boundary_Base.tpp"
#endif
