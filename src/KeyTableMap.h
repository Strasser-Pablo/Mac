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
 * @brief Container class. Linking a key to a value. Implemented with std::map.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeComp Class overloading () operator giving if the first key is before the second.
 **/
template<class TypeKey,class TypeData,class TypeComp=less<TypeKey> >
class KeyTableMap:public KeyTable<TypeKey,TypeData,KeyTableMapIterator<TypeKey,TypeData,TypeComp>,KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>,typename map<TypeKey,TypeData>::size_type>{
	map<TypeKey,TypeData,TypeComp> m_map;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
public:
	typedef typename map<TypeKey,TypeData,TypeComp>::size_type size_type;
	typedef KeyTableMapIterator<TypeKey,TypeData,TypeComp> iterator;
	typedef KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>  const_iterator;
	typedef TypeData type_data;
	typedef TypeKey type_key;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	KeyTableMap(const TypeComp& comp=less<TypeKey>() );
	virtual ~KeyTableMap();
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

#include "KeyTableMap.tpp"
#endif
