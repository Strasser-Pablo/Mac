#ifndef Algorithms_Delete_MacCell_H
#define Algorithms_Delete_MacCell_H

#include "Data_Chunk_CellType_SFINAE.h"
#include <unordered_map>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Delete_MacCell : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data type_data_neigh;
	typedef typename type_grid::iterator iterator;
	type_grid& m_grid;
	public:
	Algorithms_Delete_MacCell(DataType data,const Policy& pol) : Policy(pol), m_grid(data.m_data.GetGridData())
	{
	}
	
	template<typename T=type_data_neigh>
	typename Data_Chunk_CellType_void_SFINAE<type_data_neigh,T>::type Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().Layer_GetRef().GetIsLayerEmpty()&&!it.data().CellType_GetRef().GetIsNoDelete())
			{
				it=m_grid.erase(it);
				if(it==m_grid.end())
				{
					break;
				}
			}
		}
	
	}
	template<typename T=type_data_neigh>
	typename Data_Chunk_CellType_void_Not_SFINAE<type_data_neigh,T>::type Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().Layer_GetRef().GetIsLayerEmpty())
			{
				it=m_grid.erase(it);
				if(it==m_grid.end())
				{
					break;
				}
			}
		}
	
	}
};
#endif
