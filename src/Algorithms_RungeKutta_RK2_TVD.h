#ifndef Algorithms_RungeKutta_RK2_TVD_H
#define Algorithms_RungeKutta_RK2_TVD_H
//Need 2 speed and 1 acceleration
template <typename Data,typename Policy>
class Algorithms_RungeKutta_RK2_TVD : public Policy
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_Data_Grid::type_data::type_chunk_speed type_chunk_speed;
	typedef typename type_Data_Grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_Time_Type& m_dt;
	type_Data_Grid& m_grid;
	public:
	Algorithms_RungeKutta_RK2_TVD(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt)
	{
	}
	void Do()
	{
		type_chunk_speed::ispeed=0;
		type_chunk_speed::iacceleration=0;
		Policy::Init_Iteration();

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Acceleration_GetRef().SetZero(true);
		}

		Policy::Do();

		type_chunk_speed::ispeed=1;

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt,true);
		}

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Acceleration_GetRef().SetZero(true);
		}

		Policy::Divergence_Projection();
		Policy::Do();

		type_chunk_speed::ispeed=0;

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef(0).Set(0.5*it.data().Speed_GetRef(0).Get()+0.5*it.data().Speed_GetRef(1).Get()+ 0.5*it.data().Acceleration_GetRef(0).Get()*m_dt);
		}

		Policy::Divergence_Projection();
		Policy::End_Iteration();
	}
};
#endif
