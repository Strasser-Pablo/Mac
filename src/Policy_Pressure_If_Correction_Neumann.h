#ifndef Policy_Pressure_If_Correction_Neumann__H
#define Policy_Pressure_If_Correction_Neumann_H
template <typename Data>
class Policy_Pressure_If_Correction_Neumann
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	static const int type_dim=type_Data_Grid::type_speed::type_dim;
	public:
	Policy_Pressure_If_Correction_Neumann()
	{
	}
	bool Get_Pressure_If_Correction(type_neigh neigh)
	{
		if(neigh.CellType.GetRef().GetIsInDomain())
		{
			return true;
		}
		for(int i=1;i<=type_dim;++i)
		{
			type_neigh neigh2=neigh.GetNeighbour(i,-1);
			if(!neigh2.IsValid())
			{
				continue;
			}
			if(neigh2.CellType_GetRef().GetIsInDomain())
			{
				return true;
			}
		}
		return false;
	}
	bool Get_Pressure_If_Correction(type_neigh neigh,int i)
	{
		if(neigh.CellType_GetRef().GetIsInDomain())
		{
			return true;
		}
		type_neigh neigh2=neigh.GetNeighbour(i,-1);
		if(!neigh2.IsValid())
		{
			return false;
		}
		if(neigh2.CellType_GetRef().GetIsInDomain())
		{
			return true;
		}
		return false;
	}
};
#endif
