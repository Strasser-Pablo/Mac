#ifndef Policy_Laplacian_Speed_H
#define Policy_Laplacian_Speed_H

#include <cmath>

template<typename Data>
class Policy_Laplacian_Speed
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_speed type_data_speed;
	typedef typename type_speed::type_data_value type_speed_value;
	typedef typename type_Data_Grid::type_offset type_neigh;
	static const int type_dim=type_speed::type_dim;
	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Laplacian_Speed(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_data_speed Get_Laplacian_Speed(type_neigh m_neigh)
	{
		type_data_speed ret;
		for(int i=1;i<=type_dim;++i)
		{
			type_speed_value temp=-2*m_neigh.Speed_GetRef().Get(i)*pow(m_1_h.Get(i),2);
			temp+=m_neigh.GetNeighbour(i,1).Speed_GetRef().Get(i)*pow(m_1_h.Get(i),2);
			temp+=m_neigh.GetNeighbour(i,-1).Speed_GetRef().Get(i)*pow(m_1_h.Get(i),2);
			ret.Set(i,temp);
		}
		return ret;
	}
};

#endif
