#ifndef NeighborsVelocity_H
#define NeighborsVelocity_H
#include "Physvector.h"

/**
 * @file NeighborsVelocity.h
 * @brief
 * Declaration file for class NeighborsVelocity.
 **/

#include <iostream>
using namespace std;
/**
 * @brief
 * Class that for each speed component indicate an index of cell with respect to current where a neighboring velocity component.
 * @tparam Dim dimension of space.
 * @tparam TypeData type of data in vector.
 **/
template<int Dim,class TypeData>
class NeighborsVelocity
{
	Physvector<Dim,TypeData> m_list[Dim];
	bool m_bool[Dim];
public:
	/**
	 * @brief
	 * Get the i component position.
	 * @param i Speed component.
	 * @param vect Return value. Only valid if return true.
	 * @return bool Return true if no component exist or if index to large or to small.
	 **/
	bool Get(int i,Physvector<Dim,TypeData> & vect);
	/**
	 * @brief
	 * Constructor.
	 **/
	NeighborsVelocity();
	/**
	 * @brief
	 * Set the i component position.
	 * @param i Speed component.
	 * @param vect Value to set.
	 * @return bool Return true if correctly added or false if index to big or small.
	 **/
	bool Set(int i,const Physvector<Dim,TypeData> &vect);
}
;
#include "NeighborsVelocity.tpp"
#endif
