#ifndef MacGetVelocity_H
#define MacGetVelocity_H

#include "NLinearInterpolation.h"

#include <iostream>

/**
 * @file MacGetVelocity.h
 * @brief
 * Declaration file for class MacGetVelocity.
 **/

using namespace std;
/**
 * @brief
 * Get The Velocity in a point of space interpolating from the grid.
 * @tparam TypeWorld Type of World used.
 * @tparam TypeStagPos Type Used to know the position of speed.
 **/
template <class TypeWorld,class TypeStagPos>
class MacGetVelocity
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	NLinearInterpolation<TypeWorld> m_Interp;
	TypeStagPos& m_stag_pos;
public:
/**
 * @brief
 * Constructor
 * @param world World used to access the grid.
 * @param stag_pos Object to know the position of speed component (staggered grid).
 * @param _1_h 1 over the spacing of cell.
 **/
	MacGetVelocity(TypeWorld &world,TypeStagPos& stag_pos,const Physvector<type_dim,type_data> &_1_h );
	/**
	 * @brief
	 * Get the speed at given point by interpolation.
	 * @param pos Position where to calculate.
	 **/
	Physvector<type_dim,type_data> Get(const Physvector<type_dim,type_data> &pos);
	type_data Get(const Physvector<type_dim,type_data> &pos,int i);
};
#include "MacGetVelocity.tpp"
#endif
