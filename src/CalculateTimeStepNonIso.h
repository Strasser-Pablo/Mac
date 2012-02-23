#ifndef CalculateTimeStepNonIso_H
#define CalculateTimeStepNonIso_H

#include "ApplyToEveryMacCell.h"
#include "CalculateMacMaximalSpeedNonIso.h"
#include <iostream>
using namespace std;

/**
 * @file CalculateTimeStep.h
 * @brief
 * Declaration file for class CalculateTimeStep.
 **/

/**
 * @brief
 * Calculate the next time step so that the faster particle move only a given factor of a cell.
 * In this case the cell is non Isotropic.
 **/
template <class MacWorld,class TypeData,class TypeGetCellType>
class CalculateTimeStepNonIso{
	typedef typename MacWorld::type_cell type_cell;
	static const int type_dim=MacWorld::type_dim;
	TypeData& m_factor;
	TypeData& m_dt;
	const MacWorld &m_world;
	const Physvector<type_dim,TypeData>& m_1_h;
	TypeGetCellType &m_GetCellType;
public:
	/**
	 * @brief
	 * Constructor taken as argument reference to different data.
	 * @param[in] h Cell size.
	 * @param[in] factor Fraction of the Cell size to traverse.
	 * @param[in] world World to use to read speed.
	 * @param[out] dt Where to output time step calculated.
	 **/
	CalculateTimeStepNonIso(const MacWorld &world,const Physvector<type_dim,TypeData>& _1_h,TypeData& factor, TypeData &dt,TypeGetCellType &GetCellType);
	
	/**
	 * @brief
	 * Calculate the optimal time step.
	 **/
	void Calculate()const ;
};
#include "CalculateTimeStepNonIso.tpp"
#endif