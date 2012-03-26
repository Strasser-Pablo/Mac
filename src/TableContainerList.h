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
 * @ingroup GR_Linked_List
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
/**
 * @brief
 * Type for data.
 **/
typedef TypeData type_data;
/**
 * @brief
 * Default constructor.
 **/
	TableContainerList();
	/**
	 * @brief
	 * Destructor.
	 **/
	virtual ~TableContainerList();
	/**
	 * @brief
	 * Return if container is empty.
	 **/
	virtual bool empty() __attribute__((pure));
	/**
	 * @brief
	 * Return container size.
	 **/
	virtual size_type size() __attribute__((pure));
	/**
	 * @brief
	 * Push an element at front of the container.
	 **/
	virtual void push_front(const TypeData & data);
	/**
	 * @brief
	 * Push an element at back of the container.
	 **/
	virtual void push_back(const TypeData &data);
	/**
	 * @brief
	 * Pop the element at back of the container.
	 **/
	virtual void pop_back();
	/**
	 * @brief
	 * Pop the element at front of the container.
	 **/
	virtual void pop_front();
	/**
	 * @brief
	 * Get the element at front of the container.
	 **/
	virtual TypeData& front() __attribute__((pure));
	/**
	 * @brief
	 * Get the element at front of the container.
	 **/
	virtual const TypeData& front()const __attribute__((pure));
	/**
	 * @brief
	 * Get the element at back of the container.
	 **/
	virtual TypeData& back() __attribute__((pure));
	/**
	 * @brief
	 * Get the element at back of the container.
	 **/
	virtual const TypeData& back()const __attribute__((pure));
	/**
	 * @brief
	 * insert an element in the container.
	 * @param data Data to add.
	 **/
	virtual void insert(const TypeData &data);
	/**
	 * @brief
	 * Insert an element at a given position.
	 * @param pos Iterator to position to insert.
	 * @param data Data to add.
	 **/
	virtual iterator insert(iterator pos,const TypeData & data);
	/**
	 * @brief
	 * Erase an element at a given position.
	 * @param pos Iterator to erase. The iterator will be invalidated.
	 **/
	virtual iterator erase(iterator pos);
	/**
	 * @brief
	 * Return an iterator to the begin of the container.
	 **/
	virtual iterator begin();
	/**
	 * @brief
	 * Return an const_iterator to the begin of the container.
	 **/
	virtual const_iterator begin() const;
	/**
	 * @brief
	 * Return an iterator to the end of the container.
	 **/
	virtual iterator end();
	/**
	 * @brief
	 * Return an const_iterator to the end of the container.
	 **/
	virtual const_iterator end() const;
	
};
#include "TableContainerList.tpp"


#endif
