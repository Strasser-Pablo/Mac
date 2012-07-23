#ifndef Algorithms_Output_Only_Speed_H
#define Algorithms_Output_Only_Speed_H

#include <list>
#include <string>

using namespace std;

template <typename Data,typename Policy>
class Algorithms_Output_Only_Speed : Policy
{
	using Policy::OutputGridSpeed;
	using Policy::OutputAnimation;
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data_grid::type_data_value type_data_value;
	typedef typename type_data_grid::type_data_vector type_data_vector;
	typedef typename type_grid::const_iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_grid::type_dim;
	int m_i=0;
	const type_Time_Type & m_t;
	list<string> filename_list;
	public:
	Algorithms_Output_Only_Speed(Data & data,const Policy& pol,int i=0) : Policy(pol),m_i(i),m_t(data.m_data.GetTimingData().m_t)
	{
	}
	void Do()
	{
		OutputGridSpeed(m_i,filename_list);
		OutputAnimation(filename_list,m_t);
		filename_list.clear();
		++m_i;
	}
};
#endif
