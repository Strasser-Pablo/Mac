#ifndef MacGravity_H
#define MacGravity_H

#include "Type_Inter.h"

/**
 * @file MacGravity.h
 * @brief
 * Declaration file for class MacGravity.
 **/

/**
 * @ingroup GR_Gravity
 * @brief
 * Apply Gravity to all cell.
 * @tparam TypeWorld type of World.
 **/
template <class TypeWorld,class GetCellType>
class MacGravity
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	const Physvector<type_dim,type_data>& m_g;
	const type_data& m_dt;
	const type_cell m_fluid;
	TypeWorld & m_world;
	GetCellType & m_GetCellType;
public:
/**
 * @brief 
 * Constructor
 * @param world World use to access grid.
 * @param g Gravity Constant used.
 * @param dt TimeStep Used.
 * @param fluid Fluid value.
 * @param neigh Method to know if some velocity component are to be considered fluide although the cell is not fluid.
 **/
	MacGravity(TypeWorld & world,const Physvector<type_dim,type_data>& g,const type_data &dt,const type_cell fluid,	GetCellType & getCellType);
/**
 * @brief
 * Do the calculation for next time step.
 **/
	void Calculate();
};

#include "MacGravity.tpp"
#endif
