#include "KeyTable.h"
#ifndef KeyTableMap_H
#define KeyTableMap_H
#include <boost/serialization/map.hpp>
#include "KeyTableMapIterator.h"
#include <boost/serialization/nvp.hpp>
using namespace std;

/**
 * @file KeyTableMap.h
 * @brief
 * Declaration file for class KeyTableMap.
 **/

/**
 * @ingroup GR_Map
 * @brief Container class. Linking a key to a value. Implemented with std::map.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeComp Class overloading (Key,key) operator giving if the first key is before the second.
 **/
template<class TypeKey,class TypeData,class TypeComp=less<TypeKey> >
class KeyTableMap:public KeyTable<TypeKey,TypeData,KeyTableMapIterator<TypeKey,TypeData,TypeComp>,KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>,typename map<TypeKey,TypeData>::size_type>{
	map<TypeKey,TypeData,TypeComp> m_map;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
public:
	/**
	 * @brief
	 * Type used for size.
	 **/
	typedef typename map<TypeKey,TypeData,TypeComp>::size_type size_type;
	/**
	 * @brief
	 * Type used for iterator.
	 **/
	typedef KeyTableMapIterator<TypeKey,TypeData,TypeComp> iterator;
	/**
	 * @brief
	 * Type used for const_iterator.
	 **/
	typedef KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>  const_iterator;
	/**
	 * @brief
	 * Type used for data.
	 **/
	typedef TypeData type_data;
	/**
	 * @brief
	 * Type used for key.
	 **/
	typedef TypeKey type_key;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	KeyTableMap(const TypeComp& comp=less<TypeKey>() );
	/**
	 * @brief
	 * Destructor.
	 **/
	virtual ~KeyTableMap();
	/**
	 * @brief
	 * Insert an element for the given key with with a given value.
	 * @param key Key to insert.
	 * @param value Value to insert.
	 **/
	virtual void insert(const TypeKey & key,const TypeData & value);
	/**
	 * @brief
	 * Return if the container is empty.
	 **/
	virtual bool empty() __attribute__((pure));
	/**
	 * @brief
	 * Return the size of the container.
	 **/
	virtual size_type size() __attribute__((pure));

	/**
	 * @brief
	 * Return if key exist.
	 **/
	virtual bool Exist(const TypeKey& key) __attribute__((pure));
	/**
	 * @brief
	 * Return a reference to the value linked to a given key.
	 * If key is not in the constructor. Default construct the value.
	 **/
	virtual TypeData& operator[](const TypeKey & key);
	/**
	 * @brief
	 * Iterator to the begin of the container.
	 **/
	virtual iterator begin();
	/**
	 * @brief
	 * Iterator to the end of the container.
	 **/
	virtual iterator end();
	/**
	 * @brief Const_iterator to the begin of the container.
	 **/
	virtual const_iterator begin()const;
	/**
	 * @brief Const_iterator to the end of the container.
	 **/
	virtual const_iterator end() const;
	/**
	 * @brief
	 * Erase the value of a given position.
	 * @param pos Position to erase. The iterator will be invalidated.
	 **/
	virtual void erase(iterator pos);
	/**
	 * @brief
	 * Erase the value of a given position.
	 * @param key Key position to erase.
	 **/
	virtual void erase(const TypeKey & key);
	/**
	 * @brief
	 * Clear the content of the container.
	 **/
	virtual void clear();
	/**
	 * @brief
	 * No op in this implementation.
	 **/
	void reserve(size_type count);
};

#include "KeyTableMap.tpp"
#endif
