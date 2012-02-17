#include <iostream>

/**
 * @file VectorContainerWithLabelIterator.tpp
 * @brief
 * File for Implementation of Class VectorContainerWithLabelIterator and VectorContainerWithLabelIteratorConst.
 **/

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::VectorContainerWithLabelIterator()
{
	
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::~VectorContainerWithLabelIterator()
{
	
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::VectorContainerWithLabelIterator(typename TypeContainer::iterator data,typename TypeContainerLabel::iterator label):m_data(data),m_label(label)
{
	
}



template <class TypeContainer,class TypeContainerLabel>
bool VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator==(VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> &b)
{
	return m_data==b.m_data&&m_label==b.m_label;
}

template <class TypeContainer,class TypeContainerLabel>
bool VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator!=(const VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> &b)
{
	return m_data!=b.m_data||m_label!=b.m_label;
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>& VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator++()
{
	++m_data;
	++m_label;
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator++(int )
{
	m_data++;
	m_label++;
}

template <class TypeContainer,class TypeContainerLabel>
typename TypeContainer::reference VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator*()
{
	return *m_data;
}


template <class TypeContainer,class TypeContainerLabel>
typename TypeContainer::pointer VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator->(){
	return m_data.operator->();
}

 
template <class TypeContainer,class TypeContainerLabel>
 VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>& VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::operator=(const VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> &b){
	m_data=b.m_data;
	m_label=b.m_label;
	return *this;
}


template <class TypeContainer,class TypeContainerLabel>
typename TypeContainerLabel::reference VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>::GetLabel(){
	return *m_label;
}
















template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::VectorContainerWithLabelIteratorConst()
{
	
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::~VectorContainerWithLabelIteratorConst()
{
	
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::VectorContainerWithLabelIteratorConst(typename TypeContainer::const_iterator data,typename TypeContainerLabel::const_iterator label):m_data(data),m_label(label)
{
	
}



template <class TypeContainer,class TypeContainerLabel>
bool VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator==(VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> &b)
{
	return m_data==b.m_data&&m_label==b.m_label;
}

template <class TypeContainer,class TypeContainerLabel>
bool VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator!=(const VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> &b)
{
	return m_data!=b.m_data||m_label!=b.m_label;
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>& VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator++()
{
	++m_data;
	++m_label;
}

template <class TypeContainer,class TypeContainerLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator++(int )
{
	m_data++;
	m_label++;
}

template <class TypeContainer,class TypeContainerLabel>
typename TypeContainer::const_reference VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator*(){
	return *m_data;
}


template <class TypeContainer,class TypeContainerLabel>
typename TypeContainer::const_pointer VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator->(){
	return m_data.operator->();
}


template <class TypeContainer,class TypeContainerLabel>
 VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>& VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::operator=(const VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> &b){
	m_data=b.m_data;
	m_label=b.m_label;
	return *this;
}

template <class TypeContainer,class TypeContainerLabel>
typename TypeContainerLabel::const_reference VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel>::GetLabel(){
	return *m_label;
}