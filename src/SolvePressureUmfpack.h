#ifndef SolvePressureUmfpack_H
#define SolvePressureUmfpack_H
#include "KeyTableMap.h"
#include <suitesparse/umfpack.h>
#include <iostream>
using namespace std;
/**
 * @file SolvePressureUmfpack.h
 * @brief
 * Declaration file for class SolvePressureUmfpack.
 **/

/**
 * @brief
 * Find the correct pressure to have an incompressible fluid.
 * Using the library umfpack.
 **/
template<class TypeWorld>
class SolvePressureUmfpack
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	typedef  KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int > > type_to_key;
	const type_cell& m_fluid;
	TypeWorld & m_world;
	const Physvector<type_dim,type_data> & m_1_h;
	int* m_offset;
	int* m_indice;
	type_data* m_val;
	type_data* m_b;
	type_data *m_p;
	int m_iid;
	
	KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int > > m_key_to_num;
	KeyTableMap<int,typename TypeWorld::type_key> m_num_to_key;
	PhysvectorKeyOrder<type_dim,int> m_o;
	
	/**
	 * @brief
	 * Calculate the element for the column icol. And update the matrix given as reference.
	 * @param icol number of the column (begin from 0).
	 * @param inumb[in,out] number to the current number of entry.
	 * @param key Key to the current cell of the column line.
	 **/
	void CalculateAColumn(int icol,int& inumb,	Physvector<type_dim,int> key);
	/**
	 * @brief
	 * Change the speed of all cell from the value of the pressure in all cell.
	 **/
	void SetSpeed();
	/**
	 * @brief
	 * Calculate value of the second member. Calculating divergence and using boundary condition.
	 * @param iline Component to calculate (begin from 0).
	 * @param key Key of the component to calculate.
	 **/
	void CalculateB(int iline,Physvector<type_dim,int> key);
public:
/**
 * @brief
 * Constructor creating the reference to variable to use.
 * @param world World to use.
 * @param _1_h 1 over the spacing to use.
 * @param fluid Fluid cell value.
 **/
	SolvePressureUmfpack(TypeWorld & world,const Physvector<type_dim,type_data> & _1_h ,const type_cell& fluid);
	
	/**
	 * @brief
	 * Do the calculation.
	 * After this call the pressure is updated.
	 **/
	void Calculate();
}
;
#include "SolvePressureUmfpack.tpp"
#endif