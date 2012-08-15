#ifndef Algorithms_Speed_Constant_Mirror_H
#define Algorithms_Speed_Constant_Mirror_H

#include <unordered_set>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Speed_Constant_Mirror : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_offset type_neigh;
	typedef typename type_grid::type_key type_key;
	typedef typename type_grid::type_hash type_hash;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_Data_Grid::type_data::type_speed::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Speed_Constant_Mirror(DataType data,const Policy& pol) :Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		typedef unordered_set<type_data_key,type_hash> type_unordered_set;
		type_unordered_set m_set(10,m_grid.GetHash());
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			type_data_key k=it.key();
			if(it.data().Speed_GetRef().Speed_Is_One_Const())
			{
				m_set.insert(it.key());
			}
		}
		for(typename type_unordered_set::iterator it=m_set.begin();it!=m_set.end();++it)
		{
			type_data_key k0=*it;
			type_data_key k=*it;
			for(int i=1;i<=type_dim;++i)
			{
				k.GetRef(i)+=1;
				for(int j=1;j<=type_dim;++j)
				{
					m_grid[k].Speed_GetRef().Speed_Set(j,0);
				}
				k.GetRef(i)-=1;
			}
		}
		for(typename type_unordered_set::iterator it=m_set.begin();it!=m_set.end();++it)
		{
			type_data_key k0=*it;
			type_data_key k=*it;
			for(int i=1;i<=type_dim;++i)
			{
				k.GetRef(i)+=1;
				if(m_grid[k0].Speed_GetRef().Speed_Get_Const(i))
				{
					m_grid[k].Speed_GetRef().Speed_Set(i,m_grid[k0].GetRef().Speed_Get(i));
				}
				k.GetRef(i)-=1;
			}
		}
	}
};
#endif
