/**
 * @file Hookable_Hash_Table.tpp
 * @brief
 * Implementation file for class KeyTableMap.
 **/

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp>
Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::Hookable_Hash_Table(const TypeHash& hash,const TypeComp& comp) : KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>(hash,comp)
{	
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp >
Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::~Hookable_Hash_Table()
{	
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp >
void Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::insert(const TypeKey & key,const TypeData &value)
{
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp> >::insert(this->m_map.insert(pair<TypeKey,TypeData>(key,value)));
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp >
void Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::erase(typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator pos)
{
		Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp> >::erase(pos.GetMapIterator());
		this->m_map.erase(pos.GetMapIterator());
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp >
void Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::erase(const TypeKey & key)
{
		Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp> >::erase(key);
		this->m_map.erase(key);
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class TypeHash,class TypeComp >
TypeData& Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp>::operator[](const TypeKey & key)
{
	TypeData& ret=this->m_map[key];
	Hook<Hookable_Hash_Table<Hook,TypeKey,TypeData,TypeHash,TypeComp> >::directacess(key,ret);
	return ret;
}
