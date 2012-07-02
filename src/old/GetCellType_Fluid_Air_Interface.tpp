template <class TypeWorld,class Base>
GetCellType_Fluid_Air_Interface<TypeWorld,Base>::GetCellType_Fluid_Air_Interface(type_input_struct in):GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,GetCellType_Fluid_Air_Interface<TypeWorld,Base> >(in)
{
}

template <class TypeWorld,class Base>
bool GetCellType_Fluid_Air_Interface<TypeWorld,Base>::GetIsFluidAirInterface_Implementation(const type_cell& c1,const type_cell& c2)
{
	if((Base::GetIsFluid(c1)&&Base::GetIsAir(c2))||(Base::GetIsFluid(c2)&&Base::GetIsAir(c1)))
	{
		return true;
	}
	return false;
}
