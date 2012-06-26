/**
 * @file KeyTableMapIterator.tpp
 * @brief
 * Implementation file for class KeyTableMapIterator and KeyTableMapIterator.
 **/


template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapIterator<TypeKey,TypeData,TypeComp>::KeyTableMapIterator()
{
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapIterator<TypeKey,TypeData,TypeComp>::~KeyTableMapIterator()
{
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapIterator<TypeKey,TypeData,TypeComp>::KeyTableMapIterator(typename map<TypeKey,TypeData,TypeComp>::iterator iterator):m_iterator(iterator)
{
}



template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMapIterator<TypeKey,TypeData,TypeComp>::operator==(const KeyTableMapIterator &B)
{
	return m_iterator==B.m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMapIterator<TypeKey,TypeData,TypeComp>::operator!=(const KeyTableMapIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapIterator<TypeKey,TypeData,TypeComp>&  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::operator++()
{
	++m_iterator;
	return *this;
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapIterator<TypeKey,TypeData,TypeComp>  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::operator++(int)
{
	KeyTableMapIterator<TypeKey,TypeData,TypeComp>ret(*this);
	++m_iterator;
	return ret;
}

template<class TypeKey,class TypeData,class TypeComp>
TypeData&  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::operator*()
{
	return m_iterator->second;
}

template<class TypeKey,class TypeData,class TypeComp>
TypeKey  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::key() const
{
	return m_iterator->first;
}

template<class TypeKey,class TypeData,class TypeComp>
TypeData&  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::data()
{
	return m_iterator->second;
}


template<class TypeKey,class TypeData,class TypeComp>
const TypeData&  KeyTableMapIterator<TypeKey,TypeData,TypeComp>::data() const
{
	return m_iterator->second;
}

template<class TypeKey,class TypeData,class TypeComp>
typename map<TypeKey,TypeData,TypeComp>::iterator& KeyTableMapIterator<TypeKey,TypeData,TypeComp>::GetMapIterator()
{
	return m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
 const typename map<TypeKey,TypeData,TypeComp>::iterator& KeyTableMapIterator<TypeKey,TypeData,TypeComp>::GetMapIterator() const
{
	return m_iterator;
}










template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::KeyTableMapConstIterator()
{
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::~KeyTableMapConstIterator()
{
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::KeyTableMapConstIterator(typename map<TypeKey,TypeData,TypeComp>::const_iterator iterator):m_iterator(iterator)
{
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::KeyTableMapConstIterator(const KeyTableMapIterator<TypeKey,TypeData,TypeComp> & it):m_iterator(it.GetMapIterator() )
{
}

template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::operator==(const KeyTableMapConstIterator &B)
{
	return m_iterator==B.m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::operator!=(const KeyTableMapConstIterator &B)
{
	return m_iterator!=B.m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>&  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::operator++()
{
	++m_iterator;
	return *this;
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::operator++(int)
{
	KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>ret(*this);
	++m_iterator;
	return ret;
}

template<class TypeKey,class TypeData,class TypeComp>
const TypeData&  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::operator*()
{
	return m_iterator->second;
}

template<class TypeKey,class TypeData,class TypeComp>
const TypeKey  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::key() const
{
	return m_iterator->first;
}

template<class TypeKey,class TypeData,class TypeComp>
const TypeData&  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::data() const
{
	return m_iterator->second;
}

template<class TypeKey,class TypeData,class TypeComp>
typename map<TypeKey,TypeData,TypeComp>::const_iterator&  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::GetMapIterator()
{
	return m_iterator;
}

template<class TypeKey,class TypeData,class TypeComp>
 const typename map<TypeKey,TypeData,TypeComp>::const_iterator&  KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>::GetMapIterator()const
{
	return m_iterator;
}
