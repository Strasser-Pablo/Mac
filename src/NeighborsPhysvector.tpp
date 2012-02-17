/**
 * @file NeighborsPhysvector.tpp
 * @brief
 * Implementation file for class NeighborsPhysvector.
 **/

template<class TypeData,int DIM>
NeighborsPhysvector<TypeData,DIM>::NeighborsPhysvector(const Physvector<DIM,TypeData> &key):m_key(key),m_index(1),m_sign(-1)
{
	
}
template<class TypeData,int DIM>
bool NeighborsPhysvector<TypeData,DIM>::GetNext(Physvector<DIM,TypeData> &neigh)
{
	if(m_sign>=2){
	m_sign=-1;
	++m_index;
	}
	if(m_index>DIM)
	{
		return false;
	}
	Physvector<DIM,TypeData> temp;
	temp=m_key;
	temp.Set(m_index,temp.Get(m_index)+m_sign);
	neigh=temp;
	m_sign+=2;
	return true;
	
}