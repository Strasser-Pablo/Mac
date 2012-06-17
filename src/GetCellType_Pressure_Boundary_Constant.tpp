template <class TypeWorld,class Base>
GetCellType_Pressure_Boundary_Constant<TypeWorld,Base>::GetCellType_Pressure_Boundary_Constant(type_input_struct in):Base(in)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Pressure_Boundary_Constant<TypeWorld,Base>::GetIsPressure_Boundary_Implementation_Const(const type_key& key1,const type_key& key2,const type_mac_cell& mac1,const type_mac_cell& mac2,bool b1,bool b2,const type_cell & c1,const type_cell & c2,bool b,int sign,int dim,bool bret)
{
	if(bret)
	{
		return true;
	}
	if(!b)
	{
		throw logic_error("The two cell are no direct neighboor: More than one direction.");
	}
	if(!b1||!b2)
	{
		throw logic_error("We are in a empty zone");
	}
	bool bc;
	if(sign==1)
	{
		mac2.GetConstSpeed(dim,bc);
	}
	else if(sign==-1)
	{
		mac1.GetConstSpeed(dim,bc);
	}
	else
	{
		throw logic_error("The two cell are no direct neighboor: A distance more that 1.");
	}
	return bc;
}
