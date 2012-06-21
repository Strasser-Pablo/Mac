template <typename Implementation,typename Parent>
bool Data_CellType_Implemented_Air<Implementation,Parent>::GetIsAir(Material_Type c)
{
	return static_cast<Implementation&> (*this).Material_To_Type_Fluid(c)==Data_CellType_Implemented_Air_Traits<Parent,Implementation>::m_air;
}
