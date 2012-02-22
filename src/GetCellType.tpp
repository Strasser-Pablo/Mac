template <class TypeWorld>
GetCellType<TypeWorld>::GetCellType(const type_cell &fluid,const type_cell &boundary_fluid, const type_cell &air,const type_cell &boundary_air ):m_fluid(fluid),m_air(air),m_boundary_fluid(boundary_fluid),m_boundary_air(boundary_air)
{
	
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluid(const type_cell & cell)
{
	return GetIsFluidOnly(cell)||GetIsBoundaryFluid(cell);
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAir(const type_cell & cell)
{
	return GetIsAirOnly(cell)||GetIsBoundaryAir(cell);
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluidOnly(const type_cell & cell)
{
	return m_fluid==cell;
}
template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAirOnly(const type_cell & cell)
{
	return m_air==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryAir(const type_cell & cell)
{
	return m_boundary_air==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryFluid(const type_cell & cell)
{
	return m_boundary_fluid==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundary(const type_cell & cell)
{
	return GetIsBoundaryFluid(cell)||GetIsBoundaryAir(cell);
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetFluid()
{
	return m_fluid;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetAir()
{
	return m_air;
}
