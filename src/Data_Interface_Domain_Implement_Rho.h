#ifndef Data_Interface_Domain_Implement_Rho_H
#define Data_Interface_Domain_Implement_Rho_H

template <typename Implementation,typename Base>
class Data_Interface_Domain_Implement_Rho_Trait;


template <typename Implementation,typename Base>
class Data_Interface_Domain_Implement_Rho : public Base
{
	public:
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_mac_cell type_data_mac_cell;
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_neigh type_data_neigh;
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_key type_data_key;
	typedef typename Data_Interface_Domain_Implement_Rho_Trait<Implementation,Base>::type_data_rho type_data_rho;
	Data_Interface_Domain_Implement_Rho(const Base & base) :Base(base)
	{

	}
	type_data_rho GetDomainRho(const type_data_mac_cell &c1,const type_data_mac_cell &c2) const
	{
		return static_cast<const Implementation&>(*this).GetDomainRho_Impl(c1,c2);
	}
	type_data_rho GetDomainRho(const type_data_key &k1,const type_data_key &k2) const
	{
		return GetDomainRho(this->at(k1).Get(),this->at(k2).Get());
	}
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
