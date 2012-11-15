#ifndef Algorithms_Speed_Repeat_Constant_H
#define Algorithms_Speed_Repeat_Constant_H

#include <unordered_set>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Speed_Repeat_Constant : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_offset type_neigh;
	typedef typename type_grid::type_key type_key;
	typedef typename type_grid::type_hash type_hash;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_data::type_Data_Grid::type_data::type_speed::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Speed_Repeat_Constant(DataType data,const Policy& pol) :Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		typedef std::function<size_t(type_neigh)> type_hash;
		type_hash f=[](type_neigh neigh)
		{
			return reinterpret_cast<size_t>(neigh.GetBase());
		};
		typedef unordered_set<type_neigh,type_hash> type_unordered;
		type_unordered m_set(10,f);
		type_unordered m_set2(10,f);
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			type_key k=it.key();
			if(it.data().Speed_GetRef().Is_One_Const()&&it.data().CellType_GetRef().GetIsFluid())
			{
				m_set.insert(it.data());
			}
			if(it.data().Speed_GetRef().Is_One_Const()&&it.data().CellType_GetRef().GetIsFluid()&&!it.data().CellType_GetRef().GetIsInflow())
			{
				m_set2.insert(it.data());
			}
		}
		for(typename type_unordered::iterator it=m_set2.begin();it!=m_set2.end();++it)
		{
			type_neigh neigh;
			type_neigh neigh2=*it;
			for(int s=-1;s<=1;s+=2)
			{
				for(int i=1;i<=type_dim;++i)
				{
					neigh=it->GetNeighbour(i,s);
					if(!neigh.IsValid()||neigh.Layer_GetRef().GetLayer()!=0)
					{
						continue;
					}
					neigh2.Speed_GetRef().Set(i,neigh.Speed_GetRef().Get(i),true);
				}
			}
		}
		m_set2.clear();
		int lay=1;
		while(!m_set.empty())
		{
			for(typename type_unordered::iterator it=m_set.begin();it!=m_set.end();++it)
			{
				type_neigh neigh;
				for(int s=-1;s<=1;s+=2)
				{
					for(int i=1;i<=type_dim;++i)
					{
						neigh=it->GetNeighbour(i,s);
						if(!neigh.IsValid()||neigh.Layer_GetRef().GetLayer()!=lay)
						{
							continue;
						}
						for(int j=1;j<=type_dim;++j)
						{
							neigh.Speed_GetRef().Set(j,0);
						}
						neigh.Speed_GetRef().Set(i,it->Speed_GetRef().Get(i));
						m_set2.insert(neigh);
					}
				}
			}
			m_set.clear();
			++lay;
			m_set.swap(m_set2);
		}
	}
};
#endif
