#ifndef Policy_Speed_Interpolation_Linear_H
#define Policy_Speed_Interpolation_Linear_H

#include "RundingFunction.h"
#include "Physvector.h"

template <typename Data>
class Policy_Speed_Interpolation_Linear
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_mac_cell type_data_mac_cell;
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
	type_data_value Get_Speed_Impl(const type_data_vector& pos_scal,int i,type_data_neigh* neigh,int k)
	{
		if(i<type_dim)
		{
			type_data_value ret=(1-pos_scal.Get(i))*Get_Speed_Impl(pos_scal,i+1,neigh,k)+pos_scal.Get(i)*Get_Speed_Impl(pos_scal,i+1,neigh->GetNeighbour(i,1),k);
			return ret;
		}
		else
		{
			type_data_value ret=(1-pos_scal.Get(i))*(neigh->GetRef().Speed_Get(k))+pos_scal.Get(i)*(neigh->GetNeighbour(i,1)->GetRef().Speed_Get(k));
			return ret;
		}
	}
	public:
	Policy_Speed_Interpolation_Linear(Data& data) : m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_speed Get_Speed(const type_data_vector& pos)
	{
		type_data_vector pos_delta;
		type_data_key key0;
		type_speed ret;
		for(int i=1;i<=type_dim;++i)
		{
			pos_delta.GetRef(i)=pos.Get(i)*m_1_h.Get(i);
			key0.GetRef(i)=m_round(pos_delta.GetRef(i));
		}
		type_data_neigh* neigh=&m_grid[key0];
		for(int k=1;k<=type_dim;++k)
		{
			pos_delta.GetRef(k)+=0.5;
			ret.GetRef(k)=Get_Speed_Impl(pos_delta,1,neigh,k);
			pos_delta.GetRef(k)-=0.5;
		}
		return ret;
	}
};
#endif
