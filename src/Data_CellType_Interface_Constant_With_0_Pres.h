#ifndef Data_CellType_Interface_Constant_With_0_Pres_H
#define Data_CellType_Interface_Constant_With_0_Pres_H

#include "Data_CellType_Interface_Implement_Constant.h"
#include "Data_Staggered_Left.h"
#include <unordered_set>
#include <functional>

using std::unordered_set;

template <class Base>
class Data_CellType_Interface_Constant_With_0_Pres;

template <typename Base>
class Data_CellType_Interface_Implement_Constant_Trait<Data_CellType_Interface_Constant_With_0_Pres<Base>,Base>
{
	public:
	typedef typename Base::type_offset type_neigh;
	typedef typename Base::type_key type_key;
};

template <class Base>
class Data_CellType_Interface_Constant_With_0_Pres : public Data_CellType_Interface_Implement_Constant<Data_CellType_Interface_Constant_With_0_Pres<Base>,Base>
{
	public:
	typedef typename Base::type_offset type_neigh;
	typedef typename Base::type_key type_key;
	private:
	typedef std::function<size_t(type_neigh)> type_priv_hash;
	type_priv_hash m_hash;
	unordered_set<type_neigh,type_priv_hash> m_set;
	static size_t hash(type_neigh neigh)
	{
		return reinterpret_cast<size_t>(neigh.GetBase());
	}
	public:
	Data_CellType_Interface_Constant_With_0_Pres(const Base & base) : Data_CellType_Interface_Implement_Constant<Data_CellType_Interface_Constant_With_0_Pres<Base>,Base>(base),m_hash(Data_CellType_Interface_Constant_With_0_Pres<Base>::hash),m_set(10,m_hash)
	{
	}

	template <class T_INT, typename Is_Staggered_Left_SFINAE<T_INT,Base,int>::type =0>
	bool GetIsConstantInterface_Impl(const type_key &k1,T_INT dim,T_INT sign)
	{
		type_neigh neigh=(*this)[k1];
		type_neigh neigh2=neigh.GetNeighbour(dim,sign);
		if(!neigh2.IsValid())
		{
			return false;
		}
		if(m_set.count(neigh)==1||m_set.count(neigh2))
		{
			return false;
		}
		if(sign==1)
		{
			return neigh2.GetRef_Speed().Get_Const(dim);
		}
		else
		{
			return neigh.GetRef_Speed().Get_Const(dim);
		}
	}
	template <class T_INT, typename Is_Staggered_Left_SFINAE<T_INT,Base,int>::type =0>
	bool GetIsConstantInterface_Impl(const type_neigh &neigh,T_INT dim,T_INT sign) const
	{
		type_neigh neigh2=neigh.GetNeighbour(dim,sign);
		if(!neigh2.IsValid())
		{
			return false;
		}
		if(m_set.count(neigh)==1||m_set.count(neigh2))
		{
			return false;
		}
		if(sign==1)
		{
			return neigh2.Speed_GetRef().Get_Const(dim);
		}
		else
		{
			return neigh.Speed_GetRef().Get_Const(dim);
		}
	}
	void Add_0_Pres(const type_neigh &neigh)
	{
		m_set.insert(neigh);
	}
	void Add_0_Pres(const type_key &key)
	{
		type_neigh neigh=(*this)[key];
		m_set.insert(neigh);
	}
};

#endif
