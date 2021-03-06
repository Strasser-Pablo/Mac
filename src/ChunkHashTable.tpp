/**
 * @file ChunkHashTable.tpp
 * @brief
 * Implementation file for class KeyTableMap.
 **/

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::ChunkHashTable(const TypeData& cop,const TypeHash& hash,const TypeComp& comp):m_cop(cop),m_hash(hash),m_map(100,hash,comp),m_hook(this)
{
	for(int i=1;i<=type_dim;++i)
	{
		m_bound[2*i-2]=0;
		m_bound[2*i-1]=0;
	}
}
template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::ChunkHashTable(const ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp> & cop):m_cop(cop.m_cop),m_hash(cop.m_hash),m_map(cop.m_map),m_hook(this) 
{
	for(int i=1;i<=type_dim;++i)
	{
		m_bound[2*i-2]=cop.m_bound[2*i-2];
		m_bound[2*i-1]=cop.m_bound[2*i-1];
	}
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::~ChunkHashTable()
{
	clear();
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
bool ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::empty()
{
	return m_map.empty();
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::size_type ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::size_chunk()
{
	return m_map.size();
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::size_type ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::size_upper()
{
	return m_map.size()*type_base_offset::MaxOffset();
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
bool ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::Exist(const TypeKey & key) const
{
	TypeKey key_chunk=ToChunkKey(key);
	if(m_map.count(key_chunk)==0)
	{
		return false;
	}
	type_base_offset cur_off=ToOffsetFromKey(key);
	return m_map.at(key_chunk).GetChunk_Bool_Array()[cur_off.Get()];
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
Offset ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::operator[](const TypeKey & key)
{
	TypeKey key_chunk=ToChunkKey(key);
	type_base_offset cur_off=ToOffsetFromKey(key);
	if(m_map.count(key_chunk)==0)
	{
		m_map.insert(pair<const TypeKey,TypeData>(key_chunk,m_cop)).first->second.Allocate();
		m_hook.directacess(key_chunk,m_map.at(key_chunk));
		for(int i=1;i<=type_dim;++i)
		{
			typename TypeKey::type_data val=key_chunk.Get(i);
			if(val<m_bound[2*i-2])
			{
				m_bound[2*i-2]=val;
			}
			if(m_bound[2*i-1]<val)
			{
				m_bound[2*i-1]=val;
			}
		}
	}
	m_map.at(key_chunk).GetChunk_Bool_Array()[cur_off.Get()]=true;
	Offset off(cur_off,&m_map.at(key_chunk));
	return off;
}


template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::iterator ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::begin()
{
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> temp(m_map.begin(),type_base_offset(0),m_map.end());
	if(m_map.begin()!=m_map.end())
	{
		chunk_iterator it=m_map.begin();
		if(!it->second.GetChunk_Bool_Array()[0])
		{
			++temp;
		}
	}
	return temp;
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::iterator ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::end()
{
	return ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>(m_map.end(),type_base_offset(type_base_offset::MaxOffset()),m_map.end());
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::const_iterator ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::begin() const
{
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> temp(m_map.begin(),type_base_offset(0),m_map.end());
	if(m_map.begin()!=m_map.end())
	{
		chunk_iterator it=m_map.begin();
		if(!it->second.GetChunk_Bool_Array()[0])
		{
			++temp;
		}
	}
	return temp;
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::const_iterator ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::end() const
{
		return ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>(m_map.end(),type_base_offset(type_base_offset::MaxOffset()),m_map.end());
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::iterator  ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::erase(iterator pos)
{
	TypeKey key_chunk=ToChunkKey(pos.key());
	type_base_offset cur_off=pos.data().GetOffset();
	m_map.at(key_chunk).GetChunk_Bool_Array()[cur_off.Get()]=false;
	Offset off(cur_off,&m_map.at(key_chunk));
	if(m_map.at(key_chunk).GetChunk_Bool_Array().none())
	{
		m_map.at(key_chunk).UnAllocate();
        m_hook.erase(pos.GetMapIterator());
		typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator it=m_map.erase(pos.GetMapIterator());
		return ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>(it,type_base_offset(0),m_map.end());
	}
	return ++pos;
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
void ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::erase(const TypeKey & key)
{
	type_base_offset cur_off=ToOffsetFromKey(key);
	TypeKey key_chunk=ToChunkKey(key);
    m_map.at(key_chunk).GetChunk_Bool_Array()[cur_off.Get()]=false;
    if(m_map.at(key_chunk).GetChunk_Bool_Array().none())
	{
		m_hook.erase(key_chunk);
        m_map.at(key_chunk).UnAllocate();
		m_map.erase(key_chunk);
	}
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
void ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::clear()
{
	for(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator it=m_map.begin();it!=m_map.end();++it)
	{
		it->second.UnAllocate();
	}
	m_map.clear();
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
void ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::reserve(size_type count)
{
	m_map.reserve(count);
}


template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
TypeKey ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::ToChunkKey(const TypeKey& key) const
{
	TypeKey ret;
	for(int i=1;i<=TypeKey::type_dim;++i)
	{
		if(key.Get(i)>=0)
		{
			ret.GetRef(i)=key.Get(i)/type_base_offset::LineN();
		}
		else
		{
			ret.GetRef(i)=(key.Get(i)+1)/type_base_offset::LineN()-1;
		}
	}
	return ret;
}


template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::type_base_offset ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::ToOffsetFromKey(const TypeKey& key) const
{
	return type_base_offset(key);
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
TypeData & ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::DirectAcessChunk(const TypeKey& key_chunk)
{
	return m_map.at(key_chunk);
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
bool ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::ChunkExist(const TypeKey& key_chunk)
{
	return m_map.count(key_chunk)>0;
}

template<template<class Self> class Hook,class TypeKey,class TypeData,class Offset,class TypeHash,class TypeComp>
typename TypeKey::type_data ChunkHashTable<Hook,TypeKey,TypeData,Offset,TypeHash,TypeComp>::GetBound(int i,int dir)
{
	return type_base_offset::LineN()*(m_bound[2*i+(dir+1)/2-2]+(dir+1)/2);
}
