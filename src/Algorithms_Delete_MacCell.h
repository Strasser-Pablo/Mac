#ifndef Algorithms_Delete_MacCell_H
#define Algorithms_Delete_MacCell_H

#include <unordered_map>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Delete_MacCell : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::iterator iterator;
	type_data& m_data;
	type_grid& m_grid;
	public:
	Algorithms_Delete_MacCell(DataType data,const Policy& pol) : Policy(pol),m_data(data.m_data), m_grid(m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsLayerEmpty()&&!it.data().GetRef().GetIsNoDelete())
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
