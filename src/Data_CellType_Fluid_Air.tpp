#include <stdexcept>
template <typename DataBase>
int Data_CellType_Fluid_Air<DataBase>::MaterialToInt(Material_Type m) const
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

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::Material_To_Type_Fluid(Material_Type m) const -> Material_Type_Fluid
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

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetFluid() const -> Material_Type
{
	return Material_Type::Fluid;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetAir() const -> Material_Type
{
	return Material_Type::Air;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetRhoAir() const ->Inversible_Value<Data_CellType_Fluid_Air<DataBase>::type_data_value>
{
	return m_rho_air;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetRhoFluid() const ->Inversible_Value<Data_CellType_Fluid_Air<DataBase>::type_data_value>
{
	return m_rho_fluid;
}


template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetRho(Material_Type c) const ->Inversible_Value<Data_CellType_Fluid_Air<DataBase>::type_data_value>
{
	switch(c)
	{
		case Material_Type::Air:
			return GetRhoAir();
		case Material_Type::Fluid:
			return GetRhoFluid();
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function GetRho : Enum Value not in Enum.");
	}
}
	
template <typename DataBase>
void Data_CellType_Fluid_Air<DataBase>::SetRhoFluid(Inversible_Value<type_data_value>& rho_fluid)
{
	m_rho_fluid=rho_fluid;
}

template <typename DataBase>
void Data_CellType_Fluid_Air<DataBase>::SetRhoAir(Inversible_Value<type_data_value>& rho_air)
{
	m_rho_air=rho_air;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air<DataBase>::GetInCell() const -> Data_CellType_Fluid_Air<DataBase>::type_Cell_type__InCell
{
	return type_Cell_type__InCell(*this);
}


template <typename DataBase>
void Data_CellType_Fluid_Air__InCell<DataBase>::SetAir()
{
	m_mat=Material_Type::Air;
}

template <typename DataBase>
void Data_CellType_Fluid_Air__InCell<DataBase>::SetFluid()
{
	m_mat=Material_Type::Fluid;
}

template<typename DataBase>
auto Data_CellType_Fluid_Air__InCell<DataBase>::GetRho() const ->Inversible_Value<type_data_value>
{
	return m_data_cell_type.GetRho(m_mat);
}
