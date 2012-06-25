#ifndef Hookable_Hash_Table_H
#define Hookable_Hash_Table_H

#include <unordered_map>
#include "Hookable_Hash_Table_Iterator.h"
#include "KeyTableUnorderedMap.h"
using namespace std;

/**
 * @file KeyTableMap.h
 * @brief
 * Declaration file for class KeyTableUnorderedMap.
 **/

/**
 * @ingroup GR_Hash_Map
 * @brief Container class. Linking a key to a value. Implemented with std::unordered_map.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeHash Hashfunctor to use. Need to implement a function call that take as argument a key.
 * \tparam TypeComp Class overloading () operator giving if the first key is before the second.
 **/
template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class Hookable_Hash_Table : public KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>
{
public:
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	Hookable_Hash_Table(const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	/**
	 * @brief
	 * Destructor.
	 **/
	virtual ~Hookable_Hash_Table();
	/**
	 * @brief
	 * Insert a element at a given key to link to a given value.
	 * @param key To use to reference data.
	 * @param value To insert.
	 **/
	virtual void insert(const TypeKey & key,const TypeData & value);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param pos Position of the iterator to erase.
	 **/
	virtual void erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	virtual void erase(const TypeKey & key);
	virtual TypeData& operator[](const TypeKey & key);
};

#include "Hookable_Hash_Table.tpp"
#endif
