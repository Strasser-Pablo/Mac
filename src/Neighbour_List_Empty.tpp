#include <iostream>
using namespace std;
template<int DIM,typename Base>
void Neighbour_List_Empty<DIM,Base>::SetNeighbour(int dim,int sign,Neighbour_List_Empty<DIM,Base>* point)
{
	unsigned i=((dim-1)<<1)+((sign+1)>>1);
	m_neigh[i]=point;
}

template<int DIM,typename Base>
Neighbour_List_Empty<DIM,Base>* Neighbour_List_Empty<DIM,Base>::GetNeighbour(int dim,int sign) const
{
	unsigned i=((dim-1)<<1)+((sign+1)>>1);
	return m_neigh[i];
}
