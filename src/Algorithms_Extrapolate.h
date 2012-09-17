#ifndef Algorithms_Extrapolate_H
#define Algorithms_Extrapolate_H

#include <unordered_set>
#include <functional>
#include <sys/times.h>

using namespace std;

template <typename Data,typename Policy>
class Algorithms_Extrapolate : public Policy
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_data_value;
	typedef typename type_Data_Grid::iterator iterator;
	typedef typename type_Data_Grid::type_offset type_neigh;
	static const int type_dim=type_Data_Grid::type_key::type_dim;
	type_Data_Grid& m_grid;
	public:
	Algorithms_Extrapolate(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		typedef std::function<size_t(type_neigh)> type_hash;
		type_hash f=[](type_neigh neigh)
		{
			return reinterpret_cast<size_t>(neigh.GetBase());
		};
		unordered_set<type_neigh,type_hash> m_set(10,f);
		unordered_set<type_neigh,type_hash> m_set2(10,f);
		//We add all cell with layer 1.
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().Layer_GetRef().GetLayer()==1)
			{
				m_set.insert(it.data());
			}
		}
		int lay=1;
		while(true)
		{
			typename unordered_set<type_neigh,type_hash >::iterator it=m_set.begin();
			while(it!=m_set.end())
			{
				type_neigh neigh=*it;
				m_set.erase(it++);
				for(int i=1;i<=type_dim;++i)
				{
					//we look +1 direction on speed.
					type_neigh neigh2=neigh.GetNeighbour(i,1);
					if(neigh2.IsValid()&&!(neigh2.Layer_GetRef().GetIsLayerEmpty()))
					{
						//Ok +1 direction on speed exist and not ignored.
						if(neigh2.Layer_GetRef().GetLayer()>=lay)
						{
							//Ok we are between two cell and one with a smaller layer.
							if(neigh2.Layer_GetRef().GetLayer()>lay)
							{
								//Ok we have found a next cell layer. Add to the list.
								m_set2.insert(neigh2);
							}
							int n=0;
							type_speed_data_value val=0;
							for(int j=1;j<=type_dim;++j)
							{
								for(int s2=-1;s2<=1;s2+=2)
								{
									if(s2==-1&&j==i)
									{
										type_neigh neigh3=neigh.GetNeighbour(i,-1);
										if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh.Speed_GetRef().Get(i);
											}
										}
									}
									else if(s2==1&&j==i)
									{
										type_neigh neigh3=neigh2.GetNeighbour(i,1);
										if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3.Speed_GetRef().Get(i);
											}
										}
									}
									else
									{
										type_neigh neigh3=neigh2.GetNeighbour(j,s2);
										type_neigh neigh4=neigh.GetNeighbour(j,s2);
										if(neigh3.IsValid()&&neigh4.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty())&&(!neigh4.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay||neigh4.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3.Speed_GetRef().Get(i);
											}
										}
									}
								}
							}
							neigh2.Speed_GetRef().Set(i,val/n);
						}
					}
					//we look -1 direction on speed.
					neigh2=neigh.GetNeighbour(i,-1);
					if(neigh2.IsValid()&&!(neigh2.Layer_GetRef().GetIsLayerEmpty()))
					{
						//Ok -1 direction on speed exist and not ignored.
						if(neigh2.Layer_GetRef().GetLayer()>=lay)
						{
							//Ok we are between two cell and one with a smaller layer.
							if(neigh2.Layer_GetRef().GetLayer()>lay)
							{
								//Ok we have found a next cell layer. Add to the list.
								m_set2.insert(neigh2);
							}
							int n=0;
							type_speed_data_value val=0;
							for(int j=1;j<=type_dim;++j)
							{
								for(int s2=-1;s2<=1;s2+=2)
								{
									if(s2==1&&j==i)
									{
										type_neigh neigh3=neigh.GetNeighbour(j,1);
										if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3.Speed_GetRef().Get(j);
											}
										}
									}
									else if(s2==-1&&j==i)
									{
										type_neigh neigh3=neigh2.GetNeighbour(j,-1);
										if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh2.Speed_GetRef().Get(j);
											}
										}
									}
									else
									{
										type_neigh neigh3=neigh2.GetNeighbour(j,s2);
										type_neigh neigh4=neigh.GetNeighbour(j,s2);
										if(neigh3.IsValid()&&neigh4.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty())&&(!neigh4.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay||neigh4.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh4.Speed_GetRef().Get(i);
											}
										}
									}
								}
							}
							neigh.Speed_GetRef().Set(i,val/n);
						}
					}
					else
					{
						int n=0;
						type_speed_data_value val=0;
						for(int j=1;j<=type_dim;++j)
						{
							for(int s2=-1;s2<=1;s2+=2)
							{
								if(s2==1&&j==i)
								{
									type_neigh neigh3=neigh.GetNeighbour(j,1);
									if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
									{
										if(neigh3.Layer_GetRef().GetLayer()<lay)
										{
											++n;
											val+=neigh3.Speed_GetRef().Get(j);
										}
									}
								}
								else if(s2==-1&&j==i)
								{
								}
								else
								{
									type_neigh neigh4=neigh.GetNeighbour(j,s2);
									if(neigh4.IsValid()&&(!neigh4.Layer_GetRef().GetIsLayerEmpty()))
									{
										type_neigh neigh3=neigh4.GetNeighbour(i,-1);
										if(neigh3.IsValid()&&(!neigh3.Layer_GetRef().GetIsLayerEmpty()))
										{
											if(neigh3.Layer_GetRef().GetLayer()<lay||neigh4.Layer_GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh4.Speed_GetRef().Get(i);
											}
										}
									}
								}
							}
						}
						neigh.Speed_GetRef().Set(i,val/n);
					}
				}
			}
			//Swap new set with the old empty one.
			m_set2.swap(m_set);
			++lay;
			//new set is empty. It's a finishing case.
			if(m_set.empty())
			{
				break;
			}
		}
		long t_end=times(&t2);
		cout<<"real extrapolate "<<(t_end-t_deb)/conv<<endl;
		cout<<"user extrapolate "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
