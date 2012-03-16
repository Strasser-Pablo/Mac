/**
 * @file KeyTableUnorderedMap.tpp
 * @brief
 * Implementation file for class KeyTableMap.
 **/

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::KeyUnorderedTableMap(const TypeComp & comp):m_map(comp)
{	
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::~KeyTableMap()
{	
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
void KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>Insert(const TypeKey & key,const TypeData &value)
{
	m_map.insert(pair<TypeKey,TypeData>(key,value));
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
bool KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::empty()
{
	return m_map.empty();
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
typename KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::size_type KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>:::size()
{
	return m_map.size();
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
bool KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::Exist(const TypeKey & key)
{
	return m_map.count(key)>0;
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
TypeData& KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::operator[](const TypeKey & key)
{
	return m_map[key];
}


template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
typename KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::iteratorKeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::begin()
{
	return KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
typename KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::iteratorKeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::end()
{
	return KeyTableUnorderedMapIterator<TypeKey,TypeData,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::const_iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::begin() const
{
	return KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::
typename KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::const_iterator KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::end() const
{
		return KeyTableUnorderedMapConstIterator<TypeKey,TypeData,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::
void KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::erase(iterator pos)
{
		m_map.erase(pos.GetMapIterator());
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::
void KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::erase(const TypeKey & key)
{
		 m_map.erase(key);
}

template<class TypeKey,class TypeData,class TypeHash=std::hash<TypeKey>,class TypeComp=equal_to<TypeKey> >KeyUnorderedTableMap<TypeKey,TypeData,TypeHash,TypeComp>::
void KeyTableUnorderedMap<TypeKey,TypeData,TypeComp>::clear()
{
		 m_map.clear();
}
