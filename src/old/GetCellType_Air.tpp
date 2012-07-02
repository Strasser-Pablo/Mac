template <class TypeWorld,class Base>
GetCellType_Air<TypeWorld,Base>::GetCellType_Air(type_input_struct in):GetCellType_Air_Base<TypeWorld,Base,GetCellType_Air<TypeWorld,Base> >(in.m_base),m_air(in.m_air),m_rho(in.m_rho)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Air<TypeWorld,Base>::GetIsAir_Implementation(const type_cell& c)
{
	return c==m_air;
}

template <class TypeWorld,class Base>
auto GetCellType_Air<TypeWorld,Base>::GetRhoAir() -> const Inversible_Value<type_data>
{
	return m_rho;
}
