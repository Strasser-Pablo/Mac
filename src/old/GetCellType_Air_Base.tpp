template <class TypeWorld,class Base,class Implementation>
GetCellType_Air_Base<TypeWorld,Base,Implementation>::GetCellType_Air_Base(type_input_Base in):Base(in)
{

}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Air_Base<TypeWorld,Base,Implementation>::GetIsAir(const type_cell& c)
{
	return static_cast<Implementation&>(*this).GetIsAir_Implementation(c);
}
template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Air_Base<TypeWorld,Base,Implementation>::GetIsAir(const type_key& key)
{
	return GetIsAir(Base::KeyToType(key));
}
