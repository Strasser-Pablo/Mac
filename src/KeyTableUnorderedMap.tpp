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
bool KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::Exist(const TypeKey & key) const
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

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
template <class Archive>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::serialize(Archive & ar,const unsigned int version)
{
	
	if(typename Archive::is_loading())
	{
		size_type size;
		ar & boost::serialization::make_nvp("Size",size);
		for(size_type i=0;i<size;++i)
		{
			typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::value_type in;
			ar & boost::serialization::make_nvp("Pair",in);
			m_map.insert(in);	
		}

	}
	else if(typename Archive::is_saving())
	{
		size_type size=m_map.size();
		ar & boost::serialization::make_nvp("Size",size);
		for(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator it=m_map.begin();it!=m_map.end();++it)
		{

			typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::value_type out=*it;
			ar & boost::serialization::make_nvp("Pair",out);
		}
	}
	
}

template<class TypeKey,class TypeData,class TypeHash,class TypeComp>
void KeyTableUnorderedMap<TypeKey,TypeData,TypeHash,TypeComp>::reserve(size_type count)
{
	m_map.reserve(count);
}
