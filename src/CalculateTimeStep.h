#ifndef CalculateTimeStep_H
#define CalculateTimeStep_H

#include "ApplyToEveryMacCell.h"
#include "CalculateMacMaximalSpeed.h"
#include <iostream>
using namespace std;

/**
 * @file CalculateTimeStep.h
 * @brief
 * Declaration file for class CalculateTimeStep.
 **/

/**
 * @brief
 * Calculate the next time step so that the faster particle move only a given factor.
 * \f[\Delta t=k\frac{h}{||v_{max}||} \f]
 **/
template <class MacWorld,class TypeData>
class CalculateTimeStep{
	TypeData& m_factor;
	const TypeData& m_h;
	TypeData& m_dt;
	const MacWorld &m_world;
public:
	/**
	 * @brief
	 * Constructor taking as input reference to the following data.
	 * @param[in] h Cell size.
	 * @param[in] factor Fraction of the Cell size.
	 * @param[out] dt Reference to the time step variable to change.
	 * @param[in] world Reference to the world variable to read.
	 **/
	CalculateTimeStep(const MacWorld &world,const TypeData& h,TypeData &factor,TypeData &dt);
	
	/**
	 * @brief
	 * Calculate the time step for the given mac_grid.
	 * The output is done in reference dt.
	 **/
	 void Calculate()const ;
};
#include "CalculateTimeStep.tpp"
#endif