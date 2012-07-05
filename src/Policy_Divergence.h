#ifndef Policy_Divergence_H
#define Policy_Divergence_H

template<typename Data>
class Policy_Divergence
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
	Round<type_data_value,type_data_key_value> m_round;
	static const int type_dim=type_Data_Grid::type_dim;
	const type_data_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Divergence(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_pressure Get_Divergence(type_data_neigh* m_neigh)
	{
		type_pressure ret(0);
		for(int i=1;i<=type_dim;++i)
		{
			ret-=m_neigh->GetRef().Speed_Get(i)*m_1_h.Get(i);
			ret+=m_neigh->GetNeighbour(i,1)->GetRef().Speed_Get(i)*m_1_h.Get(i);
		}
		return ret;
	}
};

#endif
