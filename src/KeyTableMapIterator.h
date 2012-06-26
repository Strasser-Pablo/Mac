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
	/**
	 * @brief
	 * Default constructor.
	 **/
	KeyTableMapIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableMapIterator(typename map<TypeKey,TypeData,TypeComp>::iterator iterator);
	/**
	 * @brief
	 * Destructor.
	 **/
	virtual ~KeyTableMapIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	virtual bool operator==(const KeyTableMapIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Inequality operator. Check is two iterator represent different target.
	 * \param B Iterator to compare with.
	 **/
	virtual bool operator!=(const KeyTableMapIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	virtual KeyTableMapIterator<TypeKey,TypeData,TypeComp> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual TypeData& operator*() __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual TypeKey key() const __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual TypeData& data() __attribute__((pure));
	virtual const TypeData& data() const  __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::iterator& GetMapIterator() __attribute__((const));
	/**
	 * @brief
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
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
	/**
	 * @brief
	 * Default constructor.
	 **/
	KeyTableMapConstIterator();
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableMapConstIterator(const KeyTableMapIterator<TypeKey,TypeData,TypeComp> & it);
	/**
	 * @brief 
	 * Constructor constructing the iterator from the map iterator.
	 * @param iterator Map iterator to use.
	 **/
	KeyTableMapConstIterator(typename map<TypeKey,TypeData,TypeComp>::const_iterator iterator);
	/**
	 * @brief
	 * Destructor.
	 **/
	virtual ~KeyTableMapConstIterator();
	/**
	 * @brief
	 * Equality operator. Check if two iterator represent the same target.
	 * \param B Iterator to compare with.
	 **/
	virtual bool operator==(const KeyTableMapConstIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	virtual bool operator!=(const KeyTableMapConstIterator &B) __attribute__((pure));
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>& operator++();
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	virtual KeyTableMapConstIterator<TypeKey,TypeData,TypeComp> operator++(int);
	/**
	 * @brief
	 * Operator that return the value pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual const TypeData& operator*() __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the key pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual const TypeKey key() const  __attribute__((pure));
	/**
	 * @brief
	 * Return the value of the data pointed by the iterator.
	 * It can only be dereferenced safety if it's not end and not invalidated.
	 **/
	virtual const TypeData& data() const __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual typename map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator() __attribute__((const));
	/**
	 * @brief
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
	virtual const typename  map<TypeKey,TypeData,TypeComp>::const_iterator& GetMapIterator() const __attribute__((const));
};

#include "KeyTableMapIterator.tpp"

#endif
