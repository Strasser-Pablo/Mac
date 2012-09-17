#ifndef Policy_Upwind_1_Order_Dir_H
#define Policy_Upwind_1_Order_Dir_H

template <typename Data,typename Policy>
class Policy_Upwind_1_Order_Dir : public Policy
{
	using Policy::Get_Speed_At_Bound;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_data_value;
	typedef typename type_speed::type_speed type_speed_vect;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	static const int type_dim=type_speed::type_dim;

	const type_spacing_vector &m_1_h;
	type_Data_Grid& m_grid;
	type_speed_data_value Get_Convection_Element(int i,int j,type_neigh m_neigh)
	{
		if(i!=j)
		{
			type_speed_data_value U1;
			type_speed_data_value U2;
			type_speed_data_value U=Get_Speed_At_Bound(m_neigh,i,j);
			if(U>0)
			{
				U1=m_neigh.Speed_GetRef().Get(i);
				m_neigh=m_neigh.GetNeighbour(j,-1);
				U2=m_neigh.Speed_GetRef().Get(i);
				U*=(U1-U2)*m_1_h.Get(j);
			}
			else
			{
				U1=m_neigh.Speed_GetRef().Get(i);
				m_neigh=m_neigh.GetNeighbour(j,1);
				U2=m_neigh.Speed_GetRef().Get(i);
				U*=(U2-U1)*m_1_h.Get(j);
			}
			return U;
		}
		else
		{
			type_speed_data_value U0=m_neigh.Speed_GetRef().Get(i);
			type_speed_data_value U1=m_neigh.GetNeighbour(i,1).Speed_GetRef().Get(i);
			type_speed_data_value U2=m_neigh.GetNeighbour(i,-1).Speed_GetRef().Get(i);
			type_speed_data_value U=0.25*U1+0.25*U2+0.5*U0;
			if(U>0)
			{
				U*=(U0-U2)*m_1_h.Get(j);
			}
			else
			{
				U*=(U1-U0)*m_1_h.Get(j);
			}
			return U;
		}
	}
	public:
	Policy_Upwind_1_Order_Dir(Data& data,const Policy & pol) :Policy(pol), m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_speed_vect Get_Convection_Speed(type_neigh m_neigh)
	{
		type_speed_vect ret;
		for(int i=1;i<=type_dim;++i)
		{
			type_speed_data_value temp=0;
			for(int j=1;j<=type_dim;++j)
			{
				temp-=Get_Convection_Element(i,j,m_neigh);
			}
			ret.GetRef(i)=temp;
		}
		return ret;
	}

	type_speed_data_value Get_Convection_Speed(type_neigh m_neigh,int i)
	{
		type_speed_data_value ret=0;
		for(int j=1;j<=type_dim;++j)
		{
			ret-=Get_Convection_Element(i,j,m_neigh);
		}
		return ret;
	}
};

#endif
