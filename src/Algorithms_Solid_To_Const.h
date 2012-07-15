#ifndef Algorithms_Solid_To_Const_H
#define Algorithms_Solid_To_Const_H

template <typename DataType,typename Policy>
class Algorithms_Solid_To_Const : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data_grid::type_data_value type_data_value;
	typedef typename type_data_grid::type_data_vector type_data_vector;
	typedef typename type_grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_grid::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Solid_To_Const(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsSolid())
			{
				for(int i=1;i<=type_dim;++i)
				{
					it.data().GetRef().Speed_Set_Const(i);
					it.data().GetNeighbour(i,-1)->GetRef().Speed_Set_Const(i);
				}
			}
		}
	}
};

#endif
