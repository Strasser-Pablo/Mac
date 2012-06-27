#ifndef Neighbour_List_H
#define Neighbour_List_H

#include <iostream>
using namespace std;

template<int DIM,typename Data>
class Neighbour_List
{
	Data m_data;
	Neighbour_List* m_neigh[2*DIM];
	public:
	typedef Data type_data;
	Neighbour_List(const Data &data):m_data(data)
	{
		for(int i=0;i<2*DIM;++i)
		{
			m_neigh[i]=nullptr;
		}
	};
	Neighbour_List()
	{
		for(int i=0;i<2*DIM;++i)
		{
			m_neigh[i]=nullptr;
		}
	}
	void SetNeighbour(int dim,int sign,Neighbour_List<DIM,Data>* point);
	Neighbour_List<DIM,Data>* GetNeighbour(int dim,int sign);
	Data& GetRef();
	const Data& Get();
	void Set(const Data& data);
};

#include "Neighbour_List.tpp"
#endif
