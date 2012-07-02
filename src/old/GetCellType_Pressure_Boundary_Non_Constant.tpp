template <class TypeWorld,class Base>
GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetCellType_Pressure_Boundary_Non_Constant(type_input_struct in):Base(in)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetIsPressure_Boundary_Implementation_Const(const type_key& key1 __attribute__((unused)),const type_key& key2 __attribute__((unused)),const type_mac_cell& mac1 __attribute__((unused)),const type_mac_cell& mac2 __attribute__((unused)),bool b1 __attribute__((unused)),bool b2 __attribute__((unused)),const type_cell & c1 __attribute__((unused)),const type_cell &c2 __attribute__((unused)),bool b __attribute__((unused)),int sign __attribute__((unused)),int dim __attribute__((unused)),bool bret __attribute__((unused)))
{
	return bret;
}
