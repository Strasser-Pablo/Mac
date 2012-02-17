#ifndef TableContainerListIterator_H
#define TableContainerListIterator_H

#include <list>
using namespace std;
#include "TableContainerIterator.h"


/**
 * @file TableContainerListIterator.h
 * @brief
 * Declaration file for class TableContainerListIterator and TableContainerListConstIterator.
 **/

template<class TypeData>
class TableContainerListIterator;

/**
 * @brief
 * Iterator to use TableContainerList.
 * @tparam TypeData Type of the data.
 **/
template<class TypeData>
class TableContainerListIterator:public TableContainerIterator<TypeData,TableContainerListIterator<TypeData> >{
	typename list<TypeData>::iterator m_iterator;
public:
	TableContainerListIterator();
	~TableContainerListIterator();
	TableContainerListIterator( typename list<TypeData>::iterator iterator);
	
	/**
	 * @brief
	 * Comparaison operator for iterator. True if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool True if the iterator point to the same element.
	 **/
	virtual bool operator==(const TableContainerListIterator<TypeData> &B);
	/**
	 * @brief
	 * Comparaison operator for iterator. False if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool False if the iterator point to the same element.
	 **/
	virtual bool operator!=(const TableContainerListIterator<TypeData> &B);
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TableContainerListIterator<TypeData>& operator++();
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TableContainerListIterator<TypeData> operator++(int);
	/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual TypeData& operator*();
	
	virtual typename list<TypeData>::iterator GetListIterator();
	virtual const typename list<TypeData>::iterator GetListIterator() const;
};

template<class TypeData>
class TableContainerListIterator;

/**
 * @brief
 * Const Iterator to use TableContainerList.
 * @tparam TypeData Type of the data.
 **/
template<class TypeData>
class TableContainerListConstIterator:public TableContainerConstIterator<TypeData,TableContainerListConstIterator<TypeData> >{
	typename list<TypeData>::const_iterator m_iterator;
public:
	TableContainerListConstIterator();
	~TableContainerListConstIterator();
	TableContainerListConstIterator( typename list<TypeData>::const_iterator iterator);
	TableContainerListConstIterator(const TableContainerListIterator<TypeData> &it);
	/**
	 * @brief
	 * Comparaison operator for iterator. True if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool True if the iterator point to the same element.
	 **/
	virtual bool operator==(const TableContainerListConstIterator<TypeData> &B);
	/**
	 * @brief
	 * Comparaison operator for iterator. False if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool False if the iterator point to the same element.
	 **/
	virtual bool operator!=(const TableContainerListConstIterator<TypeData> &B);
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TableContainerListConstIterator<TypeData>& operator++();
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TableContainerListConstIterator<TypeData> operator++(int);
	/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual const TypeData& operator*();
	
	virtual typename list<TypeData>::const_iterator GetListIterator();
	virtual const typename list<TypeData>::const_iterator GetListIterator() const;
};
#include "TableContainerListIterator.tpp"
#endif