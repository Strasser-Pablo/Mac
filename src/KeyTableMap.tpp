/**
 * @file KeyTableMap.tpp
 * @brief
 * Implementation file for class KeyTableMap.
 **/

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMap<TypeKey,TypeData,TypeComp>::KeyTableMap(const TypeComp & comp):m_map(comp)
{	
}

template<class TypeKey,class TypeData,class TypeComp>
KeyTableMap<TypeKey,TypeData,TypeComp>::~KeyTableMap()
{	
}

template<class TypeKey,class TypeData,class TypeComp>
void KeyTableMap<TypeKey,TypeData,TypeComp>::insert(const TypeKey & key,const TypeData &value)
{
	m_map.insert(pair<TypeKey,TypeData>(key,value));
}

template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMap<TypeKey,TypeData,TypeComp>::empty()
{
	return m_map.empty();
}

template<class TypeKey,class TypeData,class TypeComp>
typename KeyTableMap<TypeKey,TypeData,TypeComp>::size_type KeyTableMap<TypeKey,TypeData,TypeComp>::size()
{
	return m_map.size();
}

template<class TypeKey,class TypeData,class TypeComp>
bool KeyTableMap<TypeKey,TypeData,TypeComp>::Exist(const TypeKey & key)
{
	return m_map.count(key)>0;
}

template<class TypeKey,class TypeData,class TypeComp>
TypeData& KeyTableMap<TypeKey,TypeData,TypeComp>::operator[](const TypeKey & key)
{
	return m_map[key];
}


template<class TypeKey,class TypeData,class TypeComp>
typename KeyTableMap<TypeKey,TypeData,TypeComp>::iterator KeyTableMap<TypeKey,TypeData,TypeComp>::begin()
{
	return KeyTableMapIterator<TypeKey,TypeData,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeComp>
typename KeyTableMap<TypeKey,TypeData,TypeComp>::iterator KeyTableMap<TypeKey,TypeData,TypeComp>::end()
{
	return KeyTableMapIterator<TypeKey,TypeData,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeComp>
typename KeyTableMap<TypeKey,TypeData,TypeComp>::const_iterator KeyTableMap<TypeKey,TypeData,TypeComp>::begin() const
{
	return KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>(m_map.begin());
}

template<class TypeKey,class TypeData,class TypeComp>
typename KeyTableMap<TypeKey,TypeData,TypeComp>::const_iterator KeyTableMap<TypeKey,TypeData,TypeComp>::end() const
{
		return KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>(m_map.end());
}

template<class TypeKey,class TypeData,class TypeComp>
void KeyTableMap<TypeKey,TypeData,TypeComp>::erase(iterator pos)
{
		m_map.erase(pos.GetMapIterator());
}

template<class TypeKey,class TypeData,class TypeComp>
void KeyTableMap<TypeKey,TypeData,TypeComp>::erase(const TypeKey & key)
{
		 m_map.erase(key);
}

template<class TypeKey,class TypeData,class TypeComp>
void KeyTableMap<TypeKey,TypeData,TypeComp>::clear()
{
		 m_map.clear();
}


template<class TypeKey,class TypeData,class TypeComp>
template <class Archive>
void KeyTableMap<TypeKey,TypeData,TypeComp>::serialize(Archive & Ar,const unsigned int version)
{
	Ar & boost::serialization::make_nvp("Map",m_map);  
}
