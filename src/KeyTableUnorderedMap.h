#include "KeyTableUnorderedMap.h"
#ifndef KeyTableUnordered_H
#define KeyTableUnordered_H
#include <unordered_map>
#include "KeyTableUnorderedMapIterator.h"

using namespace std;

/**
 * @file KeyTableMap.h
 * @brief
 * Declaration file for class KeyTableMap.
 **/

/**
 * @brief Container class. Linking a key to a value. Implemented with std::map.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeComp Class overloading () operator giving if the first key is before the second.
 **/
template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
class KeyTableUnorderedMap:public KeyTable<TypeKey,TypeData,KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeComp>,KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeComp>,typename map<TypeKey,TypeData>::size_type>{
	unordered_map<TypeKey,TypeData,TypeHash,TypeComp> m_map;
public:
	typedef typename map<TypeKey,TypeData,TypeHash,TypeComp>::size_type size_type;
	typedef KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeComp> iterator;
	typedef KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeComp>  const_iterator;
	typedef TypeData type_data;
	typedef TypeKey type_key;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	KeyTableUnorderedMap(const TypeComp& comp=less<TypeKey>() );
	virtual ~KeyTableUnorderedMap();
	virtual void insert(const TypeKey & key,const TypeData & value);
	virtual bool empty();
	virtual size_type size();
	virtual bool Exist(const TypeKey& key);
	virtual TypeData& operator[](const TypeKey & key);
	virtual iterator begin();
	virtual iterator end();
	virtual const_iterator begin()const;
	virtual const_iterator end() const;
	virtual void erase(iterator pos);
	virtual void erase(const TypeKey & key);
	virtual void clear();
};

#include "KeyTableUnorderedMap.tpp"
#endif
