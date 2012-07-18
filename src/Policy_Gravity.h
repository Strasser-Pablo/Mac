#ifndef Policy_Gravity_H
#define Policy_Gravity_H

template<typename Data>
class Policy_Gravity
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_mac_cell type_data_mac_cell;
	typedef typename type_data_mac_cell::type_pressure type_pressure;
	typedef typename type_Data_Grid::type_data_key type_data_key;
	typedef typename type_Data_Grid::type_data_key_value type_data_key_value;
	typedef typename type_Data_Grid::type_data_vector type_data_vector;
	typedef typename type_Data_Grid::type_data_value type_data_value;
	typedef typename type_Data_Grid::type_data_neigh type_data_neigh;
	typedef typename type_data_mac_cell::type_speed type_speed;
	static const int type_dim=type_Data_Grid::type_dim;
	typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_Time_Type& m_dt;
	type_Data_Grid& m_grid;
	const type_data_value m_g;
	const int m_i;
	bool NeedToApply(type_data_neigh* neigh)
	{
		if(neigh->GetRef().GetIsFluid())
		{
			return true;
		}
		if(neigh->GetRef().GetIsLayerEmpty())
		{
			return false;
		}
		for(int i=1;i<=type_dim;++i)
		{
			type_data_neigh* neigh2=neigh->GetNeighbour(i,-1);
			if(neigh2==nullptr)
			{
				return false;
			}
			if(neigh2->GetRef().GetIsFluid())
			{
				return true;
			}
		}
		return false;
	}
	public:
	Policy_Gravity(Data& data,type_data_value g,int i):m_dt(data.m_data.GetTimingData().m_dt),m_grid(data.m_data.GetGridData()),m_g(g),m_i(i)
	{
	}
	void ApplyGravity(type_data_neigh* neigh)
	{
		if(NeedToApply(neigh))
		{
			neigh->GetRef().Speed_Set(m_i,neigh->GetRef().Speed_Get(m_i)+m_g*m_dt);
		}
	}
};

#endif
