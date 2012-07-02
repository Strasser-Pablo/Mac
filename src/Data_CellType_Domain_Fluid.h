#ifndef Data_CellType_Domain_Fluid_H
#define Data_CellType_Domain_Fluid_H
#include "Data_CellType_Domain_Implement.h"

template <typename Base>
class Data_CellType_Domain_Fluid;

/**
 * @ingroup GR_Data_CellType_Domain_Implement
 * @ingroup GR_Traits
 * @brief
 * Trait class to send data for Data_CellType_Domain_Implement.
 * This specialisation is for Data_CellType_Domain_Fluid.
 * @tparam Base base class.
 **/
template<typename Base>
class Data_CellType_Domain_Implement_Trait<Data_CellType_Domain_Fluid<Base>,Base>
{
	public:
	typedef typename Base::Material_Type Material_Type;
};


template <typename Base>
class Data_CellType_Domain_Fluid__InCell;

/**
 * @ingroup GR_DataCellType_Domain_Fluid
 * @brief
 * This class give the method `GetIsInDomain` witch is to be used in the pressure solver.
 * In this class we are in Domaine if we are fluid.
 *
 * @pre
 * Base need to define `Base::GetIsFluid` and `Base::Material_Type`.
 *
 * @tparam Base base class to derivate with that need to respect the above condition.
 **/
template <typename Base>
class Data_CellType_Domain_Fluid : public Data_CellType_Domain_Implement<Data_CellType_Domain_Fluid<Base>,Base>
{
	public:
	/**
	 * @brief
	 * Type of Material.
	 **/
	typedef typename Base::Material_Type Material_Type;
	/**
	 * @brief
	 * constructor.
	 * @param base Instance of base to copy.
	 **/
	Data_CellType_Domain_Fluid(const Base& base):Data_CellType_Domain_Implement<Data_CellType_Domain_Fluid<Base>,Base>(base)
	{
	}
	/**
	 * @brief
	 * Method that will be called by child class that implement if we are at domain or not.
	 **/
	bool GetIsInDomain_Impl(const Material_Type mat) const
	{
		return Base::GetIsFluid(mat);
	}
	/**
	 * @brief
	 * Type that will be in cell.
	 **/
	typedef Data_CellType_Domain_Fluid__InCell<Base> type_Cell_type__InCell;
	/**
	 * @brief
	 * Indicate for SFINAE that this type exist.
	 **/
	typedef void type_Cell_type__InCell_exist;
};


template <typename Base>
class Data_CellType_Domain_Implement_Trait<Data_CellType_Domain_Fluid__InCell<Base>,Base>
{
	public:
	typedef typename Base::Material_Type Material_Type;
};

/**
 * @ingroup GR_DataCellType_Domain_Fluid
 * @brief
 * This class give the method `GetIsInDomain` witch is to be used in the pressure solver.
 * This class is to be stored in cell.
 *
 * Note that this class will automaticaly transform to InCell it's Base.
 *
 * @pre
 * Base need to define `Base::GetIsFluid` and `Base::Material_Type`.
 * Base need to have the mecanism of InCell because of use of SFINAE technic.
 *
 * @tparam Base base class to derivate with that need to respect the above condition.
 **/
template <typename Base>
class Data_CellType_Domain_Fluid__InCell : public Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base >
{
	/**
	 * @brief
	 * Type that we will derivate with.
	 **/
	typedef Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base > RealBase;
	public:
	/**
	 * @brief
	 * Type of Material.
	 **/
	typedef typename Base::Material_Type Material_Type;
	/**
	 * @brief
	 * Constructor.
	 * This Constructor will created an InCell type.
	 * Note that it will correctly Handle InCell sub class.
	 * @param data Data to transform.
	 **/
	Data_CellType_Domain_Fluid__InCell(const Data_CellType_Domain_Fluid<Base>& data) : Data_CellType_Domain_Implement__InCell<Data_CellType_Domain_Fluid__InCell<Base>, Base >(static_cast<const Base&>(data)),m_data_cell_type(data)
	{
	}
	/**
	 * @brief
	 * Return if current cell is in Domain.
	 * In this case returne if it's fluid.
	 **/
	bool GetIsInDomain_Impl() const
	{
		return RealBase::GetIsFluid();
	}
	/**
	 * @brief
	 * Reference to the not InCell case.
	 **/
	const Data_CellType_Domain_Fluid<Base> & m_data_cell_type;
};

#endif
