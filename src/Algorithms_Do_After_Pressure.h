#ifndef ALGORITHMS_DO_AFTER_PRESSURE_H
#define ALGORITHMS_DO_AFTER_PRESSURE_H
template <typename Data,typename Policy>
class Algorithms_Do_After_Pressure
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
    Policy& m_pol;
public:
    typedef int type_has_do_after;
    Algorithms_Do_After_Pressure(Data& m_data,Policy & pol):m_pol(pol)
    {

    }
    void DoAfter()
    {
        m_pol.Init_Iteration();
        m_pol.Divergence_Projection();
        m_pol.End_Iteration();
    }
};

#endif // ALGORITHMS_DO_AFTER_PRESSURE_H
