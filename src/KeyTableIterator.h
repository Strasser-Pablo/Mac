#ifndef KeyTableIterator_H
#define KeyTableIterator_H

/**
 * @file KeyTableIterator.h
 * @brief 
 * Declaration file for class KeyTableIterator.
 **/


/**
 * @ingroup GR_Container_Map
 * @deprecated
 * Only serve as concept. Not very usefull
 *
 * @brief
 * Iterator class to a KeyTable.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template<class TypeKey,class TypeData,class TypeIterator>
class KeyTableIterator{

public:
	/**
	 * @brief 
	 * Default Constructor.
	 **/
	 KeyTableIterator(){};
	/**
	 * @brief
	 * Default Destructor.
	 **/
	virtual ~KeyTableIterator(){};
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
	/**
	 * @brief 
	 * Get the key pointed by the iterator.
	 **/
	virtual  TypeKey key()=0;
	/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual TypeData& data()=0;
};

/**
 * @ingroup GR_Container_Map
 * @deprecated
 * Only serve as concept. Not very usefull
 *
 * @brief
 * Const Iterator class to a KeyTable.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 **/
template<class TypeKey,class TypeData,class TypeIterator>
class KeyTableConstIterator{

public:
	/**
	 * @brief 
	 * Default Constructor.
	 **/
	 KeyTableConstIterator(){};
	/**
	 * @brief
	 * Default Destructor.
	 **/
	virtual ~KeyTableConstIterator(){};
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
	/**
	 * @brief 
	 * Get the key pointed by the iterator.
	 **/
	virtual const TypeKey key()=0;
		/**
	 * @brief
	 * Get the data pointed by the iterator.
	 **/
	virtual const TypeData& data()=0;
};

#endif
