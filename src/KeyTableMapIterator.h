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
	virtual bool operator==(const KeyTableMapIterator &B);
	virtual bool operator!=(const KeyTableMapIterator &B);
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp>& operator++();
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp> operator++(int);
	virtual TypeData& operator*();
	virtual TypeKey key();
	virtual TypeData& data();
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::iterator& GetMapIterator();
	virtual const typename  map<TypeKey,TypeData,TypeComp>::iterator& GetMapIterator() const;
};

template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapConstIterator;

/**
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
	virtual bool operator==(const KeyTableMapConstIterator &B);
	virtual bool operator!=(const KeyTableMapConstIterator &B);
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>& operator++();
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp> operator++(int);
	virtual const TypeData& operator*();
	virtual const TypeKey key();
	virtual const TypeData& data();
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator();
	virtual const typename  map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator() const;
};

#include "KeyTableMapIterator.tpp"

#endif