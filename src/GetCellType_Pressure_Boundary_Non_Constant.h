#ifndef GetCellType_Pressure_Boundary_Non_Constant_H
#define GetCellType_Pressure_Boundary_Non_Constant_H

template <class TypeWorld,class Base>
class GetCellType_Pressure_Boundary_Non_Constant: public Base
{
	public:
	typedef typename Base::type_input_struct type_input_struct;
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename TypeWorld::type_mac_cell type_mac_cell;
	public:
	GetCellType_Pressure_Boundary_Non_Constant(type_input_struct in);
	bool GetIsPressure_Boundary_Implementation_Const(const type_key& key1,const type_key& key2,const type_mac_cell& mac1,const type_mac_cell& mac2,bool b1,bool b2,const type_cell & c1,const type_cell & c2,bool b);
};

#include "GetCellType_Pressure_Boundary_Non_Constant.tpp"
#endif
