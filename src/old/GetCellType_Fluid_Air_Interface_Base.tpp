template <class TypeWorld,class Base,class Implementation>
GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,Implementation>::GetCellType_Fluid_Air_Interface_Base(type_input_Base in_base):Base(in_base)
{

}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,Implementation>::GetIsFluidAirInterface(const type_cell& c1,const type_cell& c2)
{
	return static_cast<Implementation&>(*this).GetIsFluidAirInterface_Implementation(c1,c2);
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,Implementation>::GetIsFluidAirInterface(const type_key& key1,const type_key& key2)
{
	return GetIsFluidAirInterface(Base::KeyToType(key1),Base::KeyToType(key2));
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Fluid_Air_Interface_Base<TypeWorld,Base,Implementation>::GetIsFluidAirInterface(const type_key& key,int sign,int dim)
{
	type_key key2=key;
	key2.GetRef(dim)+=sign;
	return GetIsFluidAirInterface(key,key2);
}
