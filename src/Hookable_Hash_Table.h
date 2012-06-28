#ifndef Hookable_Hash_Table_H
#define Hookable_Hash_Table_H

#include <unordered_map>
#include "KeyTableUnorderedMap.h"
#include <stdexcept>
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

template<template<class Self> class Hook,class TypeKey,class TypeData,bool copy=false,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class Hookable_Hash_Table : public KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>
{
public:
	typedef TypeData type_data;
	typedef TypeKey type_key;
private:
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> > m_hook;
public:

	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	Hookable_Hash_Table(const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	Hookable_Hash_Table(const Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> & cop);
	Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> & operator=(const Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> & cop);
	/**
	 * @brief
	 * Destructor.
	 **/
	~Hookable_Hash_Table();
	/**
	 * @brief
	 * Insert a element at a given key to link to a given value.
	 * @param key To use to reference data.
	 * @param value To insert.
	 **/
	void insert(const TypeKey & key,const TypeData & value);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param pos Position of the iterator to erase.
	 **/
	void erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	void erase(const TypeKey & key);
	TypeData& operator[](const TypeKey & key);
	TypeData& at(const TypeKey & key);
	const TypeData& at(const TypeKey & key) const;
};

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp>
class Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp>: public KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>,public TypeData
{
public:
	typedef TypeData type_data;
	typedef TypeKey type_key;
private:
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> > m_hook;
public:
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	Hookable_Hash_Table(const TypeData& copy_data,const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	Hookable_Hash_Table(const Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> & cop);
	Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> & operator=(const Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> & cop);
	/**
	 * @brief
	 * Destructor.
	 **/
	~Hookable_Hash_Table();
	/**
	 * @brief
	 * Insert a element at a given key to link to a given value.
	 * @param key To use to reference data.
	 * @param value To insert.
	 **/
	void insert(const TypeKey & key,const TypeData & value);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param pos Position of the iterator to erase.
	 **/
	void erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	void erase(const TypeKey & key);
	TypeData& operator[](const TypeKey & key);
	TypeData& at(const TypeKey & key);
	const TypeData& at(const TypeKey & key) const;
};
#include "Hookable_Hash_Table.tpp"
#endif
