#include "SFINAE_Is_Policy_With_Do_After.h"
#include "SFINAE_Is_Policy_With_Do_Before.h"

#ifndef Algorithms_RungeKutta_all_H
#define Algorithms_RungeKutta_all_H
//Need 3 speed and 1 acceleration
template <typename Data,typename Policy>
class Algorithms_RungeKutta_all : public Policy
{
    using Policy::move_particle_GetRef;
    using Policy::move_particle_Begin;
    using Policy::move_particle_End;
    using Policy::move_particle_acceleration;
    using Policy::move_particle_SetDefault;
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_data::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    typedef typename Policy::move_particle_iterator move_particle_iterator;
    typedef typename Policy::move_particle_type_speed move_particle_type_speed;
    typedef Policy type_policy;
    type_Time_Type& m_dt;
    type_Time_Type& m_t;
    type_Data_Grid& m_grid;
    public:
    Algorithms_RungeKutta_all(Data data,Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_t(data.m_data.GetTimingData().m_t)
    {
    }
    Algorithms_RungeKutta_all(Data data, Policy&& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_t(data.m_data.GetTimingData().m_t)
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
        move_particle_SetDefault(0);

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
            it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*0.5,true);
            it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./6.,true);
        }
        for(move_particle_iterator it=this->move_particle_Begin();it!=this->move_particle_End();++it)
        {
            this->move_particle_GetRef(it,2)=this->move_particle_GetRef(it,0)+m_dt*0.5*this->move_particle_acceleration(it,0);
            this->move_particle_GetRef(it,1)=this->move_particle_GetRef(it,0)+m_dt*1.0/6.0*this->move_particle_acceleration(it,0);
        }

        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Acceleration_GetRef().SetZero(true);
        }

        DoAfter(this);
        m_t+=0.5*m_dt;
        type_chunk_speed::ispeed=2;
        this->move_particle_SetDefault(2);
        DoBefore(this);
        t_deb=times(&t1);
        Policy::Do();
        t_end=times(&t2);
        cout<<"real Calculate Grid "<<(t_end-t_deb)/conv<<endl;
        cout<<"user Calculate Grid "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;



        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*0.5,true);
            it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./3.,true);
        }
        for(move_particle_iterator it=this->move_particle_Begin();it!=this->move_particle_End();++it)
        {
            this->move_particle_GetRef(it,2)=this->move_particle_GetRef(it,0)+m_dt*0.5*this->move_particle_acceleration(it,2);
            this->move_particle_GetRef(it,1)+=m_dt*1.0/3.0*this->move_particle_acceleration(it,2);
        }


        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Acceleration_GetRef().SetZero(true);
        }
        DoAfter(this);
        DoBefore(this);
        t_deb=times(&t1);
        Policy::Do();
        t_end=times(&t2);
        cout<<"real Calculate Grid "<<(t_end-t_deb)/conv<<endl;
        cout<<"user Calculate Grid "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;


        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt,true);
            it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./3.,true);
        }
        for(move_particle_iterator it=this->move_particle_Begin();it!=this->move_particle_End();++it)
        {
            this->move_particle_GetRef(it,2)=this->move_particle_GetRef(it,0)+m_dt*this->move_particle_acceleration(it,2);
            this->move_particle_GetRef(it,1)=this->move_particle_GetRef(it,1)+m_dt*1.0/3.0*this->move_particle_acceleration(it,2);
        }


        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Acceleration_GetRef().SetZero(true);
        }

        DoAfter(this);
        m_t+=0.5*m_dt;
        DoBefore(this);
        t_deb=times(&t1);
        Policy::Do();
        t_end=times(&t2);
        cout<<"real Calculate Grid "<<(t_end-t_deb)/conv<<endl;
        cout<<"user Calculate Grid "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;


        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Speed_GetRef(0).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./6.);
        }
        for(move_particle_iterator it=this->move_particle_Begin();it!=this->move_particle_End();++it)
        {
            this->move_particle_GetRef(it,0)=this->move_particle_GetRef(it,1)+m_dt*1.0/6.0*this->move_particle_acceleration(it,2);
        }

        DoAfter(this);
        type_chunk_speed::ispeed=0;
        this->move_particle_SetDefault(0);
        long tA_end=times(&tA2);
        cout<<"real RungeKutta "<<(tA_end-tA_deb)/conv<<endl;
        cout<<"user RungeKutta "<<(tA2.tms_utime-tA1.tms_utime)/conv<<endl;
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
