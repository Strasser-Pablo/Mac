#ifndef Policy_Speed_Interpolation_Linear_Symmetric_H
#define Policy_Speed_Interpolation_Linear_Symmetric_H

#include "RundingFunction.h"
#include "Physvector.h"

template <typename Data>
class Policy_Speed_Interpolation_Linear_Symmetric;

template<typename Data>
class Policy_Speed_Interpolation_Linear_Functor_Symmetric
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_speed type_speed_vect;
	Policy_Speed_Interpolation_Linear_Symmetric<Data>& m_interp;	
	public:
	Policy_Speed_Interpolation_Linear_Functor_Symmetric(Policy_Speed_Interpolation_Linear_Symmetric<Data>& interp):m_interp(interp)
	{
	}
	type_speed_vect operator()(const type_spacing_vector& pos)
	{
		return m_interp.Get_Speed(pos);
	}

};

template <typename Data>
class Policy_Speed_Interpolation_Linear_Symmetric
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_data_value;
	typedef typename type_speed::type_speed type_speed_vect;
	typedef typename type_Data_Grid::type_key::type_data type_key_value;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	static const int type_dim=type_speed::type_dim;

	Round<type_speed_data_value,type_key_value> m_round;
	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	Policy_Speed_Interpolation_Linear_Functor_Symmetric<Data> m_funct;
	type_data_value Get_Speed_Impl(const type_spacing_vector& pos_scal,int i,type_neigh neigh,int k)
	{
		if(i<type_dim)
		{
			if(i!=k)
			{
				type_speed_data_value ret=(1-pos_scal.Get(i))*Get_Speed_Impl(pos_scal,i+1,neigh,k)+pos_scal.Get(i)*Get_Speed_Impl(pos_scal,i+1,neigh.GetNeighbour(i,1),k);
				return ret;
			}
			else
			{
				type_speed_data_value ret=(0.5-pos_scal.Get(i))*Get_Speed_Impl(pos_scal,i+1,neigh,k)+(0.5+pos_scal.Get(i))*Get_Speed_Impl(pos_scal,i+1,neigh.GetNeighbour(i,1),k);
				return ret;
			}
		}
		else
		{
			if(i!=k)
			{
				type_speed_data_value ret=(1-pos_scal.Get(i))*(neigh.Speed_GetRef().Speed_Get(k))+pos_scal.Get(i)*(neigh.GetNeighbour(i,1).Speed_GetRef().Speed_Get(k));
				return ret;
			}
			else
			{
				type_speed_data_value ret=(0.5-pos_scal.Get(i))*(neigh.Speed_GetRef().Speed_Get(k))+(0.5+pos_scal.Get(i))*(neigh.GetNeighbour(i,1).Speed_GetRef().Speed_Get(k));
				return ret;
			}
		}
	}
	public:
	Policy_Speed_Interpolation_Linear_Symmetric(Data& data) : m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData()),m_funct(*this)
	{
	}
	type_speed_vect Get_Speed(const type_data_vector& pos)
	{
		type_spacing_vector pos_delta;
		type_key key0;
		type_speed_vect ret;
		for(int i=1;i<=type_dim;++i)
		{
			pos_delta.GetRef(i)=pos.Get(i)*m_1_h.Get(i);
			key0.GetRef(i)=m_round(pos_delta.GetRef(i));
			pos_delta.GetRef(i)-=key0.GetRef(i);
		}
		type_data_vector pos_delta2;
		for(int k=1;k<=type_dim;++k)
		{
			type_data_key key;
			for(int j=1;j<=type_dim;++j)
			{
				if(j!=k)
				{
					if(pos_delta.GetRef(j)<0)
					{
						key.GetRef(j)=key0.GetRef(j)-1;
						pos_delta2.GetRef(j)=1+pos_delta.GetRef(j);
					}
					else
					{
						key.GetRef(j)=key0.GetRef(j);
						pos_delta2.GetRef(j)=pos_delta.GetRef(j);
					}
				}
				else
				{
					key.GetRef(j)=key0.GetRef(j);
					pos_delta2.GetRef(j)=pos_delta.GetRef(j);
				}
			}
			type_data_neigh neigh=m_grid[key];
			ret.GetRef(k)=Get_Speed_Impl(pos_delta2,1,neigh,k);
		}
		return ret;
	}
	type_speed_data_value Get_Speed_At_Bound(type_neigh neigh,int i,int j)
	{
		if(i==j)
		{
			return neigh.Speed_GetRef().Speed_Get(j);
		}
		return 0.25*(neigh.Speed_GetRef().Speed_Get(j)+neigh.GetNeighbour(j,1).Speed_GetRef().Speed_Get(j)+neigh.GetNeighbour(i,-1).Speed_GetRef().Speed_Get(j)+neigh.GetNeighbour(i,-1).GetNeighbour(j,1).Speed_GetRef().Speed_Get(j));
	}
	Policy_Speed_Interpolation_Linear_Functor_Symmetric<Data>& Get_Speed_Functor()
	{
		return m_funct;
	}
};
#endif
