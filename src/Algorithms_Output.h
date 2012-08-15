#ifndef Algorithms_Output_H
#define Algorithms_Output_H

#include <list>
#include <string>

using namespace std;

template <typename Data,typename Policy>
class Algorithms_Output : Policy
{
	using Policy::OutputGridSpeed;
	using Policy::OutputGridPressure;
	using Policy::OutputTopology;
	using Policy::OutputAnimation;
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	int m_i=0;
	const type_Time_Type & m_t;
	list<string> filename_list;
	public:
	Algorithms_Output(Data & data,const Policy& pol,int i=0) : Policy(pol),m_i(i),m_t(data.m_data.GetTimingData().m_t)
	{
	}
	void Do()
	{
		OutputGridSpeed(m_i,filename_list);
		OutputGridPressure(m_i,filename_list);
		OutputTopology(m_i,filename_list);
		OutputAnimation(filename_list,m_t);
		filename_list.clear();
		++m_i;
	}
};
#endif
