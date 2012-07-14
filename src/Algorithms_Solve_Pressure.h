#ifndef Algorithms_Solve_Pressure_H
#define Algorithms_Solve_Pressure_H

#include <cmath>
#include <map>
#include <deque>

using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Solve_Pressure: public Policy
{
	using Policy::Solve_Linear;
	using Policy::Get_Divergence;
	using Policy::Get_Gradiant;
	using Policy::Get_Is_Von_Neumann_Boundary;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data_grid::type_pressure type_pressure;
	typedef typename type_grid::type_data_neigh type_data_neigh;
	typedef typename type_data_grid::type_data_value type_data_value;
	typedef typename type_data_grid::type_data_vector type_data_vector;
	typedef typename type_grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_grid::type_dim;
	type_grid& m_grid;
	const type_data_vector& m_1_h;
	public:
	Algorithms_Solve_Pressure(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv())
	{
	}
	void Do()
	{
		// Upper bound of memory usage.
		int n=m_grid.size();
		int nEntry=2*type_dim*m_grid.size();
		int offset[n+1];
		int indice[nEntry];
		type_data_value value[nEntry];
		type_data_value b[n];
		type_data_value res[n];

		//Set every layer to tempy.
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
				it.data().GetRef().SetLayerEmpty();
		}
		offset[0]=0;
		int lay=0;
		int lay_cur;
		int off=0;
		deque<type_data_neigh *>next;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			type_data_neigh * neigh;
			if(!it.data().GetRef().GetIsLayerEmpty())
			{
				break;
			}
			next.push_back(&it.data());
			while(!next.empty())
			{
				type_data_neigh *next_neigh=next.front();
				next.pop_front();
				//For every cell in domain. Where we assign a unic number.
				if(next_neigh->GetRef().GetIsInDomain())
				{
					//Cell has no number assign one.
					if(next_neigh->GetRef().GetIsLayerEmpty())
					{
						next_neigh->GetRef().SetLayer(lay);
						lay_cur=lay;
						++lay;
					}

					//We have a number, use it.
					else
					{
						lay_cur=next_neigh->GetRef().GetLayer();
					}

					//Ordered map to store indice value relation.
					map<int,type_data_value> m_map;
					typedef typename map<int,type_data_value>::value_type type_pair;
					typedef typename map<int,type_data_value>::const_iterator const_iterator;
					type_data_value temp_diag_value=0;
					//For every direction and every sign.
					for(int i=1;i<=type_dim;++i)
					{
						for(int s=-1;s<=1;s+=2)
						{
							int lay_cur2;
							neigh=next_neigh->GetNeighbour(i,s);
							//Test if we have a neighbour.
							if(neigh!=nullptr)
							{
								//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
								if(neigh->GetRef().GetIsInDomain())
								{
									if(neigh->GetRef().GetIsLayerEmpty())
									{
										neigh->GetRef().SetLayer(lay);
										lay_cur2=lay;
										++lay;
										next.push_back(neigh);
									}
									else
									{
										lay_cur2=neigh->GetRef().GetLayer();
									}
									m_map.insert(type_pair(lay_cur2,pow(m_1_h.Get(i),2)));
									temp_diag_value-=2*pow(m_1_h.Get(i),2);
									neigh->GetRef().Pressure_Get();
								}
								// We are a von_Neumann boundary only add diagonal value.
								else if(Get_Is_Von_Neumann_Boundary(next_neigh,i,s))
								{
									temp_diag_value-=pow(m_1_h.Get(i),2);
								}
							}
						}
					}
					//Insert the diagonal value in the map.
					m_map.insert(type_pair(lay_cur,temp_diag_value));
					//Insert the value of the map. The map is ordered.
					for(const_iterator it=m_map.begin();it!=m_map.end();++it)
					{
						value[off]=it->second;
						indice[off]=it->first;
						++off;
					}
					//Add current offset.
					offset[lay_cur+1]=off;
				}
			};
		}
		n=lay;
		// Set b to divergence.
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsInDomain())
			{
				lay_cur=it.data().GetRef().GetLayer();
				b[lay_cur]=Get_Divergence(&it.data()).Get();
			}
		}
		// Solve the linear system.
		Solve_Linear(n,offset,indice,value,b,res);
		// Set the pressure of cell from the result.
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsInDomain())
			{
				lay_cur=it.data().GetRef().GetLayer();
				it.data().GetRef().Pressure_Set(type_pressure(res[lay_cur]));
			}
			else
			{
				it.data().GetRef().Pressure_Set(type_pressure(0));
			}
		}
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsInDomain())
			{
				it.data().GetRef().Speed_Set(it.data().GetRef().Speed_Get()-Get_Gradiant(&it.data()));
			}
		}

	}
};
#endif