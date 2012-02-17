#ifndef TableContainer_H
#define TableContainer_H

/**
 * @file TableContainer.h
 * @brief
 * Declaration file for class TableContainer.
 **/

/**
 * @brief
 * Container class that store data.
 * The container is able to add item at begin and at end.
 * And with forward iterator.
 * 
 * @tparam TypeData Type of data to store.
 * @tparam TypeIterator Type for Iterator.
 * @tparam TypeConstIterator Type for Const Iterator.
 * @tparam TypeSize Type for the size.
 **/
template<class TypeData,class TypeIterator,class TypeConstIterator,class TypeSize>
class TableContainer{
public:
 /**
 * @brief
 * Type for Size.
 **/
typedef TypeSize size_type;
/**
 * @brief
 * Type for Iterator.
 **/
typedef TypeIterator iterator;
/**
 * @brief
 * Type for ConstIterator.
 **/
typedef TypeConstIterator const_iterator;

typedef TypeData type_data;
	
TableContainer(){
	
}
virtual ~TableContainer(){
	
}
/**
 * @brief
 * @param
 * Return if the container is empty.
 * @return bool True if empty.
 **/
virtual bool empty()=0;
/**
 * @brief
 * Return the size of the container.
 * @return TypeSize Size of the container.
 **/
virtual TypeSize size()=0;
/**
 * @brief
 * Add an element at the begining.
 * @param data Element to add.
 **/
virtual void push_front(const TypeData & data)=0;
/**
 * @brief
 * Add an element at the end.
 * @param data Element to add.
 **/
virtual void push_back(const TypeData &data)=0;
/**
 * @brief
 * Remove last element.
 **/
virtual void pop_back()=0;
/**
 * @brief
 * Remove first element.
 **/
virtual void pop_front()=0;
/**
 * @brief
 * Return first element.
 * @return TypeData& Reference to the front of the container.
 **/
virtual TypeData& front()=0;
/**
 * @brief
 * Return first element.
 * @return TypeData& Reference to the front of the container.
 **/
virtual const TypeData& front()const=0;
/**
 * @brief
 * Return last element.
 * @return TypeData& Reference to the back of the container.
 **/
virtual TypeData& back()=0;
/**
 * @brief
 * Return last element.
 * @return TypeData& Reference to the back of the container.
 **/
virtual const TypeData& back()const=0;
/**
 * @brief
 * Insert an element in the container.
 * @param pos Position to add element.
 * @param data Data to insert.
 * @return TypeIterator iterator to inserted element.
 **/
virtual TypeIterator insert(TypeIterator pos,const TypeData & data)=0;
/**
 * @brief
 * Erase an element in the container.
 * @param pos Position to add element.
 * @return TypeIterator iterator to the next element after the erased element.
 **/
virtual TypeIterator erase(TypeIterator pos)=0;
/**
 * @brief
 * Iterator to the begin of the Container.
 * @return TypeIterator Iterator to the begin.
 **/
virtual TypeIterator begin()=0;
/**
 * @brief
 * Iterator to the begin of the Container.
 * @return TypeConstIterator Iterator to the begin.
 **/
virtual TypeConstIterator begin() const=0;
/**
 * @brief
 * Iterator to the end of the Container.
 * @return TypeIterator Iterator to the end.
 **/
virtual TypeIterator end()=0;
/**
 * @brief
 * Iterator to the end of the Container.
 * @return TypeConstIterator Iterator to the end.
 **/
virtual TypeConstIterator end() const=0;
};
#endif