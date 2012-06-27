#ifndef Hook_Neighbour_List_H
#define Hook_Neighbour_List_H

template<class HashTable>
class Hook_Neighbour_List
{
	public:
	HashTable * m_hashtable;
	typedef typename HashTable::type_key type_key;
	typedef typename HashTable::type_data type_data;
	static const int type_dim=HashTable::type_key::type_dim;
	void insert(const pair<typename HashTable::iterator,bool>&  in)
	{
		if(!in.second)
		{
			return;
		}
		type_key k=in.first.key();
		type_data & data=(*m_hashtable)[k];
		for(int i=1;i<=type_dim;++i)
		{
				k.GetRef(i)-=1;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,-1,&(*m_hashtable)[k]);
					(*m_hashtable)[k].SetNeighbour(i,1,&data);
				}
				k.GetRef(i)+=2;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,1,&(*m_hashtable)[k]);
					(*m_hashtable)[k].SetNeighbour(i,-1,&data);
				}
				k.GetRef(i)-=1;
		}
	}
	void erase(typename HashTable::iterator it)
	{
		for(int i=1;i<=type_dim;++i)
		{
			type_data *neigh=it.data().GetNeighbour(i,-1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,1,nullptr);
				it.data().SetNeighbour(i,-1,nullptr);
			}
			neigh=it.data().GetNeighbour(i,1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,-1,nullptr);
				it.data().SetNeighbour(i,1,nullptr);
			}
		}
	}
	void erase(const type_key &k)
	{
		for(int i=1;i<=type_dim;++i)
		{
			type_data *neigh=(*m_hashtable)[k].GetNeighbour(i,-1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,1,nullptr);
				(*m_hashtable)[k].SetNeighbour(i,-1,nullptr);
			}
			neigh=(*m_hashtable)[k].GetNeighbour(i,1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,-1,nullptr);
				(*m_hashtable)[k].SetNeighbour(i,1,nullptr);
			}
		}
	}
	void directacess(const type_key & key,type_data & data)
	{
		type_key k=key;
		for(int i=1;i<=type_dim;++i)
		{
				k.GetRef(i)-=1;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,-1,&((*m_hashtable)[k]));
					(*m_hashtable)[k].SetNeighbour(i,1,&data);
				}
				k.GetRef(i)+=2;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,1,&((*m_hashtable)[k]));
					(*m_hashtable)[k].SetNeighbour(i,-1,&data);
				}
				k.GetRef(i)-=1;
		}
	}
	Hook_Neighbour_List(HashTable * hash) : m_hashtable(hash)
	{
	}
};
#endif
