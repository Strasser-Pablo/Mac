#ifndef Policy_Gravity_H
#define Policy_Gravity_H

template<typename Data>
class Policy_Gravity
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_value;
	typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_Time_Type& m_dt;
	type_Data_Grid& m_grid;
	const type_speed_value m_g;
	const int m_i;
	bool NeedToApply(const type_neigh neigh)
	{
		if(neigh.CellType_GetRef().GetIsFluid())
		{
			return true;
		}
		if(neigh.Layer_GetRef().GetIsLayerEmpty())
		{
			return false;
		}
		type_neigh neigh2=neigh.GetNeighbour(m_i,-1);
		if(!neigh2.IsValid())
		{
			return false;
		}
		if(neigh2.CellType_GetRef().GetIsFluid())
		{
			return true;
		}
		return false;
	}
	public:
	Policy_Gravity(Data& data,type_speed_value g,int i):m_dt(data.m_data.GetTimingData().m_dt),m_grid(data.m_data.GetGridData()),m_g(g),m_i(i)
	{
	}
	void ApplyGravity(type_neigh neigh)
	{
		if(NeedToApply(neigh))
		{
			neigh.Speed_GetRef().Speed_Set(m_i,neigh.Speed_GetRef().Speed_Get(m_i)+m_g*m_dt);
		}
	}
};

#endif
