#ifndef NeighborsPhysvector_H
#define NeighborsPhysvector_H

#include "Physvector.h"
#include "To0.h"
#include <iostream>

/**
 * @file NeighborsPhysvector.h
 * @brief
 * Declaration file for class NeighborsPhysvector.
 **/
/**
 * @brief
 * Get Neighboard Vector of a point.
 * @tparam TypeData data of the vector.
 * @tparam Dim dimension of the vector.
 **/
using namespace std;
template<class TypeData,int DIM>
class NeighborsPhysvector{
	Physvector<DIM,TypeData> m_key;
	int m_index;
	int m_sign;
public:
/**
 * @brief
 * Constructor.
 * @param key Origine from with give neighbors.
 **/
	NeighborsPhysvector(const Physvector<DIM,TypeData> &key);
/**
 * @brief
 * Give the next neighbors if possible.
 * @param neigh Reference to next neighbors only valid if return true.
 * @return bool If a next neighbors is found.
 **/
	bool GetNext(Physvector<DIM,TypeData> &neigh);
	
};
#include "NeighborsPhysvector.tpp"
#endif