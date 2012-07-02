#ifndef Data_Interface_Domain_Implement_Rho_H
#define Data_Interface_Domain_Implement_Rho_H

/**
 * @ingroup GR_Data_Interface_Domain_Implement_Rho
 * @ingroup GR_Traits
 * @brief
 * Trait class to send data to Data_Interface_Domain_Implement_Rho.
 *
 * @pre
 * The following type need to be defined:
 * 	- type_data_mac_cell
 * 	- type_data_neigh
 * 	- type_data_key
 * 	- type_data_rho
 * 	 
 * @tparam Implementation Implementing class
 * @tparam Base Base class to derivate with.
 **/
template <typename Implementation,typename Base>
class Data_Interface_Domain_Implement_Rho_Trait
{
};

/**
 * @ingroup GR_Data_Interface_Domain_Implement_Rho
 * @brief
 * This implementation class allow to get the density between two cell.
 * This is needed for the pressure calculation.
 *
 * @pre
 * A class trait that define input type.
 * Implementation need to define a method GetDomainRho_Impl.
 *
 * @tparam Implementation Implementing class
 * @tparam Base Base class to derivate with.
 **/
template <typename Implementation,typename Base>
class Data_Interface_Domain_Implement_Rho : public Base
{
	public:
	/**
	 * @brief
	 * Type for Mac Cell.
	 **/
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_mac_cell type_data_mac_cell;
	/**
	 * @brief
	 * Type for Neighbour.
	 **/
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_neigh type_data_neigh;
	/**
	 * @brief
	 * Type for the Key.
	 **/
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_key type_data_key;
	/**
	 * @brief
	 * Type for the density.
	 **/
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_rho type_data_rho;
	/**
	 * @brief
	 * Constructor.
	 * @param base Base class instance to copy for inheritance.
	 **/
	Data_Interface_Domain_Implement_Rho(const Base & base) :Base(base)
	{

	}
	/**
	 * @brief
	 * Get the density between this two cell.
	 * @param c1 First Mac Cell.
	 * @param c2 Second Mac Cell.
	 * @return Returned density.
	 **/
	type_data_rho GetDomainRho(const type_data_mac_cell &c1,const type_data_mac_cell &c2) const
	{
		return static_cast<const Implementation&>(*this).GetDomainRho_Impl(c1,c2);
	}
	/**
	 * @brief
	 * Get the density between this two cell.
	 * @param k1 Key to the first cell.
	 * @param k2 Key to the second cell.
	 * @return Returned density.
	 **/
	type_data_rho GetDomainRho(const type_data_key &k1,const type_data_key &k2) const
	{
		return GetDomainRho(this->at(k1).Get(),this->at(k2).Get());
	}
	/**
	 * @brief
	 * Get the density between this two cell.
	 * @param k1 Key to the cell.
	 * @param dim Direction to the second cell.
	 * @param sign Sign witch to go in the direction.
	 * @return Returned density.
	 **/
	type_data_rho GetDomainRho(const type_data_key &k1,int dim,int sign) const
	{
		type_data_neigh neigh=this->at(k1);
		type_data_neigh* neigh2=neigh.GetNeighbour(dim,sign);
		if(neigh2==nullptr)
		{
			return static_cast<const Implementation&>(*this).GetDomainRho_Bound_Impl();
		}
		return GetDomainRho(neigh.Get(),neigh2->Get());
	}
};

#endif
