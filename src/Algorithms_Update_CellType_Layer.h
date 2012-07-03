#ifndef Algorithms_Update_CellType_Layer_H
#define Algorithms_Update_CellType_Layer_H

#include <stack>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Update_CellType_Layer : public Policy
{
	using Policy::GetLayerMax;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_neigh type_data_neigh;
	typedef typename type_grid::type_data_key type_data_key;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_data_key::type_dim;
	type_data& m_data;
	type_grid& m_grid;
	public:
	Algorithms_Update_CellType_Layer(DataType data,const Policy& pol) :m_data(data.m_data), m_grid(m_data.GetGridData()),Policy(pol)
	{
	}
	void Do()
	{
		typedef pair<type_data_neigh*,type_data_key> type_pair;
		stack<type_pair> s;
		stack<type_pair> s2;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			bool b=false;
			if(it.data().GetRef().GetLayer()==0)
			{
				for(int i=1;i<=type_dim;++i)
				{
					if(!b)
					{
						for(int si=-1;si<=1;si+=2)
						{
							if(it.data().GetNeighbour(i,si)==nullptr)
							{
								s.push(type_pair(&it.data(),it.key()));
								b=true;
								break;
							}
						}
					}
				}
			}
			if(b)
			{
				for(int lay=1;lay<=GetLayerMax();++lay)
				{
					while(!s.empty())
					{
						type_data_neigh* neigh=s.top().first;
						type_data_key key=s.top().second;
						s.pop();
						for(int i=1;i<=type_dim;++i)
						{
							for(int si=-1;si<=1;si+=2)
							{
								if(neigh->GetNeighbour(i,si)==nullptr)
								{
									key.GetRef(i)+=si;
									m_grid[key].GetRef().SetLayer(lay);
									m_grid[key].GetRef().SetFluid();
									s2.push(type_pair(&m_grid[key],key));
									key.GetRef(i)-=si;
								}
							}
						}
					}
					s2.swap(s);
				}
			}
		}
	}
};

#endif
