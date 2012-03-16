/**
 * @file TableContainerList.tpp
 * @brief
 * Implementation file for class TableContainerList.
 **/

template<class TypeData>
TableContainerList<TypeData>::TableContainerList()
{
}

template<class TypeData>
TableContainerList<TypeData>::~TableContainerList()
{
}

template<class TypeData>
bool TableContainerList<TypeData>::empty()
{
	return m_list.empty();
}

template<class TypeData>
typename TableContainerList<TypeData>::size_type TableContainerList<TypeData>::size()
{
	return m_list.size();
}

template<class TypeData>
void TableContainerList<TypeData>::push_front(const TypeData & data)
{
	m_list.push_front(data);
}

template<class TypeData>
void TableContainerList<TypeData>::push_back(const TypeData & data)
{
	m_list.push_back(data);
}


template<class TypeData>
void TableContainerList<TypeData>::pop_back()
{
	m_list.pop_back();
}

template<class TypeData>
void TableContainerList<TypeData>::pop_front()
{
	m_list.pop_front();
}

template<class TypeData>
TypeData & TableContainerList<TypeData>::front()
{
	return m_list.front();
}

template<class TypeData>
const TypeData & TableContainerList<TypeData>::front() const
{
	return m_list.front();
}

template<class TypeData>
TypeData & TableContainerList<TypeData>::back()
{
	return m_list.back();
}

template<class TypeData>
const TypeData & TableContainerList<TypeData>::back() const
{
	return m_list.back();
}

template<class TypeData>
typename TableContainerList<TypeData>::iterator  TableContainerList<TypeData>::insert(iterator pos,const TypeData & data)
{
	typename list<TypeData>::iterator temp=m_list.insert(pos.GetListIterator(),data);
	return TableContainerListIterator<TypeData>(temp);
}

template<class TypeData>
void  TableContainerList<TypeData>::insert(const TypeData & data)
{
	m_list.push_back(data);
}

template<class TypeData>
typename TableContainerList<TypeData>::iterator  TableContainerList<TypeData>::erase(iterator pos)
{
	typename list<TypeData>::iterator temp=m_list.erase(pos.GetListIterator());
	return TableContainerListIterator<TypeData>(temp);
}

template<class TypeData>
typename TableContainerList<TypeData>::iterator  TableContainerList<TypeData>::begin()
{
	return TableContainerListIterator<TypeData>(m_list.begin());
}

template<class TypeData>
typename TableContainerList<TypeData>::iterator  TableContainerList<TypeData>::end()
{
	return TableContainerListIterator<TypeData>(m_list.end());
}

template<class TypeData>
typename TableContainerList<TypeData>::const_iterator  TableContainerList<TypeData>::begin() const
{
	return TableContainerListConstIterator<TypeData>(m_list.begin());
}

template<class TypeData>
typename TableContainerList<TypeData>::const_iterator  TableContainerList<TypeData>::end() const
{
	return TableContainerListConstIterator<TypeData>(m_list.end());
}
