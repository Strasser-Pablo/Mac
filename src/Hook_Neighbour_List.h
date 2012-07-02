#ifndef Hook_Neighbour_List_H
#define Hook_Neighbour_List_H

/**
 * @ingroup GR_Data_Storage
 * @brief
 * Hook for Hookable_Hash_Table. To Work with data using a Neighbour_List.
 *
 * This class will assure that the neighbour list is always correct with the Hash_Table.
 * @pre
 * HashTable need to be a Hookable_Hash_Table Storing a Neighbour_List or similar interface.
 *
 * @tparam HashTable hash table.
 **/
template<class HashTable>
class Hook_Neighbour_List
{
	public:
	/**
	 * @brief
	 * Pointer to the Hash Table Instance.
	 **/
	HashTable * m_hashtable;
	/**
	 * @brief
	 * type of Key of the Hash Table.
	 **/
	typedef typename HashTable::type_key type_key;
	/**
	 * @brief
	 * type of Data of the Hash Table
	 **/
	typedef typename HashTable::type_data type_data;
	/**
	 * @brief
	 * Dimension of the Hash Table.
	 **/
	static const int type_dim=HashTable::type_key::type_dim;
	/**
	 * @brief
	 * Hook called when we insert a value in the hash table.
	 * We need to see if one of the neighbour exist.
	 * If it's the case we update the neighbour.
	 * @param in A pair of iterator and boolean. The boolean indicate if an element was inserted.
	 **/
	void insert(const pair<typename HashTable::iterator,bool>&  in)
	{
		// Ok we don't insert anything. Return.
		if(!in.second)
		{
			return;
		}
		// Loop with all neighbour see if it exist. And add in the Neighbour.
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
	/**
	 * @brief
	 * Hook called when we erase a value.
	 * Wee need to update neighbour and set there pointer to nullptr.
	 * @param it Iterator to the element that will be erased.
	 **/
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
	/**
	 * @brief
	 * Hook called when we erase a value.
	 * Wee need to update neighbour and set there pointer to nullptr.
	 * @param k Value of the key of the element that will be erased.
	 **/
	void erase(const type_key &k)
	{
		type_data& data=(*m_hashtable)[k];
		for(int i=1;i<=type_dim;++i)
		{
			type_data *neigh=data.GetNeighbour(i,-1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,1,nullptr);
				data.SetNeighbour(i,-1,nullptr);
			}
			neigh=data.GetNeighbour(i,1);
			if(neigh!=nullptr)
			{
				neigh->SetNeighbour(i,-1,nullptr);
				data.SetNeighbour(i,1,nullptr);
			}
		}
	}
	/**
	 * @brief
	 * Hook called when we acess directly a value by [].
	 * Wee need to check neighbour and update ther pointer.
	 * @param key value of the key that will be added.
	 * @param data That will be added.
	 **/
	void directacess(const type_key & key,type_data & data)
	{
		type_key k=key;
		for(int i=1;i<=type_dim;++i)
		{
				// We look at the position below
				k.GetRef(i)-=1;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,-1,&((*m_hashtable)[k]));
					(*m_hashtable)[k].SetNeighbour(i,1,&data);
				}
				// We look at the position above (-1+2=1)
				k.GetRef(i)+=2;
				if(m_hashtable->Exist(k))
				{
					data.SetNeighbour(i,1,&((*m_hashtable)[k]));
					(*m_hashtable)[k].SetNeighbour(i,-1,&data);
				}
				// We are at same point (-1+2-1=0)
				k.GetRef(i)-=1;
		}
	}
	/**
	 * @brief
	 * Constructor.
	 * @param hash Table linked to this Hook
	 **/
	Hook_Neighbour_List(HashTable * hash) : m_hashtable(hash)
	{
	}
};
#endif
