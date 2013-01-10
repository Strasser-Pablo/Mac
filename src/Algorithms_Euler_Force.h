#include "SFINAE_Is_Policy_With_Do_After.h"
#include "SFINAE_Is_Policy_With_Do_Before.h"

#ifndef Algorithms_Euler_Force_H
#define Algorithms_Euler_Force_H
//Need 3 speed and 1 acceleration
template <typename Data,typename Policy>
class Algorithms_Euler_Force : public Policy
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
    Algorithms_Euler_Force(Data data,Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_t(data.m_data.GetTimingData().m_t)
    {
    }
    Algorithms_Euler_Force(Data data, Policy&& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_t(data.m_data.GetTimingData().m_t)
    {
    }
    void Do()
    {
        struct tms tA1;
        struct tms tA2;
        double conv=double(sysconf(_SC_CLK_TCK));
        long tA_deb=times(&tA1);
        type_chunk_speed::ispeed=0;
        type_chunk_speed::iacceleration=0;

        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Acceleration_GetRef().SetZero(true);
        }

        struct tms t1;
        struct tms t2;
        DoBefore(this);
        long t_deb=times(&t1);
        Policy::Do();
        long t_end=times(&t2);
        cout<<"real Calculate Grid "<<(t_end-t_deb)/conv<<endl;
        cout<<"user Calculate Grid "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;


        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Speed_GetRef().Set(it.data().Speed_GetRef().Get()+it.data().Acceleration_GetRef().Get()*m_dt,true);
        }

        DoAfter(this);
        m_t+=m_dt;
        long tA_end=times(&tA2);
        cout<<"real Euler "<<(tA_end-tA_deb)/conv<<endl;
        cout<<"user Euler "<<(tA2.tms_utime-tA1.tms_utime)/conv<<endl;
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
    template<typename T,typename SFINAE_Is_Policy_With_Do_Before<typename T::type_policy>::FALSE=0>
    void DoBefore(T* mthis)
    {
    }
    template<typename T,typename SFINAE_Is_Policy_With_Do_Before<typename T::type_policy>::TRUE=0>
    void DoBefore(T* mthis)
    {
        Policy::DoBefore();
    }
};
#endif
