#ifndef KeyTableUnorderedMapIterator_H
#define KeyTableUnorderedMapIterator_H

#include <unordered_map>
#include "KeyTableIterator.h"
/**
 * @file KeyTableMapIterator.h
 * @brief
 * Declaration file for class KeyTableMapIterator and KeyTableMapIterator.
 **/

using namespace std;

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapIterator;
/**
 * @ingroup GR_Hash_Map
 * @brief
 * Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapIterator
{
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator m_iterator;
	public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	KeyTableUnorderedMapIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the unordered_map iterator.
	 * @param iterator unordered_Map iterator to use.
	 **/
	KeyTableUnorderedMapIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator);
	/**
	 * @brief
	 * Destructor.
	 **/
	~KeyTableUnorderedMapIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	bool operator==(const KeyTableUnorderedMapIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Inequality operator. Check is two iterator represent different target.
	 * \param B Iterator to compare with.
	 **/
	bool operator!=(const KeyTableUnorderedMapIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	TypeData& operator*() __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	TypeKey key() const  __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	TypeData& data() __attribute__((pure));
	const TypeData& data() const  __attribute__((pure));
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator() __attribute__((const));
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator() const __attribute__((const));
};

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapConstIterator;

/**
 * @ingroup GR_Hash_Map
 * @brief
 * Const Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapConstIterator
{
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator m_iterator;
	public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	KeyTableUnorderedMapConstIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the unordered_map iterator.
	 * @param iterator unordered_Map iterator to use.
	 **/
	KeyTableUnorderedMapConstIterator(const KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> & it);
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableUnorderedMapConstIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator);
	/**
	 * @brief
	 * Destructor.
	 **/
	~KeyTableUnorderedMapConstIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	bool operator==(const KeyTableUnorderedMapConstIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Inequality operator. Check is two iterator represent different target.
	 * \param B Iterator to compare with.
	 **/
	bool operator!=(const KeyTableUnorderedMapConstIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const TypeData& operator*() __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const TypeKey key() const  __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	const TypeData& data() const __attribute__((pure));
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator() __attribute__((const));
	/**
	 * @brief 
	 * Return the unordered_map iterator used internaly.
	 * @return unordered_Map iterator.
	 **/
	const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator() const __attribute__((const));
};

#include "KeyTableUnorderedMapIterator.tpp"

#endif
