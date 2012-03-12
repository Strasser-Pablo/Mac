#ifndef GetCellType_H
#include "Type_Inter.h"

template <class TypeWorld>
class GetCellType
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	const type_cell &m_fluid;
	const type_cell &m_boundary_fluid;
	const type_cell &m_air;
	const type_cell &m_boundary_air;
	const type_data &m_rho_fluid;
	const type_data &m_rho_air;
	const type_data &m_1_rho_fluid;
	const type_data &m_1_rho_air;
	const type_data &m_1_rho_inter;
	const type_data &m_rho_inter;
	const type_data &m_rho_inter_bound;
	const type_data &m_1_rho_inter_bound;
	TypeWorld &m_world;
public:
	GetCellType(TypeWorld& world,const type_cell &fluid,const type_cell &boundary_fluid, const type_cell &air,const type_cell &boundary_air,const type_data &rho_fluid,const type_data &rho_air,const type_data &_1_rho_fluid,const type_data &_1_rho_air,const type_data &rho_inter,const type_data& _1_rho_inter,const type_data &rho_inter_bound,const type_data& _1_rho_inter_bound);
	bool GetIsFluid(const type_cell & cell);	
	bool GetIsAir(const type_cell & cell);
	bool GetIsFluidOnly(const type_cell & cell);
	bool GetIsAirOnly(const type_cell & cell);
	bool GetIsBoundaryAir(const type_cell & cell);
	bool GetIsBoundaryFluid(const type_cell & cell);
	bool GetIsBoundary(const type_cell & cell);

	bool GetIsFluid(const type_key & key);	
	bool GetIsAir(const type_key & key);
	bool GetIsFluidOnly(const type_key & key);
	bool GetIsAirOnly(const type_key & key);
	bool GetIsBoundaryAir(const type_key & key);
	bool GetIsBoundaryFluid(const type_key & key);
	bool GetIsBoundary(const type_key & key);
	const type_cell & GetFluid();
	const type_cell & GetAir();
	const type_cell & GetFluidBoundary();
	const type_cell & GetAirBoundary();
	const type_data & GetFluidRho();
	const type_data & GetFluid1_Rho();
	const type_data & GetAirRho();
	const type_data & GetAir1_Rho();
	const type_data & GetInterRho();
	const type_data & GetInter1_Rho();
	const type_data & GetInterBoundRho();
	const type_data & GetInterBound1_Rho();
	Type_Inter GetInter(const type_key & key1,const type_key &key2);
	Type_Inter GetInter(const type_key & key1,int i,int sign=-1);
	const type_data & GetRhoInter(const type_key & key1,const type_key &key2);
	const type_data & GetRhoInter(const type_key &key1,int i,int sign=-1);
	const type_data & Get1_RhoInter(const type_key & key1,const type_key &key2);
	const type_data & Get1_RhoInter(const type_key &key1,int i,int sign=-1);
};

#include "GetCellType.tpp"
#endif
