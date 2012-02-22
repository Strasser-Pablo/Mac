/**
 * @file NeighborsDiagPhysvector.tpp
 * @brief
 * Implementation file for class NeighborsDiagPhysvector.
 **/

template<class TypeData,int DIM>
NeighborsDiagPhysvector<TypeData,DIM>::NeighborsDiagPhysvector(const Physvector<DIM,TypeData> &key):m_key(key),m_index(1)
{
	m_neigh.SetAll(-1);
}
template<class TypeData,int DIM>
bool NeighborsDiagPhysvector<TypeData,DIM>::GetNext(Physvector<DIM,TypeData> &neigh)
{
	m_neigh.GetRef(1)+=1;
	int i=1;
	bool bcont=m_neigh.Get(1)>=2;
	while(bcont)
	{
		m_neigh.GetRef(i)=-1;
		++i;
		if(i>DIM)
		{
			return false;
		}
		m_neigh.GetRef(i)+=1;
		bool bcont=m_neigh.Get(i)>=2;
	}
	bool b=true;
	for(int i=1;i<=type_dim;++i)
	{
		if(m_neigh.Get(i)!=0)
		{
			b=false;
			break;
		}
	}
	if(b)
	{
		return GetNext(neigh);
	}
	neigh=m_neigh+m_key;
	return true;
}