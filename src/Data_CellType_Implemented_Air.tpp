template <typename Implementation,typename Parent>
bool Data_CellType_Implemented_Air<Implementation,Parent>::GetIsAir(Material_Type c) const
{
	return static_cast<const Implementation&> (*this).Material_To_Type_Fluid(c)==Data_CellType_Implemented_Air_Traits<Parent,Implementation>::m_air;
}

template <typename Implementation>
bool Data_CellType_Implemented_Air__InCell<Implementation>::GetIsAir() const
{
	return static_cast<const Implementation&>(*this).m_data_cell_type.GetIsAir(static_cast<const Implementation&>(*this).m_mat);
}
