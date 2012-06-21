template <typename TypeData>
Data_Pressure_Data<TypeData>::operator TypeData()
{
	return m_pres;
}


template <typename TypeData>
TypeData Data_Pressure_Data<TypeData>::Get() const
{
	return m_pres;
}
template <typename TypeData>
void Data_Pressure_Data<TypeData>::Set(const TypeData & pres)
{
	m_pres=pres;
}
