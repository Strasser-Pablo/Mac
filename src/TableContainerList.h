#ifndef TableContainerList_H
#define TableContainerList_H

#include <boost/serialization/list.hpp>
using namespace std;

#include "TableContainerListIterator.h"
#include "TableContainer.h"
#include <boost/serialization/nvp.hpp>
/**
 * @file TableContainerList.h
 * @brief
 * File for Declaration of class TableContainerList.
 **/

/**
 * @brief
 * Implementation of a container based on stl list.
 * 
 * @tparam TypeData Type of data to store.
 **/
template<class TypeData>
class TableContainerList:public TableContainer<TypeData,TableContainerListIterator<TypeData>,TableContainerListConstIterator<TypeData>,typename list<TypeData>::size_type>{
	list<TypeData> m_list;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar,const unsigned int version);
public:
/**
 * @brief
 * Type for Size.
 **/
typedef typename list<TypeData>::size_type size_type;
/**
 * @brief
 * Type for Iterator.
 **/
typedef TableContainerListIterator<TypeData> iterator;
/**
 * @brief
 * Type for ConstIterator.
 **/
typedef TableContainerListConstIterator<TypeData>  const_iterator;
typedef TypeData type_data;
	TableContainerList();
	virtual ~TableContainerList();
	virtual bool empty();
	virtual size_type size();
	virtual void push_front(const TypeData & data);
	virtual void push_back(const TypeData &data);
	virtual void pop_back();
	virtual void pop_front();
	virtual TypeData& front();
	virtual const TypeData& front()const;
	virtual TypeData& back();
	virtual const TypeData& back()const;
	virtual void insert(const TypeData &data);
	virtual iterator insert(iterator pos,const TypeData & data);
	virtual iterator erase(iterator pos);
	virtual iterator begin();
	virtual const_iterator begin() const;
	virtual iterator end();
	virtual const_iterator end() const;
	
};
#include "TableContainerList.tpp"


#endif
