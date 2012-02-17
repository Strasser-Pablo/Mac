#ifndef SolvePressureCG_H
#define SolvePressureCG_H
#include "KeyTableMap.h"
#include <math.h>
#include "NeighborsPhysvector.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
/**
 * @file SolvePressureCG.h
 * @brief
 * Declaration file for class SolvePressureCG.
 **/

/**
 * @brief
 * Find the correct pressure to have an incompressible fluid.
 * Using Conjugate Gradient.
 **/
template<class TypeWorld>
class SolvePressureCG
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	const type_cell m_fluid;
	TypeWorld & m_world;
	const Physvector<type_dim,type_data> & m_1_h;
	typedef KeyTableMap<typename TypeWorld::type_key,type_data,PhysvectorKeyOrder<type_dim,int> > temp_map;
	KeyTableMap<typename TypeWorld::type_key,type_data,PhysvectorKeyOrder<type_dim,int> > m_r;
	
	KeyTableMap<typename TypeWorld::type_key,type_data,PhysvectorKeyOrder<type_dim,int> > m_p;
	KeyTableMap<typename TypeWorld::type_key,Physvector<type_dim,int>,PhysvectorKeyOrder<type_dim,int > > m_vois;
	PhysvectorKeyOrder<type_dim,int> m_o;
	fstream m_stat_out;
	/**
	 * @brief Calculate the divergence assuming that all neighbour exist.
	 **/
	type_data CalculateDivergence(Physvector<type_dim,int> key );
	type_data CalculateLaplacien(Physvector<type_dim,int> key );
	type_data CalculateLaplacienInCell(Physvector<type_dim,int> key );
	type_data CalculateSquare();
	type_data CalculateAScalar();
	void SetSpeed();
public:
/**
 * @brief
 * Constructor.
 * @param world World to use.
 * @param _1_h 1 over the spacing to use.
 * @param fluid Fluid cell value.
 **/
	SolvePressureCG(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h ,type_cell fluid);
	
	/**
	 * @brief
	 * Do the calculation.
	 **/
	void Calculate();
}
;
#include "SolvePressureCG.tpp"
#endif