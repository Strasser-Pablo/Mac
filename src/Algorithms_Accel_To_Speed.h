#ifndef ALGORITHMS_ACCEL_TO_SPEED_H
#define ALGORITHMS_ACCEL_TO_SPEED_H
template <typename Data,typename Policy>
class Algorithms_Accel_To_Speed
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
    Policy& m_alg;
public:
    Algorithms_Accel_To_Speed(Data& m_data,Policy & pol):m_alg(pol)
    {

    }
   void Do()
   {
       bool b=type_chunk_speed::GetAccel_Instead_Speed();
       type_chunk_speed::SetAccel_Instead_Speed(true);
       m_alg.Do();
       type_chunk_speed::SetAccel_Instead_Speed(b);
   }
};
#endif // ALGORITHMS_ACCEL_TO_SPEED_H
