#include <stdexcept>
template <typename DataBase>
int Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::MaterialToInt(Material_Type m) const
{
	switch(m)
	{
		case Material_Type::Air:
			return 0;
		case Material_Type::Fluid:
			return 1;
		case Material_Type::Solid:
			return 2;
		case Material_Type::Inflow:
			return 3;
		case Material_Type::Interior:
			return 4;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp, Function MaterialToInt : Enum Value not in Enum.");
	}
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::Material_To_Type_Fluid(Material_Type m) const -> Material_Type_Fluid
{
	switch(m)
	{
		case Material_Type::Air:
			return Material_Type_Fluid::Air;
		case Material_Type::Fluid:
			return Material_Type_Fluid::Fluid;
		case Material_Type::Solid:
			return Material_Type_Fluid::Air;
		case Material_Type::Inflow:
			return Material_Type_Fluid::Fluid;
		case Material_Type::Interior:
			return Material_Type_Fluid::Fluid;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function Material_To_Type : Enum Value not in Enum.");
	}
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::Material_To_Type_Inflow(Material_Type m) const -> Material_Type_Inflow
{
	switch(m)
	{
		case Material_Type::Air:
			return Material_Type_Inflow::NoInflow;
		case Material_Type::Fluid:
			return Material_Type_Inflow::NoInflow;
		case Material_Type::Solid:
			return Material_Type_Inflow::NoInflow;
		case Material_Type::Inflow:
			return Material_Type_Inflow::Inflow;
		case Material_Type::Interior:
			return Material_Type_Inflow::NoInflow;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function Material_To_Type : Enum Value not in Enum.");
	}
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::Material_To_Type_Interior(Material_Type m) const -> Material_Type_Interior
{
	switch(m)
	{
		case Material_Type::Air:
			return Material_Type_Interior::NoInterior;
		case Material_Type::Fluid:
			return Material_Type_Interior::NoInterior;
		case Material_Type::Solid:
			return Material_Type_Interior::NoInterior;
		case Material_Type::Inflow:
			return Material_Type_Interior::NoInterior;
		case Material_Type::Interior:
			return Material_Type_Interior::Interior;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function Material_To_Type : Enum Value not in Enum.");
	}
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::Material_To_Type_Solid(Material_Type m) const -> Material_Type_Solid
{
	switch(m)
	{
		case Material_Type::Air:
			return Material_Type_Solid::NoSolid;
		case Material_Type::Fluid:
			return Material_Type_Solid::NoSolid;
		case Material_Type::Solid:
			return Material_Type_Solid::Solid;
		case Material_Type::Inflow:
			return Material_Type_Solid::NoSolid;
		case Material_Type::Interior:
			return Material_Type_Solid::NoSolid;
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function Material_To_Type : Enum Value not in Enum.");
	}
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetFluid() const -> Material_Type
{
	return Material_Type::Fluid;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetAir() const -> Material_Type
{
	return Material_Type::Air;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetSolid() const -> Material_Type
{
	return Material_Type::Solid;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetInflow() const -> Material_Type
{
	return Material_Type::Inflow;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetInterior() const -> Material_Type
{
	return Material_Type::Inflow;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetRhoAir() const ->Inversible_Value<Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::type_data_value>
{
	return m_rho_air;
}

template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetRhoFluid() const ->Inversible_Value<Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::type_data_value>
{
	return m_rho_fluid;
}


template <typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::GetRho(Material_Type c) const ->Inversible_Value<Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::type_data_value>
{
	switch(c)
	{
		case Material_Type::Air:
			return GetRhoAir();
		case Material_Type::Fluid:
			return GetRhoFluid();
		case Material_Type::Inflow:
			return GetRhoFluid();
		case Material_Type::Solid:
			return 0;
		case Material_Type::Interior:
			return GetRhoFluid();
		default:
			throw std::logic_error("In Data_GetCellType_Fluid_Air.tpp Function GetRho : Enum Value not in Enum.");
	}
}
	
template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::SetRhoFluid(Inversible_Value<type_data_value>& rho_fluid)
{
	m_rho_fluid=rho_fluid;
}

template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase>::SetRhoAir(Inversible_Value<type_data_value>& rho_air)
{
	m_rho_air=rho_air;
}

template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::SetAir()
{
	if(m_mat==Material_Type::Fluid||m_mat==Material_Type::Interior)
	{
		m_mat=Material_Type::Air;
	}
}

template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::SetFluid()
{
	if(m_mat==Material_Type::Air||m_mat==Material_Type::Interior)
	{
		m_mat=Material_Type::Fluid;
	}
}


template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::SetSolid()
{
	m_mat=Material_Type::Solid;
}

template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::SetInflow()
{
	m_mat=Material_Type::Inflow;
}

template <typename DataBase>
void Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::SetInterior()
{
	m_mat=Material_Type::Interior;
}

template<typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::GetRho() const ->Inversible_Value<type_data_value>
{
	return m_data_cell_type.GetRho(m_mat);
}


template<typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::GetRhoAir() const ->Inversible_Value<type_data_value>
{
	return m_data_cell_type.GetRhoAir();
}

template<typename DataBase>
auto Data_CellType_Fluid_Air_Solid_Inflow_Interior__InCell<DataBase>::GetRhoFluid() const ->Inversible_Value<type_data_value>
{
	return m_data_cell_type.GetRhoFluid();
}
