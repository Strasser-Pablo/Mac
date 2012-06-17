template <class TypeWorld,class Base>
GetCellType_Pressure_Boundary_Domaine<TypeWorld,Base>::GetCellType_Pressure_Boundary_Domaine(type_input_struct in):GetCellType_Pressure_Boundary_Base<TypeWorld,Base,GetCellType_Pressure_Boundary_Domaine<TypeWorld,Base> >(in)
{
}

#include <iostream>
using namespace std;

template <class TypeWorld,class Base>
bool GetCellType_Pressure_Boundary_Domaine<TypeWorld,Base>::GetIsPressure_Boundary_Implementation(const type_key& key1,const type_key& key2,const type_mac_cell& mac1,const type_mac_cell& mac2,bool b1,bool b2,const type_cell & c1,const type_cell & c2)
{
	bool b=Base::GetIsPressureInDomaine(c1)^Base::GetIsPressureInDomaine(c2);
	return Base::GetIsPressure_Boundary_Implementation_Const(key1,key2,mac1,mac2,b1,b2,c1,c2,b);
}
