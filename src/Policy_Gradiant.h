#ifndef Policy_Gradiant_H
#define Policy_Gradiant_H

template<typename Data>
class Policy_Gradiant
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data type_data;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_data::type_speed::type_speed type_speed;
	typedef typename type_data::type_speed::type_data_value type_speed_value;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	static const int type_dim=type_data::type_speed::type_dim;
	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Gradiant(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_speed Get_Gradiant(type_neigh m_neigh)
	{
		type_speed ret;
		for(int i=1;i<=type_dim;++i)
		{
			type_speed_value temp=m_neigh.Pressure_GetRef().Pressure_Get().Get()*m_1_h.Get(i);
			temp-=m_neigh.GetNeighbour(i,-1).Pressure_GetRef().Pressure_Get().Get()*m_1_h.Get(i);
			ret.GetRef(i)=temp;
		}
		return ret;
	}

	type_speed_value Get_Gradiant(type_neigh m_neigh,int i)
	{
		type_speed_value ret=m_neigh.Pressure_GetRef().Pressure_Get().Get()*m_1_h.Get(i);
		ret-=m_neigh.GetNeighbour(i,-1).Pressure_GetRef().Pressure_Get().Get()*m_1_h.Get(i);
		return ret;
	}
};

#endif
