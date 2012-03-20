/**
 * @file KeyTableUnorderedMap.tpp
 * @brief
 * Implementation file for class KeyTableMap.
 **/

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::KeyTableUnorderedMap(const TypeHash& hash,const TypeComp& comp):m_map(100,hash,comp)
{	
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::~KeyTableUnorderedMap()
{	
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::insert(const TypeKey & key,const TypeData &value)
{
	m_map.insert(pair<TypeKey,TypeData>(key,value));
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::empty()
{
	return m_map.empty();
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::size_type KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::size()
{
	return m_map.size();
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
bool KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::Exist(const TypeKey & key)
{
	return m_map.count(key)>0;
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
TypeData& KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::operator[](const TypeKey & key)
{
	return m_map[key];
}


template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::begin()
{
	return KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::end()
{
	return KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeHash,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::begin() const
{
	return KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::end() const
{
		return KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeHash,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::erase(iterator pos)
{
		m_map.erase(pos.GetMapIterator());
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::erase(const TypeKey & key)
{
		 m_map.erase(key);
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::clear()
{
		 m_map.clear();
}
