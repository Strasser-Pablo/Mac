#ifndef Algorithms_Viscosity_H
#define Algorithms_Viscosity_H

template <typename Data,typename Policy>
class Algorithms_Viscosity : public Policy
{
	using Policy::Get_Laplacian_Speed;
	using Policy::Get_If_Apply_Viscosity;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_mac_cell type_data_mac_cell;
	typedef typename type_data_mac_cell::type_pressure type_pressure;
	typedef typename type_Data_Grid::type_data_key type_data_key;
	typedef typename type_Data_Grid::type_data_key_value type_data_key_value;
	typedef typename type_Data_Grid::type_data_vector type_data_vector;
	typedef typename type_Data_Grid::type_data_value type_data_value;
	typedef typename type_Data_Grid::type_data_neigh type_data_neigh;
	typedef typename type_data_mac_cell::type_speed type_speed;
	typedef typename type_Data_Grid::iterator iterator;
	typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_Data_Grid::type_dim;
	type_Data_Grid& m_grid;
	const type_Time_Type& m_dt;
	const type_data_value& m_viscosity;
	public:
	Algorithms_Viscosity(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_viscosity(data.m_data.GetGridData().m_viscosity)
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(Get_If_Apply_Viscosity(&it.data()))
			{
				it.data().GetRef().Speed_Temp_Set(it.data().GetRef().Speed_Get()+Get_Laplacian_Speed(&it.data())*m_viscosity*m_dt);
			}
			else
			{
				it.data().GetRef().Speed_Speed_To_Temp();
			}
		}
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().GetRef().Speed_Temp_To_Speed();
		}
	}
};

#endif
