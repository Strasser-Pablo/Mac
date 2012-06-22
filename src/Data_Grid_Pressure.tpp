template<typename DataBase>
void Data_Grid_Pressure<DataBase>::Pressure_Set(const type_pressure& pres)
{
	m_pres=pres;
}

template<typename DataBase>
auto Data_Grid_Pressure<DataBase>::Pressure_Get() const -> type_pressure
{
	return m_pres;
}
