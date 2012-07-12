#ifndef Algorithms_Extrapolate_H
#define Algorithms_Extrapolate_H

#include <unordered_set>

using namespace std;

template <typename Data,typename Policy>
class Algorithms_Extrapolate : public Policy
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::iterator iterator;
	typedef typename type_grid::type_data_value type_data_value;
	typedef typename type_grid::type_data_neigh type_data_neigh;
	static const int type_dim=type_grid::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Extrapolate(Data data, const Policy& pol): m_grid(data.m_data.GetGridData()), Policy(pol)
	{
	}
	void Do()
	{
		unordered_set<type_data_neigh *> m_set;
		unordered_set<type_data_neigh *> m_set2;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetLayer()==1)
			{
				m_set.insert(&it.data());
			}
		}
		int lay=1;
		while(true)
		{
			typename unordered_set<type_data_neigh *>::iterator it=m_set.begin();
			while(it!=m_set.end())
			{
				type_data_neigh* neigh=*it;
				m_set.erase(it++);
				for(int i=1;i<=type_dim;++i)
				{
					type_data_neigh* neigh2=neigh->GetNeighbour(i,1);
					if(neigh2!=nullptr)
					{
						if(neigh2->GetRef().GetLayer()>=lay)
						{
							if(neigh2->GetRef().GetLayer()>lay)
							{
								m_set2.insert(neigh2);
							}
							int n=0;
							type_data_value val=0;
							for(int j=1;j<=type_dim;++j)
							{
								for(int s2=-1;s2<=1;s2+=2)
								{
									if(s2==-1&&j==i)
									{
										type_data_neigh* neigh3=neigh->GetNeighbour(i,-1);
										if(neigh3!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh->GetRef().Speed_Get(i);
											}
										}
									}
									else if(s2==1&&j==i)
									{
										type_data_neigh* neigh3=neigh2->GetNeighbour(i,1);
										if(neigh3!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3->GetRef().Speed_Get(i);
											}
										}
									}
									else
									{
										type_data_neigh* neigh3=neigh2->GetNeighbour(j,s2);
										type_data_neigh* neigh4=neigh->GetNeighbour(j,s2);
										if(neigh3!=nullptr&&neigh4!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay||neigh4->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3->GetRef().Speed_Get(i);
											}
										}
									}
								}
							}
							neigh2->GetRef().Speed_Set(i,val/n);
						}
					}
					neigh2=neigh->GetNeighbour(i,-1);
					if(neigh2!=nullptr)
					{
						if(neigh2->GetRef().GetLayer()>=lay)
						{
							if(neigh2->GetRef().GetLayer()>lay)
							{
								m_set2.insert(neigh2);
							}
							int n=0;
							type_data_value val=0;
							for(int j=1;j<=type_dim;++j)
							{
								for(int s2=-1;s2<=1;s2+=2)
								{
									if(s2==1&&j==i)
									{
										type_data_neigh* neigh3=neigh->GetNeighbour(j,1);
										if(neigh3!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh3->GetRef().Speed_Get(j);
											}
										}
									}
									else if(s2==-1&&j==i)
									{
										type_data_neigh* neigh3=neigh2->GetNeighbour(j,-1);
										if(neigh3!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh2->GetRef().Speed_Get(j);
											}
										}
									}
									else
									{
										type_data_neigh* neigh3=neigh2->GetNeighbour(j,s2);
										type_data_neigh* neigh4=neigh->GetNeighbour(j,s2);
										if(neigh3!=nullptr&&neigh4!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay||neigh4->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh4->GetRef().Speed_Get(i);
											}
										}
									}
								}
							}
							neigh->GetRef().Speed_Set(i,val/n);
						}
					}
					else
					{
						int n=0;
						type_data_value val=0;
						for(int j=1;j<=type_dim;++j)
						{
							for(int s2=-1;s2<=1;s2+=2)
							{
								if(s2==1&&j==i)
								{
									type_data_neigh* neigh3=neigh->GetNeighbour(j,1);
									if(neigh3!=nullptr)
									{
										if(neigh3->GetRef().GetLayer()<lay)
										{
											++n;
											val+=neigh3->GetRef().Speed_Get(j);
										}
									}
								}
								else if(s2==-1&&j==i)
								{
								}
								else
								{
									type_data_neigh* neigh4=neigh->GetNeighbour(j,s2);
									if(neigh4!=nullptr)
									{
										type_data_neigh* neigh3=neigh4->GetNeighbour(i,-1);
										if(neigh3!=nullptr)
										{
											if(neigh3->GetRef().GetLayer()<lay||neigh4->GetRef().GetLayer()<lay)
											{
												++n;
												val+=neigh4->GetRef().Speed_Get(i);
											}
										}
									}
								}
							}
						}
						neigh->GetRef().Speed_Set(i,val/n);
					}
				}
			}
			m_set2.swap(m_set);
			++lay;
			if(m_set.empty())
			{
				break;
			}
		}
	}
};

#endif
