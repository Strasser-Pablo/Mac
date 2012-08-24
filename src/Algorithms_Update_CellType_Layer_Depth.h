#ifndef Algorithms_Update_CellType_Layer_Depth_H
#define Algorithms_Update_CellType_Layer_Depth_H

#include <stack>
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Update_CellType_Layer_Depth : public Policy
{
	using Policy::GetLayerMax;
	using Policy::GetDepthMax;
	using Policy::GetDepthInterior;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_offset type_data_neigh;
	typedef typename type_grid::type_key type_data_key;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_data_key::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Update_CellType_Layer_Depth(DataType data,const Policy& pol) :Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		typedef pair<type_data_neigh,type_data_key> type_pair;
		stack<type_pair> s;
		stack<type_pair> sback;
		stack<type_pair> s2;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Depth_GetRef().SetDepthEmpty();
			bool b=false;
			if(it.data().Layer_GetRef().GetLayer()==0)
			{
				for(int i=1;i<=type_dim;++i)
				{
					if(!b)
					{
						for(int si=-1;si<=1;si+=2)
						{
							if((!it.data().GetNeighbour(i,si).IsValid())|| it.data().GetNeighbour(i,si).Layer_GetRef().GetIsLayerEmpty())
							{
								it.data().Depth_GetRef().SetDepth(0);
								s.push(type_pair(it.data(),it.key()));
								b=true;
								break;
							}
						}
					}
				}
			}
		}
		sback=s;
		for(int lay=1;lay<=GetLayerMax();++lay)
		{
			while(!s.empty())
			{
				type_data_neigh neigh=s.top().first;
				type_data_key key=s.top().second;
				s.pop();
				for(int i=1;i<=type_dim;++i)
				{
					for(int si=-1;si<=1;si+=2)
					{
						if((!neigh.GetNeighbour(i,si).IsValid())||neigh.GetNeighbour(i,si).Layer_GetRef().GetIsLayerEmpty())
						{
							key.GetRef(i)+=si;
							m_grid[key].Layer_GetRef().SetLayer(lay);
							m_grid[key].CellType_GetRef().SetAir();
							s2.push(type_pair(m_grid[key],key));
							key.GetRef(i)-=si;
						}
					}
				}
			}
			s2.swap(s);
		}
		while(!s.empty())
		{
			type_data_neigh neigh=s.top().first;
			type_data_key key=s.top().second;
			s.pop();
			for(int i=1;i<=type_dim;++i)
			{
				if((!neigh.GetNeighbour(i,1).IsValid())||neigh.GetNeighbour(i,1).Layer_GetRef().GetIsLayerEmpty())
				{
					key.GetRef(i)+=1;
					m_grid[key].Layer_GetRef().SetLayer(GetLayerMax()+1);
					m_grid[key].CellType_GetRef().SetAir();
					key.GetRef(i)-=1;
				}
			}
		}
		for(int depth=1;;++depth)
		{
			while(!sback.empty())
			{
				type_data_neigh neigh=sback.top().first;
				type_data_key key=sback.top().second;
				sback.pop();
				for(int i=1;i<=type_dim;++i)
				{
					for(int si=-1;si<=1;si+=2)
					{
						if(neigh.GetNeighbour(i,si).Layer_GetRef().GetLayer()==0&&(neigh.GetNeighbour(i,si).Depth_GetRef().GetIsDepthEmpty()))
						{
							key.GetRef(i)+=si;
							m_grid[key].Layer_GetRef().SetLayer(0);
							m_grid[key].Depth_GetRef().SetDepth(depth);
							if(depth<GetDepthInterior())
							{
								m_grid[key].CellType_GetRef().SetFluid();
							}
							else
							{
								m_grid[key].CellType_GetRef().SetInterior();
							}
							s2.push(type_pair(m_grid[key],key));
							key.GetRef(i)-=si;
						}
					}
				}
			}
			s2.swap(sback);
			if(sback.empty())
			{
				break;
			}
		}
	}
};

#endif
