#ifndef UpdateCellFluid_H
#define UpdateCellFluid_H
#include "ParticleToKey.h"

#include <iostream>
using namespace std;
/**
 * @file UpdateCellFluid.h
 * @brief
 * Declaration file for class UpdateCellFluid.
 **/

/**
 * @brief
 * Update the cell that have fluid and their layer.
 * @tparam TypeWorld type of the World used.
 * 
 * If a particle go lower thant -5 in the seconde coordinate.
 * It's erase.
 * 
 * If a cell is empty but with a constant speed state.
 * A particle is created in it's center and it's border in the constant speed direction. 
 **/
template <class TypeWorld,class TypeStagPos>
class UpdateCellFluid
{
	TypeWorld & m_world;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_particle type_particle;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	typedef typename TypeWorld::type_data type_data;
	ParticleToKey< type_particle,type_key_vect_data,type_data,type_dim> m_to_key;
	type_cell& m_fluid;
	TypeStagPos & m_stag_pos;
public:
	/**
	 * @brief
	 * Constructor
	 * @param world World to use.
	 * @param _1_h 1/h used to convert position to key.  
	 **/
	UpdateCellFluid(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h,const Physvector<type_dim,type_data> &h,type_cell& fluid,TypeStagPos & stag_pos);
	/**
	 * @brief
	 * Do the update.
	 **/
	void Update();
};
#include "UpdateCellFluid.tpp"
#endif