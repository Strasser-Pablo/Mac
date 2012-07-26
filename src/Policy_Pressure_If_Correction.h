#ifndef Policy_Pressure_If_Correction_H
#define Policy_Pressure_If_Correction_H
template <typename Data>
class Policy_Pressure_If_Correction
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
	public:
	Policy_Pressure_If_Correction()
	{
	}
	bool Get_Pressure_If_Correction(type_data_neigh* neigh)
	{
		if(neigh->GetRef().GetIsInDomain())
		{
			return true;
		}
		for(int i=1;i<=type_dim;++i)
		{
			type_data_neigh* neigh2=neigh->GetNeighbour(i,-1);
			if(neigh2==nullptr)
			{
				continue;
			}
			if(neigh2->GetRef().GetIsInDomain())
			{
				return true;
			}
		}
		return false;
	}
	bool Get_Pressure_If_Correction(type_data_neigh* neigh,int i)
	{
		if(neigh->GetRef().GetIsInDomain())
		{
			return true;
		}
		type_data_neigh* neigh2=neigh->GetNeighbour(i,-1);
		if(neigh2==nullptr)
		{
			return false;
		}
		if(neigh2->GetRef().GetIsInDomain())
		{
			return true;
		}
		return false;
	}
};
#endif
