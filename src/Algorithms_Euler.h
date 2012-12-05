#include "SFINAE_Is_Policy_With_Do_After.h"

#ifndef Algorithms_Euler_H
#define Algorithms_Euler_H

template <typename Data,typename Policy>
class Algorithms_Euler : public Policy
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
	typedef typename type_Data_Grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    typedef Policy type_policy;
	type_Time_Type& m_dt;
    type_Time_Type& m_t;
	type_Data_Grid& m_grid;
	public:
    Algorithms_Euler(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_t(data.m_data.GetTimingData().m_t)
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		type_chunk_speed::ispeed=0;
		type_chunk_speed::iacceleration=0;
		Policy::Init_Iteration();
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Acceleration_GetRef().SetZero(true);
		}
		Policy::Do();
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef().Set(it.data().Speed_GetRef().Get()+it.data().Acceleration_GetRef().Get()*m_dt);
		}
		type_chunk_speed::ispeed=0;
		Policy::Divergence_Projection();
		Policy::End_Iteration();
        m_t+=m_dt;
        DoAfter(this);
		long t_end=times(&t2);
		cout<<"real Euler "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Euler "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
    template<typename T,typename SFINAE_Is_Policy_With_Do_After<typename T::type_policy>::FALSE=0>
    void DoAfter(T* mthis)
    {
    }
    template<typename T,typename SFINAE_Is_Policy_With_Do_After<typename T::type_policy>::TRUE=0>
    void DoAfter(T* mthis)
    {
        Policy::DoAfter();
    }
};
#endif
