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
	TypeData m_factor;
	const TypeData& m_h;
public:
	/**
	 * @brief
	 * Constructor for a given cell size and factor.
	 * @param h Cell size.
	 * @param factor Fraction of the Cell size.
	 **/
	CalculateTimeStep(const TypeData& h,TypeData factor);
	
	/**
	 * @brief
	 * Calculate the time step for the given mac_grid.
	 * @param world mac_world to use.
	 * @return TypeData Time_step to use.
	 **/
	TypeData Calculate(const MacWorld &world)const ;
};
#include "CalculateTimeStep.tpp"
#endif