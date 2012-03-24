#ifndef HASHPHYSVECTOR_H
#define HASHPHYSVECTOR_H
#include "Physvector.h"
/**
 * @ingroup GR_Hash_Map
 **/
template<int DIM,class TypeData>
class HashPhysvector
{
	public:
size_t operator()(const Physvector<DIM,TypeData>& key) const; 
};
#include "HashPhysvector.tpp"
#endif
