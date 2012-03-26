#ifndef HASHPHYSVECTOR_H
#define HASHPHYSVECTOR_H
#include "Physvector.h"
/**
 * @ingroup GR_Hash_Map
 * @brief
 * A hashfunction class.
 * @tparam DIM Dimension of the Physvector.
 * @tparam TypeData Data of the Physvector.
 **/
template<int DIM,class TypeData>
class HashPhysvector
{
	public:
	/**
	 * @brief
	 * A function call that calculate the hash.
	 * @param key Key to calculate the hash.
	 **/
size_t operator()(const Physvector<DIM,TypeData>& key) const; 
};
#include "HashPhysvector.tpp"
#endif
