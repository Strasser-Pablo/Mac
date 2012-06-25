#ifndef Neighbour_List_H
#define Neighbour_List_H

template<int DIM,typename Data>
class Neighbour_List
{
	Data m_data;
	Data* m_neigh[2*DIM];
	Neighbour_List(const Neighbour_List&)=delete;
	Neighbour_List(Neighbour_List&&)=delete;
	public:
	Neighbour_List(const Data &data):m_data(data)
	{
	};
	Neighbour_List()
	{
	}
	void SetNeighbour(int dim,int sign,Data* point);
	Data* GetNeighbour(int dim,int sign);
	Data& GetRef();
	const Data& Get();
	void Set(const Data& data);
};

#include "Neighbour_List.tpp"
#endif
