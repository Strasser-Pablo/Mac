#ifndef GetCellType_H

template <class TypeWorld>
class GetCellType
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	const type_cell &m_fluid;
	const type_cell &m_boundary_fluid;
	const type_cell &m_air;
	const type_cell &m_boundary_air;
	const type_data &m_rho_fluid;
	const type_data &m_rho_air;
	const type_data &m_1_rho_fluid;
	const type_data &m_1_rho_air;
public:
	GetCellType(const type_cell &fluid,const type_cell &boundary_fluid, const type_cell &air,const type_cell &boundary_air,const type_data &rho_fluid,const type_data &rho_air,const type_data &_1_rho_fluid,const type_data &_1_rho_air);
	bool GetIsFluid(const type_cell & cell);
	bool GetIsAir(const type_cell & cell);
	bool GetIsFluidOnly(const type_cell & cell);
	bool GetIsAirOnly(const type_cell & cell);
	bool GetIsBoundaryAir(const type_cell & cell);
	bool GetIsBoundaryFluid(const type_cell & cell);
	bool GetIsBoundary(const type_cell & cell);
	const type_cell & GetFluid();
	const type_cell & GetAir();
	const type_cell & GetFluidBoundary();
	const type_cell & GetAirBoundary();
	const type_data & GetRho();
	const type_data & Get1_Rho();
};

#include "GetCellType.tpp"
#endif