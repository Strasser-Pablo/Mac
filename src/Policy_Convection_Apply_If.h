#ifndef Policy_Convection_Apply_If_H
#define Policy_Convection_Apply_If_H

#include <cmath>

template<typename Data>
class Policy_Convection_Apply_If
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	static const int type_dim=type_speed::type_dim;
	public:
	Policy_Convection_Apply_If()
	{
	}
	bool Get_If_Apply_Convection(type_neigh neigh)
	{
		if(neigh.CellType_GetRef().GetIsFluid())
		{
			return true;
		}
		if(neigh.Layer_GetRef().GetIsLayerEmpty())
		{
			return false;
		}
		for(int i=1;i<=type_dim;++i)
		{
			type_neigh neigh2=neigh.GetNeighbour(i,-1);
			if(!neigh2.IsValid())
			{
				continue;
			}
			if(neigh2.GetRef().GetIsFluid())
			{
				return true;
			}
		}
		return false;
	}
	bool Get_If_Apply_Convection(type_neigh neigh,int i)
	{
		if(neigh.CellType_GetRef().GetIsFluid())
		{
			return true;
		}
		if(neigh.Layer_GetRef().GetIsLayerEmpty())
		{
			return false;
		}
		type_neigh neigh2=neigh.GetNeighbour(i,-1);
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
};

#endif
