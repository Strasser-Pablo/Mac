template <class TypeWorld,class Base,class Implementation>
GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetCellType_Pressure_Boundary_Base(type_input_Base in_base):Base(in_base)
{
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetIsPressure_Boundary(const type_key& key1,const type_key& key2)
{
	int sign;
	int dim;
	bool ret=Base::KeyToSignDiff(key1,key2,sign,dim);;
	return GetIsPressure_Boundary_Impl(key1,key2,ret,sign,dim);
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetIsPressure_Boundary(const type_key& key,int sign,int dim)
{
	type_key key2;
	Base::SignDiffToKey(key,key2,sign,dim);
	return GetIsPressure_Boundary_Impl(key,key2,true,sign,dim);
}

template <class TypeWorld,class Base,class Implementation>
bool GetCellType_Pressure_Boundary_Base<TypeWorld,Base,Implementation>::GetIsPressure_Boundary_Impl(const type_key& key1,const type_key & key2,bool b,int sign,int dim)
{
	type_mac_cell mac1;
	type_mac_cell mac2;
	type_cell c1;
	type_cell c2;
	bool b1=Base::KeyToMacCellAndType(key1,mac1,c1);
	bool b2=Base::KeyToMacCellAndType(key2,mac2,c2);
	return static_cast<Implementation&>(*this).GetIsPressure_Boundary_Implementation(key1,key2,mac1,mac2,b1,b2,c1,c2,b,sign,dim);
}
