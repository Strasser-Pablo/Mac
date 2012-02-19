#ifndef CalculateMacMaximalSpeedNonIso_H
#define CalculateMacMaximalSpeedNonIso_H

#include "ApplyToEveryMacCell.h"
#include <iostream>
#include "Physvector.h"
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
class CalculateMacMaximalSpeedNonIso{
	typedef typename TypeMacCell::type_data type_data;
	typedef typename TypeMacCell::type_cell type_cell;
	const type_cell & m_fluid;
    type_data m_max;
	static const int type_dim=TypeMacCell::type_dim;
	const Physvector<type_dim,type_data>& m_1_h;
public:
/**
 * @brief 
 * Default Constructor.
 **/
	CalculateMacMaximalSpeedNonIso(const Physvector<type_dim,type_data> & _1_h,const type_cell & fluid);
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
#include "CalculateMacMaximalSpeedNonIso.tpp"
#endif