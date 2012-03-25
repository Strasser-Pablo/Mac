#ifndef TableContainerIterator_H
#define TableContainerIterator_H

/**
 * @file TableContainerIterator.h
 * @brief
 * Declaration file for class TableContainerIterator and TableContainerConstIterator.
 **/

/**
 * @ingroup GR_Container_List
 * @deprecated
 * Only serve as concept.
 **/
template <class TypeData, class TypeIterator>
class TableContainerIterator{
public:
 /**
 * @brief
 * Default Constructor.
 **/
	TableContainerIterator(){
		
	}
 /**
 * @brief
 * Default Destructor.
 **/
	virtual ~TableContainerIterator(){
		
	}
	/**
	 * @brief
	 * Comparaison operator for iterator. True if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool True if the iterator point to the same element.
	 **/
	virtual bool operator==(const TypeIterator &B)=0;
	/**
	 * @brief
	 * Comparaison operator for iterator. False if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool False if the iterator point to the same element.
	 **/
	virtual bool operator!=(const TypeIterator &B)=0;
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TypeIterator& operator++()=0;
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TypeIterator operator++(int)=0;
	/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual TypeData& operator*()=0;
};

/**
 * @ingroup GR_Container_List
 * @deprecated
 * Only serve as concept.
 **/
template <class TypeData, class TypeIterator>
class TableContainerConstIterator{
public:
 /**
 * @brief
 * Default Constructor.
 **/
	TableContainerConstIterator(){
		
	}
 /**
 * @brief
 * Default Destructor.
 **/
	virtual ~TableContainerConstIterator(){
		
	}
	/**
	 * @brief
	 * Comparaison operator for iterator. True if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool True if the iterator point to the same element.
	 **/
	virtual bool operator==(const TypeIterator &B)=0;
	/**
	 * @brief
	 * Comparaison operator for iterator. False if iterator point to the same element.
	 * @param B Iterator to compare with.
	 * @return bool False if the iterator point to the same element.
	 **/
	virtual bool operator!=(const TypeIterator &B)=0;
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TypeIterator& operator++()=0;
	/**
	 * @brief
	 * Advance the iterator the the next element.
	 **/
	virtual TypeIterator operator++(int)=0;
	/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual const TypeData& operator*()=0;
};

#endif
