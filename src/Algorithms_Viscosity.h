#ifndef Algorithms_Viscosity_H
#define Algorithms_Viscosity_H

template <typename Data,typename Policy>
class Algorithms_Viscosity : public Policy
{
	using Policy::Get_Laplacian_Speed;
	using Policy::Get_If_Apply_Viscosity;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_speed::type_data_value type_data_value;
	typedef typename type_Data_Grid::iterator iterator;
	static const int type_dim=type_Data_Grid::type_dim;
	type_Data_Grid& m_grid;
	const type_data_value& m_viscosity;
	public:
	Algorithms_Viscosity(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_viscosity(data.m_data.GetGridData().m_viscosity)
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(Get_If_Apply_Viscosity(it.data()))
			{
				it.data().Acceleration_GetRef().Set(it.data().Acceleration_GetRef().Get()+Get_Laplacian_Speed(it.data())*m_viscosity);
			}
		}
		long t_end=times(&t2);
		cout<<"real Viscosity "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Viscosity "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
