#ifndef Algorithms_RungeKutta_H
#define Algorithms_RungeKutta_H
//Need 3 speed and 1 acceleration
template <typename Data,typename Policy>
class Algorithms_RungeKutta : public Policy
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
	Algorithms_RungeKutta(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt)
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

		type_chunk_speed::ispeed=2;

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*0.5,true);
			it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./6.,true);
		}

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Acceleration_GetRef().SetZero(true);
		}

		Policy::Divergence_Projection();
		Policy::Do();

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt*0.5,true);
			it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./3.,true);
		}

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Acceleration_GetRef().SetZero(true);
		}

		Policy::Divergence_Projection();
		Policy::Do();

		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Speed_GetRef(2).Set(it.data().Speed_GetRef(0).Get()+it.data().Acceleration_GetRef().Get()*m_dt,true);
			it.data().Speed_GetRef(1).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./3.,true);
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
			it.data().Speed_GetRef(0).Set(it.data().Speed_GetRef(1).Get()+it.data().Acceleration_GetRef().Get()*m_dt*1./6.);
		}

		Policy::Divergence_Projection();
		Policy::End_Iteration();
	}
};
#endif
