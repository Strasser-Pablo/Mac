#include "KeyTable.h"
#ifndef KeyTableUnordered_H
#define KeyTableUnordered_H
#include <unordered_map>
#include "KeyTableUnorderedMapIterator.h"
#include <boost/serialization/utility.hpp>
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
template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class KeyTableUnorderedMap
{
protected:
	unordered_map<TypeKey,TypeData,TypeHash,TypeComp> m_map;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
public:
	/**
	 * @brief
	 * Type used for size.
	 **/
	typedef typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::size_type size_type;
	/**
	 * @brief
	 * Type for iterator.
	 **/
	typedef KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> iterator;
	/**
	 * @brief
	 * Type for const_iterator.
	 **/
	typedef KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>  const_iterator;
	/**
	 * @brief
	 * Type for Data.
	 **/
	typedef TypeData type_data;
	/**
	 * @brief
	 * Type for key.
	 **/
	typedef TypeKey type_key;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	KeyTableUnorderedMap(const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	/**
	 * @brief
	 * Destructor.
	 **/
	~KeyTableUnorderedMap();
	/**
	 * @brief
	 * Insert a element at a given key to link to a given value.
	 * @param key To use to reference data.
	 * @param value To insert.
	 **/
	void insert(const TypeKey & key,const TypeData & value);
	/**
	 * @brief
	 * Return if the container is empty.
	 **/
	bool empty();
	/**
	 * @brief
	 * Return the size of the container.
	 **/
	size_type size();
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
	TypeData& operator[](const TypeKey & key);
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
	void erase(iterator pos);
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
};

#include "KeyTableUnorderedMap.tpp"
#endif
