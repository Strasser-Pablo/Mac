#ifndef UpdateCellFluid3_H
#define UpdateCellFluid3_H
#include "ParticleToKey.h"
#include <set>
#include <iostream>
#include "Math_Set2.h"
#include <stack>
#include <functional>
using namespace std;
/**
 * @file UpdateCellFluid.h
 * @brief
 * Declaration file for class UpdateCellFluid.
 **/

/**
 * @ingroup GR_Update_Fluid
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
template <class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart>
class UpdateCellFluid3
{
	TypeWorld & m_world;
	typedef typename TypeWorld::dir_exterior dir_exterior;
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_mac_cell type_mac_cell;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_particle type_particle;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_list_surface_elem type_list_surface_elem;
	typedef typename TypeWorld::type_list_elem type_list_elem;
	typedef typename TypeWorld::type_list_surface type_list_surface;
	ParticleToKey< type_particle,type_key_vect_data,type_data,type_dim> m_to_key;
	TypeGetCellType &m_GetCellType;
	TypeStagPos & m_stag_pos;
	TypeCondPart & m_condpart;
	const Physvector<type_dim,type_data> &m_h;
	Math_Set2<type_dim,int> m_set;

	void Rafine(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,const typename type_list_surface_elem::iterator & it,type_list_surface_elem & list_surface);
	void AddToSet(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,dir_exterior dir);
public:
	/**
	 * @brief
	 * Constructor
	 * @param world World to use.
	 * @param _1_h 1/h used to convert position to key.  
	 **/
	UpdateCellFluid3(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h,const Physvector<type_dim,type_data> &h,TypeGetCellType &GetCellType,TypeStagPos & stag_pos,TypeCondPart &condpart);
	/**
	 * @brief
	 * Do the update.
	 **/
	void Update();
	/**
	 * @brief
	 *
	 * Assume positif constant speed.
	 **/
	void PrepareConst();
};
#include "UpdateCellFluid3.tpp"
#endif
