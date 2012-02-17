/**
 * @file TableContainerListIterator.tpp
 * @brief
 * Implementation file for class TableContainerListIterator and TableContainerListConstIterator.
 **/

template<class TypeData>
TableContainerListIterator<TypeData>::TableContainerListIterator()
{
}

template<class TypeData>
TableContainerListIterator<TypeData>::~TableContainerListIterator()
{
}

template<class TypeData>
TableContainerListIterator<TypeData>::TableContainerListIterator(typename list<TypeData>::iterator iterator):m_iterator(iterator)
{
}

template<class TypeData>
bool TableContainerListIterator<TypeData>::operator==(const TableContainerListIterator &B)
{
	return m_iterator==B.m_iterator;
}

template<class TypeData>
bool TableContainerListIterator<TypeData>::operator!=(const TableContainerListIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template<class TypeData>
TableContainerListIterator<TypeData>& TableContainerListIterator<TypeData>::operator++()
{
	++m_iterator;
	return *this;
}

template<class TypeData>
TableContainerListIterator<TypeData> TableContainerListIterator<TypeData>::operator++(int)
{
	TableContainerListIterator<TypeData> res(*this);
	++m_iterator;
	return res;
}

template<class TypeData>
TypeData& TableContainerListIterator<TypeData>::operator*()
{
	return *m_iterator;
}

template<class TypeData>
typename list<TypeData>::iterator TableContainerListIterator<TypeData>::GetListIterator()
{
	return m_iterator;
}

template<class TypeData>
const typename list<TypeData>::iterator TableContainerListIterator<TypeData>::GetListIterator() const
{
	return m_iterator;
}









template<class TypeData>
TableContainerListConstIterator<TypeData>::TableContainerListConstIterator()
{
}

template<class TypeData>
TableContainerListConstIterator<TypeData>::~TableContainerListConstIterator()
{
}

template<class TypeData>
TableContainerListConstIterator<TypeData>::TableContainerListConstIterator(typename list<TypeData>::const_iterator iterator):m_iterator(iterator)
{
}

template<class TypeData>
TableContainerListConstIterator<TypeData>::TableContainerListConstIterator(const TableContainerListIterator<TypeData> &it):m_iterator(it.GetListIterator())
{
}

template<class TypeData>
bool TableContainerListConstIterator<TypeData>::operator==(const TableContainerListConstIterator &B)
{
	return m_iterator==B.m_iterator;
}

template<class TypeData>
bool TableContainerListConstIterator<TypeData>::operator!=(const TableContainerListConstIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template<class TypeData>
TableContainerListConstIterator<TypeData>& TableContainerListConstIterator<TypeData>::operator++()
{
	++m_iterator;
	return *this;
}

template<class TypeData>
TableContainerListConstIterator<TypeData> TableContainerListConstIterator<TypeData>::operator++(int)
{
	TableContainerListConstIterator<TypeData> res(*this);
	++m_iterator;
	return res;
}

template<class TypeData>
const TypeData& TableContainerListConstIterator<TypeData>::operator*()
{
	return *m_iterator;
}

template<class TypeData>
typename list<TypeData>::const_iterator TableContainerListConstIterator<TypeData>::GetListIterator()
{
	return m_iterator;
}

template<class TypeData>
const typename list<TypeData>::const_iterator TableContainerListConstIterator<TypeData>::GetListIterator() const
{
	return m_iterator;
}