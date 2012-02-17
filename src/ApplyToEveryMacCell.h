#ifndef ApplyToEveryMacCell_H
#define ApplyToEveryMacCell_H

/**
 * @file ApplyToEveryMacCell.h
 * @brief
 * Declaration file for class ApplyToEveryMacCell.
 **/

/**
 * @brief
 * Class that apply a functor to all mac cell.
 * @tparam TypeFunctor type of the functor.
 * The functor need to define a () operator with Mac cell as argument.
 * The order of call for the functor is not determind.
 **/
template <class TypeFunctor,class MacWorld>
class ApplyToEveryMacCell{
public:
	/**
	 * @brief
	 * Constructor that apply the functor to all mac cell.
	 * @param world MacWorld that contain the mac cell to use.
	 * @param funct Functor to be applied to all mac cell.
	 **/
	ApplyToEveryMacCell(const MacWorld & world,TypeFunctor & funct);
	/**
	 * @brief
	 * Constructor that apply the functor to all mac cell.
	 * @param world MacWorld that contain the mac cell to use.
	 * @param funct Functor to be applied to all mac cell.
	 **/
	ApplyToEveryMacCell(MacWorld & world,TypeFunctor & funct);
};
#include "ApplyToEveryMacCell.tpp"
#endif