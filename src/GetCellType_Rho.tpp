#include <stdexcept>
template <class TypeWorld,class Base>
GetCellType_Rho<TypeWorld,Base>::GetCellType_Rho(type_input_struct in):GetCellType_Rho_Base<TypeWorld,Base,GetCellType_Rho<TypeWorld,Base> >(in)
{
}


template <class TypeWorld,class Base>
auto GetCellType_Rho<TypeWorld,Base>::GetRho_Implementation(const type_cell& c)->const Inversible_Value<type_data>
{
	if(Base::GetIsFluid(c))
	{
		return Base::GetRhoFluid();
	}
	else if(Base::GetIsAir(c))
	{
		return Base::GetRhoAir();
	}
	else
	{
		throw runtime_error("Rho for cell that is not air and not fluid asked");
	}
}
