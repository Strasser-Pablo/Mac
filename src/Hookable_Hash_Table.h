#ifndef Hookable_Hash_Table_H
#define Hookable_Hash_Table_H

#include <unordered_map>
#include "KeyTableUnorderedMap.h"
#include <stdexcept>
using namespace std;


/**
 * @ingroup GR_Hookable_Table
 * @brief
 * This class is an hash table specialization that will inform it's hook when a new type is added.
 * This allow to implement complex behaviour in only changing the hook.
 * @tparam Hook template class name that take as template argument this class.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeHash Hashfunctor to use. Need to implement a function call that take as argument a key.
 * \tparam TypeComp Class overloading () operator giving if the first key is before the second.
 * \tparam copy Boolean value if we can default construct new TypeData element or if we need to copy from a stored value to copy.
 **/
template<template<class Self> class Hook,class TypeKey,class TypeData,bool copy=false,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class Hookable_Hash_Table : public KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>
{
public:
	/**
	 * @brief
	 * Type Data.
	 **/
	typedef TypeData type_data;
	/**
	 * @brief
	 * Type Key.
	 **/
	typedef TypeKey type_key;
private:
	/**
	 * @brief
	 * Hook.
	 **/
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> > m_hook;
public:

	/**
	 * @brief
	 * Constructor.
	 * @param hash Hash to use for Hash Table.
	 * @param TypeComp Equality comparaison.
	 **/
	Hookable_Hash_Table(const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	/**
	 * @brief
	 * Constructor.
	 * @param cop Value to copy. 
	 **/
	Hookable_Hash_Table(const Hookable_Hash_Table<Hook,TypeKey,TypeData,copy,TypeHash,TypeComp> & cop);
	/**
	 * @brief
	 * operator=
	 * @param cop Equality operator. 
	 * @return This.
	 **/
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
	typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	void erase(const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key. Creating a default constructed data if needed.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	TypeData& operator[](const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key.
	 * If the key doesn't exist it's an error.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	TypeData& at(const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key.
	 * If the key doesn't exist it's an error.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	const TypeData& at(const TypeKey & key) const;
};

/**
 * @ingroup GR_Hookable_Table
 * @brief
 * This class is an hash table specialization that will inform it's hook when a new type is added.
 * This allow to implement complex behaviour in only changing the hook.
 * @tparam Hook template class name that take as template argument this class.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeHash Hashfunctor to use. Need to implement a function call that take as argument a key.
 * \tparam TypeComp Class overloading () operator giving if the first key is before the second.
 *
 * We copy the data in creation and don't use default constructor.
 **/
template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp>
class Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp>: public KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>,public TypeData
{
public:
	/**
	 * @brief
	 * Type Data.
	 **/
	typedef TypeData type_data;
	/**
	 * @brief
	 * Type Key.
	 **/
	typedef TypeKey type_key;
private:
	/**
	 * @brief
	 * Hook.
	 **/
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> > m_hook;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param copy_data Default value to copy in the creation.
	 * @param hash Hash to use for Hash Table.
	 * @param TypeComp Equality comparaison.
	 **/
	Hookable_Hash_Table(const TypeData& copy_data,const TypeHash& hash=std::hash<TypeKey>(),const TypeComp& comp=equal_to<TypeKey>());
	/**
	 * @brief
	 * Constructor.
	 * @param cop Value to copy. 
	 **/
	Hookable_Hash_Table(const Hookable_Hash_Table<Hook,TypeKey,TypeData,true,TypeHash,TypeComp> & cop);
	/**
	 * @brief
	 * operator=
	 * @param cop Equality operator. 
	 * @return This.
	 **/
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
	typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos);
	/**
	 * @brief
	 * Erase the iterator at a given position.
	 * @param key Key to erase.
	 **/
	void erase(const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key. Creating a data in copying the default value.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	TypeData& operator[](const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key.
	 * If the key doesn't exist it's an error.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	TypeData& at(const TypeKey & key);
	/**
	 * @brief
	 * Get a reference to the data pointed by key.
	 * If the key doesn't exist it's an error.
	 * @param key Position to get.
	 * @return Reference to the Data stored at position key.
	 **/
	const TypeData& at(const TypeKey & key) const;
};
#include "Hookable_Hash_Table.tpp"
#endif
