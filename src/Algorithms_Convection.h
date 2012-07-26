#ifndef Algorithms_Convection_H
#define Algorithms_Convection_H

template <typename Data,typename Policy>
class Algorithms_Convection : public Policy
{
	using Policy::Get_Convection_Speed;
	using Policy::Get_If_Apply_Convection;
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
	static const int type_dim=type_Data_Grid::type_dim;
	typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_Data_Grid& m_grid;
	const type_Time_Type& m_dt;
	public:
	Algorithms_Convection(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt)
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().GetRef().Speed_Speed_To_Temp();
			for(int i=1;i<=type_dim;++i)
			{
				if(Get_If_Apply_Convection(&it.data(),i))
				{
					it.data().GetRef().Speed_Temp_Set(i,it.data().GetRef().Speed_Temp_Get(i)+Get_Convection_Speed(&it.data(),i)*m_dt);
				}
			}
		}
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().GetRef().Speed_Temp_To_Speed();
		}
	}
};

#endif
