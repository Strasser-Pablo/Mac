#ifndef UpdateCellFluid3_H
#define UpdateCellFluid3_H
#include "ParticleToKey.h"
#include <set>
#include <iostream>
#include "Math_Set2.h"
#include "Math_Set3.h"
#include <stack>
#include <functional>
#include <unordered_map>
#include "HashPhysvector.h"
#include "RundingFunction.h"
#include <sys/times.h>
#include "Hash_Pair.h"
#include <limits>
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
	typedef typename type_list_surface_elem::iterator ppart_it;
	typedef pair<ppart_it,ppart_it> type_seg;
	typedef list<type_seg> type_list_seg; 
	typedef typename type_list_seg::iterator type_list_seg_iterator; 
	typedef unordered_map<int,type_list_seg> type_id_list_seg;
	typedef typename type_id_list_seg::iterator type_id_list_seg_iterator;
	typedef HashPhysvector<type_dim,int> Hash;
	typedef unordered_map<Physvector<type_dim,int>,type_id_list_seg,Hash> type_key_id_list_seg;
	typedef typename type_key_id_list_seg::iterator type_key_id_list_seg_iterator;
	typedef pair<int,int> type_id_pair;
	typedef pair<type_seg,type_seg> type_seg_pair;
	typedef pair<type_seg_pair,Physvector<type_dim,type_data> > type_inter;
	typedef unordered_multimap<type_id_pair,type_inter> type_unord_id_pair_to_inter;
	typedef typename type_unord_id_pair_to_inter::iterator type_unord_id_pair_to_inter_iterator;
	struct Intersection_Iterator_List
	{
		typename list<Intersection_Iterator_List>::iterator * m_other;		
		type_unord_id_pair_to_inter_iterator m_intersection;
	};
	typedef list<Intersection_Iterator_List> type_intersection_list;
	typedef typename type_intersection_list::iterator type_intersection_list_iterator;
	typedef unordered_map<int,type_intersection_list> type_intersection_map;
	ParticleToKey< type_particle,type_key_vect_data,type_data,type_dim> m_to_key;
	TypeGetCellType &m_GetCellType;
	TypeStagPos & m_stag_pos;
	TypeCondPart & m_condpart;
	const Physvector<type_dim,type_data> &m_h;
	const Physvector<type_dim,type_data> &m_1_h;
	Math_Set2<type_dim,int> m_set;
	Math_Set3<type_dim,int,type_data> m_set2;
	Hash m_hash;
	unordered_map<Physvector<type_dim,int>, int,Hash> m_trav;
	unordered_map<Physvector<type_dim,int>, bool,Hash> m_plein;
	type_key_id_list_seg m_key_seg_list;
	type_unord_id_pair_to_inter m_inter_map;
	type_intersection_map m_id_inter_map;
	void Rafine(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,typename type_list_surface_elem::iterator & it2,type_list_surface_elem & list_surface);
	void CountTrav(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,dir_exterior dir,int &mode,double &keyx,bool &bcontend);
	void AddToSet(const typename type_list_surface_elem::iterator & it,type_list_surface_elem & list_surface,dir_exterior dir);
	void AddToSegment(typename type_list_surface_elem::iterator & it,typename type_list_surface_elem::iterator &it2,const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data> & pos2,int id);
	bool CalculateIntersection(const Physvector<type_dim,type_data> & pos1,const Physvector<type_dim,type_data>&  pos2,const Physvector<type_dim,type_data> & pos3,const Physvector<type_dim,type_data> & pos4,Physvector<type_dim,type_data> & pos);
	void DoElemIntersectProcessing(type_seg & seg1,type_seg  & seg2,int id1,int id2);
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
