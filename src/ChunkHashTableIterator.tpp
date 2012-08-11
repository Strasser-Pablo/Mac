/**
 * @file KeyTableMapIterator.tpp
 * @brief
 * Implementation file for class KeyTableMapIterator and KeyTableMapIterator.
 **/


template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::ChunkHashTableIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::~ChunkHashTableIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::ChunkHashTableIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator,type_offset off,typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator iterator_end):m_off(off),m_iterator(iterator),m_iterator_end(iterator_end)
{
}



template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
bool ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator==(const ChunkHashTableIterator &B)
{
	return (m_iterator==B.m_iterator)&&(m_off==B.m_off||m_iterator==m_iterator_end);
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
bool ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator!=(const ChunkHashTableIterator &B)
{
	return (m_iterator!=B.m_iterator)||(m_off!=B.m_off&&m_iterator!=m_iterator_end);
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>&  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator++()
{
	if(!m_off.end())
	{
		++m_off;
		if(m_off.end())
		{
			++m_iterator;
			m_off.Set(0);
			if(m_iterator!=m_iterator_end)
			{
				if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
				{
					++(*this);
				}
			}
		}
		else if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
		{
			++(*this);
		}
	}
	else
	{
		++m_iterator;
		m_off.Set(0);
		if(m_iterator!=m_iterator_end)
		{
			if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
			{
				++(*this);
			}
		}
	}
	return *this;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator++(int)
{
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>ret(*this);
	if(!m_off.end())
	{
		++m_off;
		if(m_off.end())
		{
			++m_iterator;
			m_off.Set(0);
			if(m_iterator!=m_iterator_end)
			{
				if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
				{
					++(*this);
				}
			}
		}
		else if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
		{
			++(*this);
		}
	}
	else
	{
		++m_iterator;
		m_off.Set(0);
		if(m_iterator!=m_iterator_end)
		{
			if(!m_iterator->second.GetChunk_Bool_Array()[m_off.Get()])
			{
				++(*this);
			}
		}
	}
	return ret;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
Offset  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator*()
{
	Offset off(m_off,&m_iterator->second);
	return off;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
TypeKey  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::key() const
{
	TypeKey key;
	m_off.ToKey(key,m_iterator->first);
	return key;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
Offset  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::data()
{
	Offset off(m_off,&m_iterator->second);
	return off;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
const Offset  ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::data() const
{
	Offset off(m_off,&m_iterator->second);
	return off;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::GetMapIterator()
{
	return m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
 const typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::iterator& ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::GetMapIterator() const
{
	return m_iterator;
}










template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::ChunkHashTableConstIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::~ChunkHashTableConstIterator()
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::ChunkHashTableConstIterator(typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator,type_offset off,typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator iterator_end):m_iterator(iterator),m_off(off),m_iterator_end(iterator_end)
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::ChunkHashTableConstIterator(const ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset> & it):m_iterator(it.GetMapIterator(),it.m_off )
{
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
bool ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator==(const ChunkHashTableConstIterator &B)
{
	return (m_iterator==B.m_iterator)&&(m_off==B.m_off||m_iterator==m_iterator_end);
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
bool ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator!=(const ChunkHashTableConstIterator &B)
{
	return (m_iterator!=B.m_iterator)||(m_off!=B.m_off&&m_iterator!=m_iterator_end);
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>&  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator++()
{
	if(!m_off.end())
	{
		++m_off;
		if(m_off.end())
		{
			++m_iterator;
			m_off.Set(0);
			if(m_iterator!=m_iterator_end)
			{
				if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
				{
					++(*this);
				}
			}
		}
		else if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
		{
			++(*this);
		}
	}
	else
	{
		++m_iterator;
		m_off.Set(0);
		if(m_iterator!=m_iterator_end)
		{
			if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
			{
				++(*this);
			}
		}
	}
	return *this;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator++(int)
{
	ChunkHashTableIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>ret(*this);
	if(!m_off.end())
	{
		++m_off;
		if(m_off.end())
		{
			++m_iterator;
			m_off.Set(0);
			if(m_iterator!=m_iterator_end)
			{
				if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
				{
					++(*this);
				}
			}
		}
		else if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
		{
			++(*this);
		}
	}
	else
	{
		++m_iterator;
		m_off.Set(0);
		if(m_iterator!=m_iterator_end)
		{
			if(!this->Data().GetChunk_Bool_Array()[m_off.Get()])
			{
				++(*this);
			}
		}
	}
	return ret;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
const Offset  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::operator*()
{
	Offset off(m_off,&m_iterator->second);
	return off;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
const TypeKey  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::key() const
{
	TypeKey key;
	m_off.ToKey(key,m_iterator->first);
	return key;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
const Offset  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::data() const
{
	Offset off(m_off,&m_iterator->second);
	return off;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator&  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::GetMapIterator()
{
	return m_iterator;
}

template <class TypeKey,class TypeData,class TypeHash,class TypeComp,class Offset>
 const typename unordered_map<TypeKey,TypeData,TypeHash,TypeComp>::const_iterator&  ChunkHashTableConstIterator<TypeKey,TypeData,TypeHash,TypeComp,Offset>::GetMapIterator()const
{
	return m_iterator;
}
