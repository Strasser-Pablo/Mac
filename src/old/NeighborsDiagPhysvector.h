#ifndef NeighborsDiagPhysvector_H
#define NeighborsDiagPhysvector_H

#include "Physvector.h"
#include "To0.h"
#include <iostream>

/**
 * @file NeighborsDiagPhysvector.h
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
class NeighborsDiagPhysvector{
	Physvector<DIM,TypeData> m_key;
	Physvector<DIM,TypeData> m_neigh;
public:
/**
 * @brief
 * Constructor.
 * @param key Origine from with give neighbors.
 **/
	NeighborsDiagPhysvector(const Physvector<DIM,TypeData> &key);
/**
 * @brief
 * Give the next neighbors if possible.
 * @param neigh Reference to next neighbors only valid if return true.
 * @return bool If a next neighbors is found.
 **/
	bool GetNext(Physvector<DIM,TypeData> &neigh);
	
};
#include "NeighborsDiagPhysvector.tpp"
#endif
