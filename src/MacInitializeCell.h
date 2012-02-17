#ifndef MacInitializeCell_H
#define MacInitializeCell_H
#include "UpdateCellFluid.h"
#include "UpdateCellToInitialLayer.h"
#include "UpdateCellTypeAndLayer.h"
#include "UpdateDeleteCell.h"

/**
 * @file MacInitializeCell.h
 * @brief 
 * Declaration file for class MacInitializeCell.
 **/

/**
 * @brief
 * Initialize the grid. Consisting to the following step:
 * - Cell with particle in it are Fluid Cell.
 * - A buffer zone of air is created with a certain depth.
 * - Other cell are deleted.
 * 
 * After use of this class. We can calculate derivative without risk
 * of overflow of cell limit.
 * 
 * @tparam TypeWorld type of world used.
 **/
template<class TypeWorld,class TypeStagPos >
class MacInitializeCell
{
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	 UpdateCellToInitialLayer<TypeWorld> mc_init;
	 UpdateCellFluid<TypeWorld,TypeStagPos> mc_fluid;
	 UpdateCellTypeAndLayer<TypeWorld> mc_layer;
	 UpdateDeleteCell<TypeWorld> mc_delete;
public:
	/**
	 * @brief
	 * Constructor
	 * @param world World used to acess grid.
	 * @param Fluid Value of fluid cell type.
	 * @param Air Value to put in air cell.
	 * @param _1_h 1 over the celle spacing.
	 * @param level Depth to use.
	 **/
	MacInitializeCell(TypeWorld &world,type_cell & Fluid,type_cell &Air,Physvector<type_dim,type_data>& _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos);
	void Update();
	void PrepareConstSpeed();
};
#include "MacInitializeCell.tpp"
#endif