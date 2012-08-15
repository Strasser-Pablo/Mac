#ifndef Data_CellType_Interface_Implement_Constant_H
#define Data_CellType_Interface_Implement_Constant_H

template <typename Implementation, typename Base>
class Data_CellType_Interface_Implement_Constant_Trait;

template <typename Implementation,typename Base>
class Data_CellType_Interface_Implement_Constant : public Base
{
	public:
	typedef typename Data_CellType_Interface_Implement_Constant_Trait<Implementation,Base>::type_neigh type_neigh;
	typedef typename Data_CellType_Interface_Implement_Constant_Trait<Implementation,Base>::type_key type_key;
	Data_CellType_Interface_Implement_Constant(const Base & base) :Base(base)
	{

	}
	bool GetIsConstantInterface(const type_key &k1,int dim,int sign)
	{
		return static_cast<const Implementation&>(*this).GetIsConstantInterface_Impl(k1,dim,sign);
	}
	bool GetIsConstantInterface(const type_neigh &neigh,int dim,int sign)
	{
		return static_cast<const Implementation&>(*this).GetIsConstantInterface_Impl(neigh,dim,sign);
	}
};

#endif
