#ifndef Data_Interface_Domain_Rho_Fluid_H
#define Data_Interface_Domain_Rho_Fluid_H
#include "Data_Interface_Domain_Implement_Rho.h"

template <typename Base>
class Data_Interface_Domain_Rho_Fluid;

/**
 * @ingroup GR_Data_Interface_Domain_Implement_Rho
 * @ingroup GR_Traits
 * @brief
 * Trait class to send data to Data_Interface_Domain_Implement_Rho.
 * This is a specialization for Data_Interface_Domain_Rho_Fluid.
 * 	 
 * @tparam Base Base class to derivate with.
 **/
template <typename Base>
class Data_Interface_Domain_Implement_Rho_Trait<Data_Interface_Domain_Rho_Fluid<Base>,Base>
{
	public:
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	typedef typename Base::type_data_neigh type_data_neigh;
	typedef typename Base::type_data_key type_data_key;
	typedef typename type_data_mac_cell::type_data_rho type_data_rho;
};

/**
 * @ingroup GR_Data_Interface_Domain_Rho_Fluid
 * @brief
 * Class that implement the calculation of rho for intercell Rho. In this class the rho value is fluid rho if one of the cell is fluid
 * and air rho otherwise.
 * This class is used for pressure.
 *
 * @pre
 * Base need to define the following type:
 * 	- type_data_mac_cell
 * 	- type_data_neigh
 * 	- type_data_key
 * 	- type_data_mac_cell::type_data_rho
 *
 * @tparam Base base class to derivate with.
 **/
template <typename Base>
class Data_Interface_Domain_Rho_Fluid : public Data_Interface_Domain_Implement_Rho<Data_Interface_Domain_Rho_Fluid<Base>,Base>
{
	public: 
	/**
	 * @brief
	 * Type for Mac  Cell.
	 **/
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	/**
	 * @brief
	 * Type for Mac  Cell.
	 **/
	typedef typename Base::type_data_neigh type_data_neigh;
	/**
	 * @brief
	 * Type for the key.
	 **/
	typedef typename Base::type_data_key type_data_key;
	/**
	 * @brief
	 * Type for Density.
	 **/
	typedef typename type_data_mac_cell::type_data_rho type_data_rho;
	/**
	 * @brief
	 * Constructor.
	 * @param data Base class to copy for inheriting.
	 **/
	Data_Interface_Domain_Rho_Fluid(const Base &data ) : Data_Interface_Domain_Implement_Rho<Data_Interface_Domain_Rho_Fluid<Base>,Base>(data)
	{
	}
	/**
	 * @brief
	 * Function that will be called to get the density.
	 * @param mac1 First Cell.
	 * @param mac2 Second cell.
	 * @return Returned density.
	 **/
	type_data_rho GetDomainRho_Impl(const type_data_mac_cell& mac1,const type_data_mac_cell & mac2) const
	{
		if(mac1.GetIsInDomain()||mac2.GetIsInDomain())
		{
			return mac1.GetRhoFluid();
		}
		else
		{
			return mac1.GetRhoAir();
		}
	}
	/**
	 * @brief
	 * Function called to get the density if one of the cell does not exist.
	 * @return Density returned.
	 **/
	type_data_rho GetDomainRho_Bound_Impl() const
	{
		return this->Get().GetRhoFluid();
	}
};

#endif
