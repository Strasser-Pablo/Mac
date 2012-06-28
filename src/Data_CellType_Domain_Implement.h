#ifndef Data_CellType_Domain_Implement_H
#define Data_CellType_Domain_Implement_H
#include "Data_CellType_SFINAE.h"
template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement_Trait;

template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement : public Base
{
	typedef typename Data_CellType_Domain_Implement_Trait<Implementation,Base>::Material_Type Material_Type;
	public:
	bool GetIsInDomain(const Material_Type mat) const
	{
		return static_cast<const Implementation&> (*this).GetIsInDomain_Impl(mat);
	}
	Data_CellType_Domain_Implement(const Base & base): Base(base)
	{
	}
};


template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement__InCell : public Data_CellType_Derivate_SFINAE<Base>
{
	typedef typename Data_CellType_Domain_Implement_Trait<Implementation,Base>::Material_Type Material_Type;
	public:
	bool GetIsInDomain() const
	{
		return static_cast<const Implementation&> (*this).GetIsInDomain_Impl();
	}

	template<typename T,typename Data_CellType_Constructor_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Domain_Implement__InCell(const T & base): Data_CellType_Derivate_SFINAE<Base>(base)
	{
	}
	template<typename T,typename Data_CellType_Constructor_Not_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Domain_Implement__InCell(const T & base) 
	{
	}
};
#endif
