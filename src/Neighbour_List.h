#ifndef Neighbour_List_H
#define Neighbour_List_H

/**
 * @ingroup GR_Data_Storage
 * @brief
 * This class store Data and allow to set and get pointer with respect to a sign and a direction.
 *
 * This is mean to be used as a class to store information in a grid with pointer acess to the neighbour.
 *
 * @tparam DIM Dimension of the problem. The total number of neighbour is the dobble of this number.
 * @tparam Data The Data to store.
 **/
template<int DIM,typename Data>
class Neighbour_List
{
	/**
	 * @brief
	 * The Data.
	 **/
	Data m_data;
	/**
	 * @brief
	 * The Neighbour pointer array.
	 * The value are accessed by 2*(i-1)+sign+1. Where i is from 1 to DIM.
	 **/
	Neighbour_List* m_neigh[2*DIM];
	public:
	/**
	 * @brief
	 * Type of Data.
	 **/
	typedef Data type_data;
	/**
	 * @brief
	 * Constructor.
	 * @param data Instance to be stored.
	 **/
	Neighbour_List(const Data &data):m_data(data)
	{
		for(int i=0;i<2*DIM;++i)
		{
			m_neigh[i]=nullptr;
		}
	};
	/**
	 * @brief
	 * Default Constructor.
	 **/
	Neighbour_List()
	{
		for(int i=0;i<2*DIM;++i)
		{
			m_neigh[i]=nullptr;
		}
	}
	/**
	 * @brief
	 * Set the pointer with given position and sign.
	 * @param dim Position to set, between 1 and type_dim.
	 * @param sign Sign of the neighbour, +-1.
	 * @param point Pointer to set.
	 **/
	void SetNeighbour(int dim,int sign,Neighbour_List<DIM,Data>* point);
	/**
	 * @brief
	 * Get the pointer with given position and sign.
	 * @param dim Position to set, between 1 and type_dim.
	 * @param sign Sign of the neighbour, +-1.
	 * @return Pointer stored.
	 **/
	Neighbour_List<DIM,Data>* GetNeighbour(int dim,int sign);
	/**
	 * @brief
	 * Get a Reference to the current value.
	 * @return Reference to Data.
	 **/
	Data& GetRef();
	const Data& GetRef() const;
	/**
	 * @brief
	 * Get the value.
	 * @return Constant reference to Data.
	 **/
	const Data& Get() const;
	/**
	 * @brief
	 * Set the data.
	 * @param data Value to set data to.
	 **/
	void Set(const Data& data);
};

#include "Neighbour_List.tpp"
#endif
