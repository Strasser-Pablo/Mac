template <class TypeWorld,class Base>
GetCellType_Pressure_In_Domaine_Fluid_Only<TypeWorld,Base>::GetCellType_Pressure_In_Domaine_Fluid_Only(type_input_struct in):GetCellType_Pressure_In_Domaine_Base<TypeWorld,Base,GetCellType_Pressure_In_Domaine_Fluid_Only<TypeWorld,Base> >(in)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Pressure_In_Domaine_Fluid_Only<TypeWorld,Base>::GetIsPressureInDomaine_Implementation(const type_cell& c)
{
	return Base::GetIsFluid(c);
}

template <class TypeWorld,class Base>
auto GetCellType_Pressure_In_Domaine_Fluid_Only<TypeWorld,Base>::GetRhoPressureInDomaine()->const Inversible_Value<type_data>
{
	return Base::GetRhoFluid();
}
