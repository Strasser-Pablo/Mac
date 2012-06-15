template <class TypeWorld,class Base>
GetCellType_Fluid<TypeWorld,Base>::GetCellType_Fluid(type_input_struct in):GetCellType_Fluid_Base<TypeWorld,Base,GetCellType_Fluid<TypeWorld,Base> >(in.m_base),m_fluid(in.m_fluid),m_rho(in.m_rho)
{

}

template <class TypeWorld,class Base>
bool GetCellType_Fluid<TypeWorld,Base>::GetIsFluid_Implementation(const type_cell& c)
{
	return c==m_fluid;
}
