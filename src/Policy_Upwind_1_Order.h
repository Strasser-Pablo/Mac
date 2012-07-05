#ifndef Policy_Upwind_1_Order_H
#define Policy_Upwind_1_Order_H

template <typename Data,typename Policy>
class Policy_Upwind_1_Order : public Policy
{
	using Policy::Get_Speed_At_Bound;
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
	type_data_value Get_Convection_Element(int i,int j,type_data_neigh* m_neigh)
	{
		type_data_value U1;
		type_data_value U2;
		type_data_value U=Get_Speed_At_Bound(m_neigh,i,j);
		if(U>0)
		{
			U1=m_neigh->GetRef().Speed_Get(i);
			m_neigh=m_neigh->GetNeighbour(j,-1);
			U2=m_neigh->GetRef().Speed_Get(i);
			U*=(U1-U2)*m_1_h.Get(j);
		}
		else
		{
			U1=m_neigh->GetRef().Speed_Get(i);
			m_neigh=m_neigh->GetNeighbour(j,1);
			U2=m_neigh->GetRef().Speed_Get(i);
			U*=(U2-U1)*m_1_h.Get(j);
		}
		return U;
	}
	public:
	Policy_Upwind_1_Order(Data& data,const Policy & pol) :Policy(pol), m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_grid(data.m_data.GetGridData())
	{
	}
	type_speed Get_Convection_Speed(type_data_neigh* m_neigh)
	{
		type_speed ret;
		for(int i=1;i<=type_dim;++i)
		{
			type_data_value temp=0;
			for(int j=1;j<=type_dim;++j)
			{
				temp-=Get_Convection_Element(i,j,m_neigh);
			}
			ret.GetRef(i)=temp;
		}
		return ret;
	}
};

#endif
