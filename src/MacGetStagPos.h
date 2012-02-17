#ifndef MacGetStagPos_H
#define MacGetStagPos_H

#include "Physvector.h"

#include <iostream>

#include "NeighborsVelocity.h"


/**
 * @file MacGetStagPos.h
 * @brief Declaration file for class MacGetStagPos.
 **/

using namespace std;
/**
 * @brief
 * Give the relatif position from the center of the different speed component.
 * @tparam TypeWorld Type of world.
 **/
template<class TypeWorld>
class MacGetStagPos{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	const Physvector<type_dim,type_data> &m_h;
	NeighborsVelocity<type_dim,int> m_neighv;
public:
/**
 * @brief
 * Constructor
 * @param h Spacing of the cell.
 **/
	MacGetStagPos(const Physvector<type_dim,type_data> &h);
/**
 * @brief
 * Get Position of ind component of speed.
 * @param key Position of the cell.
 * @param ind Index of speed component.
 **/
	Physvector<type_dim,type_data> Get( const Physvector<type_dim,int> key,int ind);
	/**
 * @brief
 * Get Correction from center of Position of ind component of speed.
 * @param key Position of the cell.
 * @param ind Index of speed component.
 **/
	Physvector<type_dim,type_data> GetCorrectLow( const Physvector<type_dim,type_data> pos,int ind);
	
		/**
 * @brief
 * Get Correction from center of Position of ind component of speed.
 * @param key Position of the cell.
 * @param ind Index of speed component.
 **/
	Physvector<type_dim,type_data> GetCorrect( const Physvector<type_dim,type_data> pos,int ind);
/**
	 * @brief
	 * Return an object representing witch cell have a velocity at boundary.
	 **/
	NeighborsVelocity<type_dim,int> GetNeighborsVelocity();
};
#include "MacGetStagPos.tpp"
#endif