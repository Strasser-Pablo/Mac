template <class TypeWorld,class Base>
GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetCellType_Pressure_Boundary_Non_Constant(type_input_struct in):Base(in)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetIsPressure_Boundary_Implementation_Const(const type_key& key1,const type_key& key2,const type_mac_cell& mac1,const type_mac_cell& mac2,bool b1,bool b2,const type_cell & c1,const type_cell & c2,bool b)
{
	return b;
}
