#ifndef KeyTableMapIterator_H
#define KeyTableMapIterator_H

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
 * @brief
 * Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapIterator:public KeyTableIterator<TypeKey,TypeData,KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> >{
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator m_iterator;
	public:
	KeyTableUnorderedMapIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableUnorderedMapIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator);
	virtual ~KeyTableUnorderedMapIterator();
	virtual bool operator==(const KeyTableUnorderedMapIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableUnorderedMapIterator &B) __attribute__((pure));
	virtual KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>& operator++();
	virtual KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> operator++(int);
	virtual TypeData& operator*() __attribute__((pure));
	virtual TypeKey key() __attribute__((pure));
	virtual TypeData& data() __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator() __attribute__((const));
	virtual const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& GetMapIterator() const __attribute__((const));
};

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapConstIterator;

/**
 * @brief
 * Const Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
class KeyTableUnorderedMapConstIterator:public KeyTableConstIterator<TypeKey,TypeData,KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp> > {
	typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator m_iterator;
	public:
	KeyTableUnorderedMapConstIterator();
	KeyTableUnorderedMapConstIterator(const KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> & it);
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableUnorderedMapConstIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator);
	virtual ~KeyTableUnorderedMapConstIterator();
	virtual bool operator==(const KeyTableUnorderedMapConstIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableUnorderedMapConstIterator &B) __attribute__((pure));
	virtual KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>& operator++();
	virtual KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp> operator++(int);
	virtual const TypeData& operator*() __attribute__((pure));
	virtual const TypeKey key() __attribute__((pure));
	virtual const TypeData& data() __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator() __attribute__((const));
	virtual const typename  unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator& GetMapIterator() const __attribute__((const));
};

#include "KeyTableUnorderedMapIterator.tpp"

#endif
