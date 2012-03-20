/**
 * @file KeyTableMapIterator.tpp
 * @brief
 * Implementation file for class KeyTableMapIterator and KeyTableMapIterator.
 **/


template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMapIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::~KeyTableUnorderedMapIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMapIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator):m_iterator(iterator)
{
}



template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator==(const KeyTableUnorderedMapIterator &B)
{
	return m_iterator==B.m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator!=(const KeyTableUnorderedMapIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>&  KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator++()
{
	++m_iterator;
	return *this;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>  KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator++(int)
{
	KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>ret(*this);
	++m_iterator;
	return ret;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
TypeData&  KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator*()
{
	return m_iterator->second;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
TypeKey  KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::key()
{
	return m_iterator->first;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
TypeData&  KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::data()
{
	return m_iterator->second;
}


template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::GetMapIterator()
{
	return m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
 const typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>::GetMapIterator() const
{
	return m_iterator;
}










template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMapConstIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::~KeyTableUnorderedMapConstIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMapConstIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator):m_iterator(iterator)
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMapConstIterator(const KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp> & it):m_iterator(it.GetMapIterator() )
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator==(const KeyTableUnorderedMapConstIterator &B)
{
	return m_iterator==B.m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator!=(const KeyTableUnorderedMapConstIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>&  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator++()
{
	++m_iterator;
	return *this;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator++(int)
{
	KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>ret(*this);
	++m_iterator;
	return ret;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
const TypeData&  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::operator*()
{
	return m_iterator->second;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
const TypeKey  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::key()
{
	return m_iterator->first;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
const TypeData&  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::data()
{
	return m_iterator->second;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator&  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::GetMapIterator()
{
	return m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp>
 const typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator&  KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>::GetMapIterator()const
{
	return m_iterator;
}
