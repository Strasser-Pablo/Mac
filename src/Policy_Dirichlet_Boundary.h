#ifndef POLICY_DIRICHLET_BOUNDARY_H
#define POLICY_DIRICHLET_BOUNDARY_H
template< typename Data>
class Policy_Dirichlet_Boundary
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    static const int type_dim=type_Data_Grid::type_key::type_dim;
    const type_spacing_vector &m_1_h;
    const type_spacing_vector &m_h;
    const type_speed_data_value &m_viscosity;
    type_Data_Grid& m_grid;
    type_Time_Type& m_dt;
public:
    Policy_Dirichlet_Boundary(Data data):m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_viscosity(data.m_data.GetGridData().m_viscosity),m_dt(data.m_data.GetTimingData().m_dt)
    {

    }

    bool GetIsDirichletBoundary(const type_neigh& neigh)
    {
        if(!neigh.CellType_GetRef().GetIsAir())
        {
            return false;
        }
        for(int i=1;i<=type_dim;++i)
        {

            for(int s=-1;s<=1;s+=2)
            {
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(neigh2.IsValid())
                {
                    if(!neigh2.CellType_GetRef().GetIsAir())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool GetIsDirichletBoundaryNeighbour(const type_neigh& neigh)
    {
        for(int i=1;i<=type_dim;++i)
        {
            for(int s=-1;s<=1;s+=2)
            {
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(GetIsDirichletBoundary(neigh2))
                {
                    return true;
                }
            }
        }
        return false;
    }

    type_speed_data_value GetDirichletSumBoundaryPressure(const type_neigh& neigh)
    {
        type_speed_data_value ret=0;
        for(int i=1;i<=type_dim;++i)
        {
            for(int s=-1;s<=1;s+=2)
            {
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(GetIsDirichletBoundary(neigh2))
                {
                    ret+=GetDirichletBoundaryPressure(neigh2)*m_1_h.Get(i)*m_1_h.Get(i);
                }
            }
        }
        return ret;
    }

    type_speed_data_value GetDirichletBoundaryPressure(const type_neigh& neigh)
    {
        type_speed_data_value ret=0;
            if(!neigh.CellType_GetRef().GetIsAir())
            {
                return 0;
            }
            for(int i=1;i<=type_dim;++i)
            {
                for(int s=-1;s<=1;s+=2)
                {
                    const type_neigh neigh2=neigh.GetNeighbour(i,s);
                    if(neigh2.IsValid())
                    {
                        if(!neigh2.CellType_GetRef().GetIsAir())
                        {
                            type_speed_data_value v1=neigh.Speed_GetRef(-1,false).Get(i);
                            const type_neigh neigh2=neigh.GetNeighbour(i,1);
                            type_speed_data_value v2=neigh2.Speed_GetRef(-1,false).Get(i);
                            ret-=2*m_viscosity*(v2-v1)*m_1_h.Get(i)*s;
                        }
                    }
                }
            }
            return ret;
        }
};

#endif // POLICY_DIRICHLET_BOUNDARY_H
