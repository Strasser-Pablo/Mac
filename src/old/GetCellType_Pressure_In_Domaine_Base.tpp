template <class TypeWorld,class Base,class Implementation>
GetCellType_Pressure_In_Domaine_Base<TypeWorld,Base,Implementation>::GetCellType_Pressure_In_Domaine_Base(type_input_Base in_base):Base(in_base)
{
}
template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_In_Domaine_Base<TypeWorld,Base,Implementation>::GetIsPressureInDomaine(const type_cell& c)
{
	return static_cast<Implementation&>(*this).GetIsPressureInDomaine_Implementation(c);
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_In_Domaine_Base<TypeWorld,Base,Implementation>::GetIsPressureInDomaine(const type_key& key)
{
	return GetIsPressureInDomaine(Base::KeyToType(key));
}
