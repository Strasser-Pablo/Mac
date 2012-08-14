#ifndef ChunkHashTableIterator_H
#define ChunkHashTableIterator_H

#include <unordered_map>
/**
 * @file KeyTableMapIterator.h
 * @brief
 * Declaration file for class KeyTableMapIterator and KeyTableMapIterator.
 **/

using namespace std;

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
class ChunkHashTableIterator;
/**
 * @ingroup GR_Hash_Map
 * @brief
 * Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
class ChunkHashTableIterator
{
	typedef typename Offset::type_offset type_offset;
	typedef typename TypeData::type_value_bool_array type_value_bool_array;
	type_offset m_off;
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator m_iterator;
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator m_iterator_end;
	public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	ChunkHashTableIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the unordered_map iterator.
	 * @param iterator unordered_Map iterator to use.
	 **/
	ChunkHashTableIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator,type_offset off,typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator_end);
	/**
	 * @brief
	 * Destructor.
	 **/
	~ChunkHashTableIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	bool operator==(const ChunkHashTableIterator &B);
	/**
	 * @brief
	 * Inequality operator. Check is two iterator represent different target.
	 * \param B Iterator to compare with.
	 **/
	bool operator!=(const ChunkHashTableIterator &B);
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	Offset operator*();
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	TypeKey key() const;
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	Offset data();
	const Offset data() const;
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator();
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator() const;
};

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
class ChunkHashTableConstIterator;

/**
 * @ingroup GR_Hash_Map
 * @brief
 * Const Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
class ChunkHashTableConstIterator
{
	typedef typename Offset::type_offset type_offset;
	typedef typename TypeData::type_value_bool_array type_value_bool_array;
	type_offset m_off;
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator m_iterator;
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator m_iterator_end;
	public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	ChunkHashTableConstIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the unordered_map iterator.
	 * @param iterator unordered_Map iterator to use.
	 **/
	ChunkHashTableConstIterator(const ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> & it);
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	ChunkHashTableConstIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator,type_offset off,typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator_end);
	/**
	 * @brief
	 * Destructor.
	 **/
	~ChunkHashTableConstIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	bool operator==(const ChunkHashTableConstIterator &B);
	/**
	 * @brief
	 * Inequality operator. Check is two iterator represent different target.
	 * \param B Iterator to compare with.
	 **/
	bool operator!=(const ChunkHashTableConstIterator &B);
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const Offset operator*();
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const TypeKey key() const;
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const Offset data() const;
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator();
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator() const;
};

#include "ChunkHashTableIterator.tpp"

#endif
