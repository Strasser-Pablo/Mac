template <typename Implementation,typename Parent>
bool Data_CellType_Implemented_Fluid<Implementation,Parent>::GetIsFluid(Material_Type c) const
{
	return static_cast<const Implementation&> (*this).Material_To_Type_Fluid(c)==Data_CellType_Implemented_Fluid_Traits<Parent,Implementation>::m_fluid;
}

template <typename Implementation>
bool Data_CellType_Implemented_Fluid__InCell<Implementation>::GetIsFluid() const
{
	return static_cast<const Implementation&>(*this).m_data_cell_type.GetIsFluid(static_cast<const Implementation&>(*this).m_mat);
}
