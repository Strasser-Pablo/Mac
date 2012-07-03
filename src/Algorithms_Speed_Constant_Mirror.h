#ifndef Algorithms_Speed_Constant_Mirror_H
#define Algorithms_Speed_Constant_Mirror_H

template <typename DataType,typename Policy>
class Algorithms_Speed_Constant_Mirror : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_neigh type_data_neigh;
	typedef typename type_grid::type_data_key type_data_key;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_data_key::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Speed_Constant_Mirror(DataType data,const Policy& pol) :m_grid(data.m_data.GetGridData()),Policy(pol)
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().Speed_Is_One_Const())
			{
				type_data_key k=it.key();
				for(int i=1;i<=type_dim;++i)
				{
					k.GetRef(i)+=1;
					if(it.data().GetRef().Speed_Get_Const(i))
					{
						m_grid[k].GetRef().Speed_Set(i,it.data().GetRef().Speed_Get(i));
					}
					else
					{
						m_grid[k].GetRef().Speed_Set(i,0);
					}
					k.GetRef(i)-=1;
				}
			}
		}
	}
};
#endif
