#ifndef CalculateMacMaximalSpeed_H
#define CalculateMacMaximalSpeed_H

#include "ApplyToEveryMacCell.h"
#include <iostream>
using namespace std;

/**
 * @file CalculateMacMaximalSpeed.h
 * @brief
 * Declaration file for class CalculateMacMaximalSpeed.
 **/

/**
 * @brief
 * Functor to be used to calculate the maximal speed on a mac_grid.
 * Can be used with ApplyToEveryMacCell.
 **/
template <class TypeMacCell>
class CalculateMacMaximalSpeed{
	typename TypeMacCell::type_data m_max;
	typedef typename TypeMacCell::type_cell type_cell;
	const type_cell & m_fluid;
public:
/**
 * @brief 
 * Default Constructor.
 **/
	CalculateMacMaximalSpeed(const type_cell& fluid);
	/**
	* @brief 
	* Method that update the current maximun.
	* @param cell Mac_Cell to use to uptdate speed.
	**/
	void operator()(const TypeMacCell & cell);
	/**
	* @brief 
	* Return the found maximal speed norm.
	* @return TypeMacCell::type_data Maximal speed norm found.
	**/
	typename TypeMacCell::type_data GetResult();
};
#include "CalculateMacMaximalSpeed.tpp"
#endif