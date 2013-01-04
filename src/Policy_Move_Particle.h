#ifndef POLICY_MOVE_PARTICLE_H
#define POLICY_MOVE_PARTICLE_H

template <typename DataType,typename Policy>
class Policy_Move_Particle
{
    typedef typename DataType::type_data_struct type_data;
    typedef typename type_data::type_Data_Topology type_topology;
    typedef typename type_topology::type_particle_list type_particle_list;
    typedef typename type_topology::type_particle type_particle;
    typedef typename type_particle_list::iterator iterator;
    typedef typename type_data::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_speed::type_vector type_speed_vect;
    type_particle_list& m_list;
    type_Time_Type& m_dt;
    Policy m_pol;
    public:
    typedef iterator move_particle_iterator;
    typedef type_speed_vect move_particle_type_speed;

    Policy_Move_Particle(DataType data,const Policy& pol): m_pol(pol),m_list(data.m_data.GetTopologyData().GetRefToParticleList()),m_dt(data.m_data.GetTimingData().m_dt)
    {
    }
    type_speed_vect& move_particle_GetRef(iterator it,int i)
    {
        return (*it).GetParticlePosRef(i);
    }
    const type_speed_vect& move_particle_GetRef(iterator it,int i) const
    {
        return (*it).GetParticlePosRef(i);
    }
    iterator move_particle_Begin()
    {
        return m_list.begin();
    }
    iterator move_particle_End()
    {
        return m_list.end();
    }

    type_speed_vect& move_particle_acceleration(type_speed_vect& pos)
    {
        return m_pol.Get_Speed(pos);
    }
    type_speed_vect move_particle_acceleration(iterator it,int i)
    {
        return m_pol.Get_Speed(move_particle_GetRef(it,i));
    }

    static void move_particle_SetDefault(int i)
    {
        type_particle::SetIPos(i);
    }
    static int move_particle_GetDefault()
    {
        return type_particle::GetIPos();
    }
};
#endif // POLICY_MOVE_PARTICLE_H
