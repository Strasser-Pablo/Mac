template <class TypeWorld,class Base,class Implementation>
GetCellType_Fluid_Base<TypeWorld,Base,Implementation>::GetCellType_Fluid_Base(type_input_Base in):Base(in)
{

}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Fluid_Base<TypeWorld,Base,Implementation>::GetIsFluid(const type_cell& c)
{
	return static_cast<Implementation&>(*this).GetIsFluid_Implementation(c);
}
template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Fluid_Base<TypeWorld,Base,Implementation>::GetIsFluid(const type_key& key)
{
	return GetIsFluid(Base::KeyToType(key));
}
