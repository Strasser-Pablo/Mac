#ifndef MacCalculateCirculation_H
#define MacCalculateCirculation_H

#include "Physvector.h"
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
template <class TypeWorld>
class MacCalculateCirculation
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	TypeWorld & m_world;
	Physvector<type_dim,type_data>& m_h;
public:
	MacCalculateCirculation(TypeWorld & world,Physvector<type_dim,type_data>& h);
	void Calculate();
};

#include "MacCalculateCirculation.tpp"
#endif
