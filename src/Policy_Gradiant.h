#ifndef Policy_Gradiant_H
#define Policy_Gradiant_H

template<typename Data>
class Policy_Gradiant
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
	const type_data_vector &m_1_h;
	type_Data_Grid& m_grid;
	public:
	Policy_Gradiant(Data& data) :m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_speed Get_Gradiant(type_data_neigh* m_neigh)
	{
		type_speed ret;
		for(int i=1;i<=type_dim;++i)
		{
			type_data_value temp=m_neigh->GetRef().Pressure_Get().Get()*m_1_h.Get(i);
			temp-=m_neigh->GetNeighbour(i,-1)->GetRef().Pressure_Get().Get()*m_1_h.Get(i);
			ret.GetRef(i)=temp;
		}
		return ret;
	}

	type_data_value Get_Gradiant(type_data_neigh* m_neigh,int i)
	{
		type_data_value ret=m_neigh->GetRef().Pressure_Get().Get()*m_1_h.Get(i);
		ret-=m_neigh->GetNeighbour(i,-1)->GetRef().Pressure_Get().Get()*m_1_h.Get(i);
		return ret;
	}
};

#endif
