#ifndef Policy_Von_Neumann_Boundary_H
#define Policy_Von_Neumann_Boundary_H

template<typename Data>
class Policy_Von_Neumann_Boundary
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
	type_Data_Grid& m_grid;
	public:
	Policy_Von_Neumann_Boundary(Data& data) :m_grid(data.m_data.GetGridData())
	{
	}
	bool Get_Is_Von_Neumann_Boundary(type_data_neigh* neigh,int i,int sign)
	{
		return m_grid.GetIsConstantInterface(*neigh,i,sign);
	}
};

#endif
