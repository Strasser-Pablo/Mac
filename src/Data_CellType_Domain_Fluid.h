#ifndef Data_CellType_Domain_Fluid_H
#define Data_CellType_Domain_Fluid_H
#include "Data_CellType_Domain_Implement.h"

template <typename Base>
class Data_CellType_Domain_Fluid;

template<typename Base>
class Data_CellType_Domain_Implement_Trait<Data_CellType_Domain_Fluid<Base>,Base>
{
	public:
	typedef typename Base::Material_Type Material_Type;
};


template <typename Base>
class Data_CellType_Domain_Fluid__InCell;

template <typename Base>
class Data_CellType_Domain_Fluid : public Data_CellType_Domain_Implement<Data_CellType_Domain_Fluid<Base>,Base>
{
	public:
	typedef typename Base::Material_Type Material_Type;
	Data_CellType_Domain_Fluid(const Base& base):Data_CellType_Domain_Implement<Data_CellType_Domain_Fluid<Base>,Base>(base)
	{
	}
	bool GetIsInDomain_Impl(const Material_Type mat) const
	{
		return Base::GetIsFluid(mat);
	}
		typedef Data_CellType_Domain_Fluid__InCell<Base> type_Cell_type__InCell;
		typedef void type_Cell_type__InCell_exist;
};


template <typename Base>
class Data_CellType_Domain_Implement_Trait<Data_CellType_Domain_Fluid__InCell<Base>,Base>
{
	public:
	typedef typename Base::Material_Type Material_Type;
};
template <typename Base>
class Data_CellType_Domain_Fluid__InCell : public Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base >
{
	typedef Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base > RealBase;
	public:
	typedef typename Base::Material_Type Material_Type;
	Data_CellType_Domain_Fluid__InCell(const Data_CellType_Domain_Fluid<Base>& data) : m_data_cell_type(data),Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base >(static_cast<const Base&>(data))
	{
	}
	bool GetIsInDomain_Impl() const
	{
		return RealBase::GetIsFluid();
	}
	const Data_CellType_Domain_Fluid<Base> & m_data_cell_type;
};

#endif
