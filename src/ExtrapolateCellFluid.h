#ifndef ExtrapolateCellFluid_H
#define ExtrapolateCellFluid_H

#include "SetLayerFluidCell.h"
#include "NeighborsPhysvector.h"
#include "NeighborsVelocity.h"
#include <iostream>
using namespace std;
/**
 * @file ExtrapolateCellFluid.h
 * @brief
 * Declaration file for class ExtrapolateCellFluid.
 **/
 
 /**
  * @brief
  * Extrapolate the speed to the exterior of the fluid zone.
  * @tparam TypeWorld Type used for the grid.
  * Need to define the following operation:
  * typedef type_cell give the type of cell (fluid or not).
  * static const int type_dim that give the dimension of the world.
  * typedef type_key_vect that give the type of key used for acess grid element.
  * typedef type_cell::type_data that give the type of the data of the key.
  * typedef type_keytable key table.
  * A member m_mac_grid that is a key table.
  **/
template <class TypeWorld>
class ExtrapolateCellFluid
{
	TypeWorld & m_world;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	typedef typename TypeWorld::type_data type_data;
	type_cell m_fluid;
	SetLayerFluidCell<TypeWorld> m_layer_fluid;
	int m_level;
	NeighborsVelocity<type_dim,int>& m_neighv;
public:
	/**
	 * @brief 
	 * Constructor.
	 * @param world used to acess grid.
	 * @param fluid value of type that represent fluid.
	 * @param level how many cell of air we need to extrapolate.
	 * @param neighv Object reveling if because of staggered grid some air cell velocity component are in boundary between water cell.
	 * And need so to be considered water component.
	 **/
	ExtrapolateCellFluid(TypeWorld & world, type_cell fluid,int level,NeighborsVelocity<type_dim,int>& neighv);
	/**
	 * @brief
	 * Calculate the Extrapolation.
	 **/
	void Calculate();
	void Calculate2();
	void Calculate3();
}
;
#include "ExtrapolateCellFluid.tpp"
#endif