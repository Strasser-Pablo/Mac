#ifndef Policy_Laplacian_H
#define Policy_Laplacian_H

#include <cmath>

template<typename Data>
class Policy_Laplacian
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_pressure::type_pressure type_pressure;
	typedef typename type_Data_Grid::type_data::type_pressure::type_pressure::type_data type_data_pressure;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_key::type_data type_key_value;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_offset type_neigh;
	static const int type_dim=type_Data_Grid::type_spacing_vector::type_dim;
	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Laplacian(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_pressure Get_Laplacian(type_neigh m_neigh)
	{
		type_pressure ret;
		type_data_pressure temp=0;
		for(int i=1;i<=type_dim;++i)
		{
			temp-=2*m_neigh->GetRef().Pressure_Get().Get()*pow(m_1_h.Get(i),2);
			temp+=m_neigh->GetNeighbour(i,-1)->GetRef().Pressure_Get().Get()*pow(m_1_h.Get(i),2);
			temp+=m_neigh->GetNeighbour(i,1)->GetRef().Pressure_Get().Get()*pow(m_1_h.Get(i),2);
		}
		ret.Set(temp);
		return ret;
	}
};

#endif
