#ifndef GetCellType_H

template <class TypeWorld>
class GetCellType
{
	typedef typename TypeWorld::type_cell type_cell;
	const type_cell &m_fluid;
	const type_cell &m_boundary_fluid;
	const type_cell &m_air;
	const type_cell &m_boundary_air;
public:
	GetCellType(const type_cell &fluid,const type_cell &boundary_fluid, const type_cell &air,const type_cell &boundary_air );
	bool GetIsFluid(const type_cell & cell);
	bool GetIsAir(const type_cell & cell);
	bool GetIsFluidOnly(const type_cell & cell);
	bool GetIsAirOnly(const type_cell & cell);
	bool GetIsBoundaryAir(const type_cell & cell);
	bool GetIsBoundaryFluid(const type_cell & cell);
	bool GetIsBoundary(const type_cell & cell);
	const type_cell & GetFluid();
	const type_cell & GetAir();
};

#include "GetCellType.tpp"
#endif