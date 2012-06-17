template <class TypeWorld,class Base,class Implementation>
GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetCellType_Pressure_Boundary_Base(type_input_Base in_base):Base(in_base)
{
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetIsPressure_Boundary(const type_key& key1,const type_key& key2)
{
	type_mac_cell mac1;
	type_mac_cell mac2;
	bool b1=Base::KeyToMacCell(key1,mac1);
	bool b2=Base::KeyToMacCell(key2,mac2);
	return static_cast<Implementation&>(*this).GetIsPressure_Boundary_Implementation(key1,key2,mac1,mac2,b1,b2,Base::KeyToType(key1),Base::KeyToType(key2));
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetIsPressure_Boundary(const type_key& key,int sign,int dim)
{
	type_key key2=key;
	key2.GetRef(dim)+=sign;
	return GetIsPressure_Boundary(key,key2);
}
