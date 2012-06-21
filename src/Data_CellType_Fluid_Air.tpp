#include <stdexcept>
template <typename TypeData>
int Data_CellType_Fluid_Air<TypeData>::MaterialToInt(Material_Type m)
{
	switch(m)
	{
		case Material_Type::Air:
			return 0;
		case Material_Type::Fluid:
			return 1;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp, Function MaterialToInt : Enum Value not in Enum.");
	}
}

template <typename TypeData>
auto Data_CellType_Fluid_Air<TypeData>::Material_To_Type_Fluid(Material_Type m) -> Material_Type_Fluid
{
	switch(m)
	{
		case Material_Type::Air:
			return Material_Type_Fluid::Air;
		case Material_Type::Fluid:
			return Material_Type_Fluid::Fluid;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function Material_To_Type : Enum Value not in Enum.");
	}
}

template <typename TypeData>
auto Data_CellType_Fluid_Air<TypeData>::GetFluid() -> Material_Type
{
	return Material_Type::Fluid;
}

template <typename TypeData>
auto Data_CellType_Fluid_Air<TypeData>::GetAir() -> Material_Type
{
	return Material_Type::Air;
}

template <typename TypeData>
auto Data_CellType_Fluid_Air<TypeData>::GetRhoAir()->Inversible_Value<TypeData>
{
	return m_rho_air;
}

template <typename TypeData>
auto Data_CellType_Fluid_Air<TypeData>::GetRhoFluid()->Inversible_Value<TypeData>
{
	return m_rho_fluid;
}
	
template <typename TypeData>
void Data_CellType_Fluid_Air<TypeData>::SetRhoFluid(Inversible_Value<TypeData>& rho_fluid)
{
	m_rho_fluid=rho_fluid;
}

template <typename TypeData>
void Data_CellType_Fluid_Air<TypeData>::SetRhoAir(Inversible_Value<TypeData>& rho_air)
{
	m_rho_air=rho_air;
}
