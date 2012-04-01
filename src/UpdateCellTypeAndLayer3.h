#ifndef UpdateCellTypeAndLayer3_H
#define UpdateCellTypeAndLayer3_H
#include "NDFor.h"
#include "NeighborsPhysvector.h"
#include "NeighborsDiagPhysvector.h"
#include <iostream>
#include <functional>
#include <stack>
#include <set>
#include "NDForMin.h"
#include "Math_Set2.h"
#include "PhysvectorKeyOrder.h"
#include "UpdateDeleteCell.h"
#include <fstream>
#include "ParticleToKey.h"
using namespace std;
/**
 * @file UpdateCellTypeAndLayer3.h
 * @brief
 * Declaration file for class UpdateCellTypeAndLayer3.
 **/
 
 /**
  * @brief GR_Topology
  * @brief
  * Update the cell type to fluid if a particle is in it. And give a correct layer.
  * It create the air layer with a given depth.
  **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
class UpdateCellTypeAndLayer3
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_particle type_particle;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	TypeGetCellType & m_GetCellType;
	TypeWorld & m_world;
	int m_level;
	int m_nb_comp_con;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename map<int,Math_Set2<type_dim,int> >::iterator iterator_map;
	typedef typename set<Physvector<type_dim,int>,PhysvectorKeyOrder<type_dim,int> >::iterator iterator_set;
	TypeFunctionPressure & m_func_pres;
	map<int,Math_Set2<type_dim,int> > m_set;
	PhysvectorKeyOrder<type_dim,int> m_O;
	set<Physvector<type_dim,int>,PhysvectorKeyOrder<type_dim,int> > m_bound_set;
	UpdateDeleteCell<TypeWorld> m_delete_cell;
	void CreateLayer();
	void CalculateAirNeighbour();
	void Follow(Physvector<type_dim,int> & key,int id);
	void EraseIfIn(iterator_map & it);
	void CleanSet();
	int m_i_out;
	ParticleToKey< type_particle,type_key_vect_data,type_data,type_dim> m_to_key;
	fstream m_stat_out;
	const Physvector<type_dim,type_data>& m_h;
public:
/**
 * @brief
 * Constructor
 * @param world World to use.
 * @param fluid Fluid value to use.
 * @param air Air value to use.
 * @param level Depth of air layer to use.
 **/
	UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres,const Physvector<type_dim,type_data>& h,const Physvector<type_dim,type_data>& _1_h);
	
	/**
	 * @brief
	 * Do the calculation.
	 **/
	void Update();
};
#include "UpdateCellTypeAndLayer3.tpp"
#endif
