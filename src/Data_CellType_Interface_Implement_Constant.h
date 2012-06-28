#ifndef Data_CellType_Interface_Implement_Constant_H
#define Data_CellType_Interface_Implement_Constant_H

template <typename Implementation, typename Base>
class Data_CellType_Interface_Implement_Constant_Trait;

template <typename Implementation,typename Base>
class Data_CellType_Interface_Implement_Constant : public Base
{
	public:
	typedef typename Data_CellType_Interface_Implement_Constant_Trait<Implementation,Base>::type_data_mac_cell type_data_mac_cell;
	typedef typename Data_CellType_Interface_Implement_Constant_Trait<Implementation,Base>::type_data_neigh type_data_neigh;
	typedef typename Data_CellType_Interface_Implement_Constant_Trait<Implementation,Base>::type_data_key type_data_key;
	Data_CellType_Interface_Implement_Constant(const Base & base) :Base(base)
	{

	}
	bool GetIsConstantInterface(const type_data_key &k1,int dim,int sign)
	{
		return static_cast<const Implementation&>(*this).GeIsConstantInterface_Impl(k1,dim,sign);
	}
};

#endif
