template <class TypeWorld,class Base>
GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetCellType_Pressure_Boundary_Non_Constant(type_input_struct in):Base(in)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Pressure_Boundary_Non_Constant<TypeWorld,Base>::GetIsPressure_Boundary_Implementation_Const(const type_key& __attribute__((unused)) key1,const type_key& __attribute__((unused)) key2,const type_mac_cell& __attribute__((unused)) mac1,const type_mac_cell& __attribute__((unused)) mac2,bool __attribute__((unused)) b1,bool __attribute__((unused)) b2,const type_cell & __attribute__((unused)) c1,const type_cell & __attribute__((unused)) c2,bool __attribute__((unused)) b,int __attribute__((unused)) sign,int __attribute__((unused)) dim,bool bret)
{
	return bret;
}
