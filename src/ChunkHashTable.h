#ifndef ChunkHashTable_H
#define ChunkHashTable_H

#include <unordered_map>
#include "ChunkHashTableIterator.h"
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
template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class ChunkHashTable
{
	const TypeData& m_cop;
	TypeHash m_hash;
protected:
	unordered_map<TypeKey,TypeData,TypeHash,TypeComp> m_map;
	TypeKey ToChunkKey(const TypeKey& key) const;
public:
	typedef typename Offset::type_offset type_base_offset;
	typedef Offset type_offset;
protected:
	type_base_offset ToOffsetFromKey(const TypeKey& key) const __attribute__ ((const));
public:
	typedef typename type_base_offset::type_type type_value_offset;
	typedef TypeData type_data;
	/**
	 * @brief
	 * Type Key.
	 **/
	typedef TypeKey type_key;
	typedef TypeHash type_hash;
	typedef typename TypeData::type_value_bool_array type_value_bool_array;
	const TypeHash& GetHash()
	{
		return m_hash;
	}
	typedef unordered_map<TypeKey,TypeData,TypeHash,TypeComp> type_map;
	typedef typename type_map::iterator chunk_iterator;
	typedef typename type_map::const_iterator chunk_const_iterator;
	/**
	 * @brief
	 * Type used for size.
	 **/
	typedef typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::size_type size_type;
	/**
	 * @brief
	 * Type for iterator.
	 **/
	typedef ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> iterator;
	/**
	 * @brief
	 * Type for const_iterator.
	 **/
	typedef ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>  const_iterator;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	ChunkHashTable(const TypeData& cop,const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	ChunkHashTable(const ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp> &);
	/**
	 * @brief
	 * Destructor.
	 **/
	~ChunkHashTable();
	/**
	 * @brief
	 * Insert a element at a given key to link to a given value.
	 * @param key To use to reference data.
	 * @param value To insert.
	 **/
	/**
	 * @brief
	 * Return if the container is empty.
	 **/
	bool empty();
	/**
	 * @brief
	 * Return the size of the container.
	 **/
	size_type size_chunk();
	size_type size_upper() __attribute__ ((pure));
	/**
	 * @brief
	 * Return if key Exist.
	 * @param key Key to test existance.
	 **/
	bool Exist(const TypeKey& key) const;
	/**
	 * @brief
	 * Return a reference to the value at the given key.
	 * Creating a default constructed object if needed.
	 * @param key Key to use. 
	 **/
	type_offset operator[](const TypeKey & key);
	/**
	 * @brief
	 * Return an iterator to the begin of the container.
	 **/
	iterator begin();
	/**
	 * @brief
	 * Return an iterator to the end of the container.
	 **/
	iterator end();
	/**
	 * @brief
	 * Return an const_iterator to the begin of the container.
	 **/
	const_iterator begin() const;
	/**
	 * @brief
	 * Return an const_iterator to the end of the container.
	 **/
	const_iterator end() const;
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param pos Position of the iterator to erase.
	 **/
	iterator erase(iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	void erase(const TypeKey & key);
	/**
	 * @brief
	 * Clear the container.
	 **/
	void clear();
	/**
	 * @brief
	 * Reserve the given size to the container.
	 * It give the garanty that the iterator will not be invalidated in insertion.
	 * @param count Size to reserve.
	 **/
	void reserve(size_type count);
	TypeData & DirectAcessChunk(const TypeKey& key_chunk);
	bool ChunkExist(const TypeKey& key_chunk) __attribute__ ((pure));
private:
	Hook<ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp> > m_hook;
};

#include "ChunkHashTable.tpp"
#endif
