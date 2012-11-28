#ifndef Algorithms_Delete_MacCell_H
#define Algorithms_Delete_MacCell_H

#include "Data_Chunk_CellType_SFINAE.h"
#include <unordered_map>
#include <sys/times.h>
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
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
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
		long t_end=times(&t2);
		cout<<"real Delete MacCell "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Delete MacCell "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
	template<typename T=type_data_neigh>
	typename Data_Chunk_CellType_void_Not_SFINAE<type_data_neigh,T>::type Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
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
		long t_end=times(&t2);
		cout<<"real Delete MacCell "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Delete MacCell "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};
#endif
