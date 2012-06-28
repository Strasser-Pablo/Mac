#ifndef Data_Interface_Domain_Rho_Fluid_H
#define Data_Interface_Domain_Rho_Fluid_H
#include "Data_Interface_Domain_Implement_Rho.h"

template <typename Base>
class Data_Interface_Domain_Rho_Fluid;

template <typename Base>
class Data_Interface_Domain_Implement_Rho_Trait<Data_Interface_Domain_Rho_Fluid<Base>,Base>
{
	public:
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	typedef typename Base::type_data_neigh type_data_neigh;
	typedef typename Base::type_data_key type_data_key;
	typedef typename type_data_mac_cell::type_data_rho type_data_rho;
};

template <typename Base>
class Data_Interface_Domain_Rho_Fluid : public Data_Interface_Domain_Implement_Rho<Data_Interface_Domain_Rho_Fluid<Base>,Base>
{
	public: 
	typedef typename Base::type_data_mac_cell type_data_mac_cell;
	typedef typename Base::type_data_neigh type_data_neigh;
	typedef typename Base::type_data_key type_data_key;
	typedef typename type_data_mac_cell::type_data_rho type_data_rho;
	Data_Interface_Domain_Rho_Fluid(const Base &data ) : Data_Interface_Domain_Implement_Rho<Data_Interface_Domain_Rho_Fluid<Base>,Base>(data)
	{
	}
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
	type_data_rho GetDomainRho_Bound_Impl() const
	{
		return this->Get().GetRhoFluid();
	}
};

#endif
