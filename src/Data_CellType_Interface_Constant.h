#ifndef Data_CellType_Interface_Constant_H
#define Data_CellType_Interface_Constant_H

#include "Data_CellType_Interface_Implement_Constant.h"
#include "Data_Staggered_Left.h"
template <class Base>
class Data_CellType_Interface_Constant;

template <typename Base>
class Data_CellType_Interface_Implement_Constant_Trait<Data_CellType_Interface_Constant<Base>,Base>
{
	public:
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	typedef typename Base::type_data_neigh type_data_neigh;
	typedef typename Base::type_data_key type_data_key;
};

template <class Base>
class Data_CellType_Interface_Constant : public Data_CellType_Interface_Implement_Constant<Data_CellType_Interface_Constant<Base>,Base>
{
	public:
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	typedef typename Base::type_data_neigh type_data_neigh;
	typedef typename Base::type_data_key type_data_key;
	Data_CellType_Interface_Constant(const Base & base) : Data_CellType_Interface_Implement_Constant<Data_CellType_Interface_Constant<Base>,Base>(base)
	{
	}

	template <class T_INT, typename Is_Staggered_Left_SFINAE<T_INT,Base,int>::type =0>
	bool GetIsConstantInterface_Impl(const type_data_key &k1,T_INT dim,T_INT sign) const
	{
		type_data_neigh neigh=this->at(k1);
		type_data_neigh* neigh2=neigh.GetNeighbour(dim,sign);
		if(neigh2==nullptr)
		{
			return false;
		}
		if(sign==1)
		{
			return neigh2->Get().Speed_Get_Const(dim);
		}
		else
		{
			return neigh.Get().Speed_Get_Const(dim);
		}
	}
	template <class T_INT, typename Is_Staggered_Left_SFINAE<T_INT,Base,int>::type =0>
	bool GetIsConstantInterface_Impl(const type_data_neigh &neigh,T_INT dim,T_INT sign) const
	{
		type_data_neigh* neigh2=neigh.GetNeighbour(dim,sign);
		if(neigh2==nullptr)
		{
			return false;
		}
		if(sign==1)
		{
			return neigh2->Get().Speed_Get_Const(dim);
		}
		else
		{
			return neigh.Get().Speed_Get_Const(dim);
		}
	}
};

#endif
