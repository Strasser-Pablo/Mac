#ifndef MacInitializeCell4_H
#define MacInitializeCell4_H
#include "UpdateCellFluid3.h"
#include "UpdateCellToInitialLayer.h"
#include "UpdateCellTypeAndLayer.h"
#include "UpdateDeleteCell.h"
/**
 * @file MacInitializeCell3.h
 * @brief 
 * Declaration file for class MacInitializeCell.
 **/

/**
 * @ingroup GR_Mac_Initialize
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
template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate,class TypeOutput>
class MacInitializeCell4
{
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	static const int type_dim=TypeWorld::type_dim;
	 UpdateCellToInitialLayer<TypeWorld> mc_init;
	 UpdateCellFluid3<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart> mc_fluid;
	 UpdateCellTypeAndLayer<TypeWorld,TypeGetCellType,TypeFunctionPressure> mc_layer;
	 UpdateDeleteCell<TypeWorld> mc_delete;
	 TypeOutput & m_out;
	 TypeExtrapolate &m_Extrap;
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
	MacInitializeCell4(TypeWorld &world, TypeGetCellType & GetCellType,Physvector<type_dim,type_data>& _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos,TypeCondPart &condpart,TypeFunctionPressure &func_pres,TypeExtrapolate &Extrap,TypeOutput &out);
	/**
	 * @brief
	 * Update the cell to initialize value and be ready for the other calculation.
	 **/
	void Update();
	/**
	 * @brief
	 * Like Update but extrapolate around constant speed cell.
	 **/
	void PrepareConstSpeed(bool b=true);
};
#include "MacInitializeCell4.tpp"
#endif
