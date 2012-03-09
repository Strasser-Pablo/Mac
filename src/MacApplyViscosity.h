#ifndef MacApplyViscosity_H
#define MacApplyViscosity_H

#include "ComputeSpeedLaplacien.h"
#include "Type_Inter.h"
/**
 * @file MacApplyViscosity.h
 * @brief
 * Declaration file for class MacApplyViscosity.
 **/

/**
 * @brief
 * Add the viscosity force contribution. Calculating the laplacien.
 * @tparam TypeWorld World type to use.
 **/
template<class TypeWorld,class GetTypeCell>
class MacApplyViscosity
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	const type_data & m_viscosity;
	const type_data& m_dt;
	TypeWorld & m_world;
	ComputeSpeedLaplacien<TypeWorld> m_lap;
	GetTypeCell &m_GetTypeCell;
public:
/**
 * @brief
 * Constructor.
 * @param world World to use.
 * @param viscosity Viscosity value.
 * @param dt Time step used.
 * @param _1_h Vector of spacing in all direction.
 * @param fluid Fluid cell value.
 **/
	MacApplyViscosity(TypeWorld &world,const type_data &viscosity, const type_data & dt,const Physvector<type_dim,type_data> & _1_h,GetTypeCell &getTypeCell);
	/**
	 * @brief
	 * Do the calculation.
	 **/
	void Calculate();
};
#include "MacApplyViscosity.tpp"

#endif
