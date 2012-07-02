template <class TypeWorld,class Base,class Implementation>
GetCellType_Rho_Base<TypeWorld,Base,Implementation>::GetCellType_Rho_Base(type_input_Base in_base):Base(in_base)
{
}

template <class TypeWorld,class Base,class Implementation>
auto GetCellType_Rho_Base<TypeWorld,Base,Implementation>::GetRho(const type_cell& c)->const Inversible_Value<type_data>
{
	return static_cast<Implementation&>(*this).GetRho_Implementation(c);
}

template <class TypeWorld,class Base,class Implementation>
auto GetCellType_Rho_Base<TypeWorld,Base,Implementation>::GetRho(const type_key& key)->const Inversible_Value<type_data>
{
	return GetRho(Base::KeyToType(key));
}
