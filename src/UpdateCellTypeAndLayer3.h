#ifndef UpdateCellTypeAndLayer3_H
#define UpdateCellTypeAndLayer3_H

#include "NeighborsPhysvector.h"
#include "NeighborsDiagPhysvector.h"
#include <iostream>
using namespace std;
/**
 * @file UpdateCellTypeAndLayer3.h
 * @brief
 * Declaration file for class UpdateCellTypeAndLayer.
 **/
 
 /**
  * @brief
  * Update the cell type to fluid if a particle is in it. And give a correct layer.
  * It create the air layer with a given depth.
  **/
template <class TypeWorld,class TypeGetCellType,class TypeFunctionPressure>
class UpdateCellTypeAndLayer3
{
	typedef typename TypeWorld::type_cell type_cell;
	TypeGetCellType & m_GetCellType;
	TypeWorld & m_world;
	int m_level;
	int m_nb_comp_con;
	static const int type_dim=TypeWorld::type_dim;
		typedef typename TypeWorld::type_data type_data;
		TypeFunctionPressure & m_func_pres;
		
		void CalculateAirNeighbour();
		void DoAir(Physvector<type_dim,int> & key);
public:
/**
 * @brief
 * Constructor
 * @param world World to use.
 * @param fluid Fluid value to use.
 * @param air Air value to use.
 * @param level Depth of air layer to use.
 **/
	UpdateCellTypeAndLayer3(TypeWorld & world,TypeGetCellType & GetCellType,int level,TypeFunctionPressure & func_pres);
	
	/**
	 * @brief
	 * Do the calculation.
	 **/
	void Update();
	/**
	 * @brief Create cell above constant speed cell.
	 * Put the speed of the celle the same that the constant speed.
	 * And put the type to air.
	 * To be used the first time in the initialization phase.
	 **/
	void PrepareConstSpeed();
};
#include "UpdateCellTypeAndLayer3.tpp"
#endif