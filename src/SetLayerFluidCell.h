#ifndef SetLayerFluidCell_H
#define SetLayerFluidCell_H

/**
 * @file SetLayerFluidCell.h
 * @brief
 * Declaration file for class SetLayerFluidCell.
 **/
/**
 * @brief
 * Set All fluid cell layer to 0. And non fluid cell layer to -1.
 **/
template <class TypeWorld>
class SetLayerFluidCell
{
	TypeWorld & m_world;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_key_vect type_key_vect;
	typedef typename TypeWorld::type_key_vect::type_data type_key_vect_data;
	typedef typename TypeWorld::type_data type_data;
	type_cell m_fluid;
public:
/**
 * @brief
 * Constructor
 * @param world World to use.
 * @param fluid Value of fluid cell.
 **/
	SetLayerFluidCell(TypeWorld & world,type_cell fluid);
	/**
	 * @brief
	 * Do the calculation.
	 **/
	void Calculate();
};
#include "SetLayerFluidCell.tpp"

#endif