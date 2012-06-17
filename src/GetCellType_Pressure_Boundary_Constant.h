#ifndef GetCellType_Pressure_Boundary_Constant_H
#define GetCellType_Pressure_Boundary_Constant_H

#include <stdexcept>
using namespace std;

template <class TypeWorld,class Base>
class GetCellType_Pressure_Boundary_Constant: public Base
{
	public:
	typedef typename Base::type_input_struct type_input_struct;
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename TypeWorld::type_mac_cell type_mac_cell;
	static const int type_dim=TypeWorld::type_dim;
	public:
	GetCellType_Pressure_Boundary_Constant(type_input_struct in);
	bool GetIsPressure_Boundary_Implementation_Const(const type_key& __attribute__((unused)) key1,const type_key& __attribute__((unused)) key2,const type_mac_cell& mac1,const type_mac_cell&  mac2,bool b1,bool b2,const type_cell & __attribute__((unused)) c1,const type_cell & __attribute__((unused)) c2,bool b,int sign,int dim,bool bret);
};

#include "GetCellType_Pressure_Boundary_Constant.tpp"
#endif
