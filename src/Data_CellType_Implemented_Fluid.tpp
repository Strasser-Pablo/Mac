template <typename Implementation,typename Parent>
bool Data_CellType_Implemented_Fluid<Implementation,Parent>::GetIsFluid(Material_Type c)
{
	return static_cast<Implementation&> (*this).Material_To_Type_Fluid(c)==Data_CellType_Implemented_Fluid_Traits<Parent,Implementation>::m_fluid;
}
