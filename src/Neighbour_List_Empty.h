#ifndef Neighbour_List_Empty_H
#define Neighbour_List_Empty_H

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
template<int DIM,typename Base>
class Neighbour_List_Empty : public Base
{
	/**
	 * @brief
	 * The Neighbour pointer array.
	 * The value are accessed by 2*(i-1)+sign+1. Where i is from 1 to DIM.
	 **/
	Neighbour_List_Empty<DIM,Base>* m_neigh[2*DIM];
	public:
	/**
	 * @brief
	 * Default Constructor.
	 **/
	template< typename ...Arg>
	Neighbour_List_Empty(Arg &... arg):Base(arg...)
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
	void SetNeighbour(int dim,int sign,Neighbour_List_Empty<DIM,Base>* point);
	/**
	 * @brief
	 * Get the pointer with given position and sign.
	 * @param dim Position to set, between 1 and type_dim.
	 * @param sign Sign of the neighbour, +-1.
	 * @return Pointer stored.
	 **/
	Neighbour_List_Empty<DIM,Base>* GetNeighbour(int dim,int sign) const __attribute__ ((pure));
};

#include "Neighbour_List_Empty.tpp"
#endif
