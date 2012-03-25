#include "VectorContainer.h"

#ifndef VectorContainerWithLabelIterator_h
#define VectorContainerWithLabelIterator_h

/**
 * @file VectorContainerWithLabelIterator.h
 * @brief
 * File for declaration of Class VectorContainerWithLabelIterator and VectorContainerWithLabelIteratorConst.
 **/

/**
 * @deprecated
 * Not used.
 * @brief
 * Iterator class for class VectorContainerWithLabel.
 * It work like stl Forward iterator. With possibility to access the label with GetLabel().
 * 
 * @tparam TypeContainer Container to stock data.
 * @tparam TypeContainerLabel Container to stock label.
 **/
template <class TypeContainer,class TypeContainerLabel>
class VectorContainerWithLabelIterator{
	/**
	 * @brief
	 * Data iterator.
	 **/
	typename TypeContainer::iterator m_data;
	/**
	 * @brief
	 * Label iterator.
	 **/
	typename TypeContainerLabel::iterator m_label;
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	inline VectorContainerWithLabelIterator();
	
	/**
	 * @brief
	 * Constructor from the iterator of the two container.
	 * \param data Iterator of the data container.
	 * \param label Iterator of the data label.
	 **/
	inline VectorContainerWithLabelIterator(typename TypeContainer::iterator data,typename TypeContainerLabel::iterator label);
	
	/**
	 * @brief
	 * Destructor.
	 **/
	inline ~VectorContainerWithLabelIterator();
	
	/**
	 * @brief
	 * Comparaison operator. Compare element by element.
	 * @param b Container to compare with.
	 * @return bool If equal or not.
	 **/
	inline bool operator==(VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> &b);
	
	/**
	 * @brief
	 * Ineguality operator. Only true if label or data are different.
	 * @param b Container to compare with.
	 * @return bool If inequal or not.
	 **/
	inline bool operator!=(const VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> &b);
	/**
	 * Increment the iterator to the next element.
	 **/
	inline  VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>& operator++();
	/**
	 * @brief
	 * Increment the iterator to the next element.
	 **/
	inline  VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> operator++(int);
	/**
	 * @brief
	 * Obtain a reference to the data.
	 **/
	inline typename TypeContainer::reference operator*();
	/**
	 * @brief
	 * Obtain a pointer to the data that can be used to call a method of the data.
	 **/
	inline typename TypeContainer::pointer operator->();
	
	/**
	 * @brief
	 * Assignement operator.
	 * @param b Container to assign from.
	 **/
	inline  VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>& operator=(const VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>& b);
	
	/**
	 * @brief
	 * Obtain a reference to the label
	 **/
	inline typename TypeContainerLabel::reference GetLabel();
};

/**
 * @deprecated
 * Not used
 *
 * @brief
 * constant Iterator class for class VectorContainerWithLabel.
 * It work like stl constant Forward iterator. With possibility to access the label with GetLabel().
 * 
 * @tparam TypeContainer Container to stock data.
 * @tparam TypeContainerLabel Container to stock label.
 **/
template <class TypeContainer,class TypeContainerLabel>
class VectorContainerWithLabelIteratorConst{
	typename TypeContainer::const_iterator m_data;
	typename TypeContainerLabel::const_iterator m_label;
public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	inline VectorContainerWithLabelIteratorConst();
	
	/**
	 * @brief
	 * Constructor from the iterator of the two container.
	 * \param data Iterator of the data container.
	 * \param label Iterator of the data label.
	 **/
	inline VectorContainerWithLabelIteratorConst(typename TypeContainer::const_iterator data,typename TypeContainerLabel::const_iterator label);
	
	/**
	 * @brief
	 * Destructor.
	 **/
	inline ~VectorContainerWithLabelIteratorConst();
	
	/**
	 * @brief
	 * Comparaison operator. Compare element by element.
	 * @param b Container to compare with.
	 * @return bool If equal or not.
	 **/
	inline bool operator==(VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> &b);
	
	/**
	 * @brief
	 * Ineguality operator. Only true if label or data are different.
	 * @param b Container to compare with.
	 * @return bool If inequal or not.
	 **/
	inline bool operator!=(const VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> &b);
	
	/**
	 * @brief
	 * Increment the iterator to the next element.
	 **/
	inline  VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>& operator++();
	
	/**
	 * @brief
	 * Increment the iterator to the next element.
	 **/
	inline  VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> operator++(int);
	
	/**
	 * @brief
	 * Obtain a reference to the data.
	 **/
	inline typename TypeContainer::const_reference operator*();
	
	/**
	 * @brief
	 * Obtain a pointer to the data that can be used to call a method of the data.
	 **/
	inline typename TypeContainer::const_pointer operator->();
	
	/**
	 * @brief
	 * Assignement operator.
	 * @param b Container to assign from.
	 **/
	inline  VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>& operator=(const VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>& b);
	
	/**
	 * @brief
	 * Obtain a reference to the label
	 **/
	inline typename TypeContainerLabel::const_reference GetLabel();
};
#include "VectorContainerWithLabelIterator.tpp"
#endif
