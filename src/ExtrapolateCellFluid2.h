#ifndef ExtrapolateCellFluid_H
#define ExtrapolateCellFluid_H

#include "SetLayerFluidCell.h"
#include "NeighborsPhysvector.h"
#include "Physvector.h"
#include "Type_Inter.h"
#include <iostream>
using namespace std;
/**
 * @file ExtrapolateCellFluid2.h
 * @brief
 * Declaration file for class ExtrapolateCellFluid.
 **/
 
 /**
  * @ingroup GR_Extrapolate
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
template <class TypeWorld,class TypeGetCellType>
class ExtrapolateCellFluid2
{
	TypeWorld & m_world;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	typedef typename TypeWorld::type_data type_data;
	SetLayerFluidCell<TypeWorld,TypeGetCellType> m_layer_fluid;
	TypeGetCellType & m_GetCellType;
	const Physvector<type_dim,type_data>& m_h;
	const Physvector<type_dim,type_data>& m_1_h;
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
	ExtrapolateCellFluid2(TypeWorld & world, TypeGetCellType & GetCellType,const Physvector<type_dim,type_data>& h,const Physvector<type_dim,type_data>& _1_h);
	/**
	 * @brief
	 * Calculate the Extrapolation.
	 **/
	void Calculate(bool b=false);
}
;
#include "ExtrapolateCellFluid2.tpp"
#endif
