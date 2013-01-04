#ifndef ALGORITHMS_SOLVE_PRESSURE_FORCE_H
#define ALGORITHMS_SOLVE_PRESSURE_FORCE_H
template <typename Data,typename Policy>
class Algorithms_Solve_Pressure_Force
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
    Policy& m_pol;
public:
    Algorithms_Solve_Pressure_Force(Data& m_data,Policy & pol):m_pol(pol)
    {

    }
    void Do()
    {
        bool b=type_chunk_speed::GetAccel_Instead_Speed();
        type_chunk_speed::SetAccel_Instead_Speed(true);
        m_pol.Init_Iteration();
        m_pol.Divergence_Projection();
        m_pol.End_Iteration();
        type_chunk_speed::SetAccel_Instead_Speed(b);
    }
};

#endif // ALGORITHMS_SOLVE_PRESSURE_FORCE_H
