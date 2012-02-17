#ifndef KeyTable_H
#define KeyTable_H
/**
 * @file KeyTable.h
 * @brief Declaration file for class KeyTable.
 **/

/**
 * @brief Container abstract class. Linking a key to a value.
 * \tparam TypeKey TypeKey to use. Need to have a < operator.
 * \tparam TypeData TypeData to use. Has no constraint.
 * \tparam TypeIterator Iterator to use. Used by the deriving class.
 * \tparam TypeConstIterator ConstIterator to use. Used by the deriving class.
 * \tparam TypeSize TypeSize to use. Used by the deriving class.
 **/
template<class TypeKey,class TypeData,class TypeIterator,class TypeConstIterator,class TypeSize>
class KeyTable{
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
typedef TypeKey type_key;
/**
 * @brief
 * Default Constructor.
 **/
	KeyTable(){};
/**
 * @brief
 * Default Destructor.
 **/
	virtual ~KeyTable(){
		
	}
	/**
	 * @brief
	 * Insert a value in the container.
	 * @param key Key for the value to add.
	 * @param value Value to add.
	 **/
	virtual void insert(const TypeKey & key,const TypeData & value)=0;
	/**
	 * @brief 
	 * Return if the container is empty.
	 **/
	virtual bool empty()=0;
	/**
	 * @brief
	 * Return the size of the container.
	 **/
	virtual size_type size()=0;
	/**
	 * @brief
	 * Return if the key exist.
	 * @param key Key to test.
	 **/
	virtual bool Exist(const TypeKey &key)=0;
	/**
	 * @brief
	 * Return a reference to the data.
	 * @param key Key to access.
	 **/
	virtual TypeData& operator[](const TypeKey & key)=0;
	
	/**
	 * @brief
	 * Return an iterator to the begining.
	 **/
	virtual iterator begin()=0;
	/**
	 * @brief
	 * Return an iterator to the end.
	 **/
	virtual iterator end()=0;
	/**
	 * @brief
	 * Return an constant iterator to the begining.
	 **/
	virtual const_iterator begin() const =0;
	/**
	 * @brief
	 * Return an constant iterator to the end.
	 **/
	virtual const_iterator end() const =0;
	/**
	 * @brief
	 * Erase an element of the container.
	 * @param pos iterator to delete.
	 **/
	virtual void erase(iterator pos)=0;
	/**
	 * @brief 
	 * Erase an element of the container.
	 * @param key Key to erase.
	 **/
	virtual void erase(const TypeKey & key)=0;
};

#endif