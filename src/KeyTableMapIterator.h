#ifndef KeyTableMapIterator_H
#define KeyTableMapIterator_H

#include <map>
#include "KeyTableIterator.h"
/**
 * @file KeyTableMapIterator.h
 * @brief
 * Declaration file for class KeyTableMapIterator and KeyTableMapIterator.
 **/

using namespace std;

template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapIterator;
/**
 * @ingroup GR_Map
 * @brief
 * Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapIterator:public KeyTableIterator<TypeKey,TypeData,KeyTableMapIterator<TypeKey,TypeData,TypeComp> >{
	typename map<TypeKey,TypeData,TypeComp>::iterator m_iterator;
	public:
	KeyTableMapIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableMapIterator(typename map<TypeKey,TypeData,TypeComp>::iterator iterator);
	virtual ~KeyTableMapIterator();
	virtual bool operator==(const KeyTableMapIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableMapIterator &B) __attribute__((pure));
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp>& operator++();
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp> operator++(int);
	virtual TypeData& operator*() __attribute__((pure));
	virtual TypeKey key() __attribute__((pure));
	virtual TypeData& data() __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::iterator& GetMapIterator() __attribute__((const));
	virtual const typename  map<TypeKey,TypeData,TypeComp>::iterator& GetMapIterator() const __attribute__((const));
};

template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapConstIterator;

/**
 * @ingroup GR_Map
 * @brief
 * Const Iterator class to a KeyTableMap.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapConstIterator:public KeyTableConstIterator<TypeKey,TypeData,KeyTableMapConstIterator<TypeKey,TypeData,TypeComp> > {
	typename map<TypeKey,TypeData,TypeComp>::const_iterator m_iterator;
	public:
	KeyTableMapConstIterator();
	KeyTableMapConstIterator(const KeyTableMapIterator<TypeKey,TypeData,TypeComp> & it);
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableMapConstIterator(typename map<TypeKey,TypeData,TypeComp>::const_iterator iterator);
	virtual ~KeyTableMapConstIterator();
	virtual bool operator==(const KeyTableMapConstIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableMapConstIterator &B) __attribute__((pure));
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>& operator++();
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp> operator++(int);
	virtual const TypeData& operator*() __attribute__((pure));
	virtual const TypeKey key() __attribute__((pure));
	virtual const TypeData& data() __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator() __attribute__((const));
	virtual const typename  map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator() const __attribute__((const));
};

#include "KeyTableMapIterator.tpp"

#endif
