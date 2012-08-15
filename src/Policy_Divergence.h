#ifndef Policy_Divergence_H
#define Policy_Divergence_H

template<typename Data>
class Policy_Divergence
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data type_data_data;
	typedef typename type_data_data::type_pressure::type_pressure type_pressure;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_data_data::type_speed type_speed;
	static const int type_dim=type_speed::type_dim;
	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Divergence(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_pressure Get_Divergence(type_neigh m_neigh)
	{
		type_pressure ret(0);
		for(int i=1;i<=type_dim;++i)
		{
			ret-=m_neigh.Speed_GetRef().Speed_Get(i)*m_1_h.Get(i);
			ret+=m_neigh.GetNeighbour(i,1).Speed_GetRef().Speed_Get(i)*m_1_h.Get(i);
		}
		return ret;
	}
};

#endif
