#include <iostream>
using namespace std;
template<int DIM,typename Data>
void Neighbour_List<DIM,Data>::SetNeighbour(int dim,int sign,Neighbour_List<DIM,Data>* point)
{
	unsigned i=((dim-1)<<1)+((sign+1)>>1);
	m_neigh[i]=point;
}

template<int DIM,typename Data>
Neighbour_List<DIM,Data>* Neighbour_List<DIM,Data>::GetNeighbour(int dim,int sign)
{
	unsigned i=((dim-1)<<1)+((sign+1)>>1);
	return m_neigh[i];
}

template<int DIM,typename Data>
const Data& Neighbour_List<DIM,Data>::Get()
{
	return m_data;
}


template<int DIM,typename Data>
Data& Neighbour_List<DIM,Data>::GetRef()
{
	return m_data;
}

template<int DIM,typename Data>
void Neighbour_List<DIM,Data>::Set(const Data& data)
{
	m_data=data;
}
