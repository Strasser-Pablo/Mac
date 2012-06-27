#ifndef Data_Interface_Fluid_Air_H
#define Data_Interface_Fluid_Air_H

template<typename DataBase>
class Data_Interface_Fluid_Air : public DataBase
{
	public: 
	typedef typename DataBase::type_data_mac_cell type_data_mac_cell;
	typedef typename DataBase::type_data_neigh type_data_neigh;
	typedef typename DataBase::type_data_key type_data_key;
	bool GetIsFluidAirInterface(const type_data_mac_cell &c1,const type_data_mac_cell &c2)
	{
		return (c1.GetIsFluid()&&c2.GetIsAir())||(c2.GetIsFluid()&&c2.GetIsAir());		
	}
	bool GetIsFluidAirInterface(const type_data_key &k1,const type_data_key &k2)
	{
		return GetIsFluidAirInterface((*this)[k1].Get(),(*this)[k2].Get());
	}
	bool GetIsFluidAirInterface(const type_data_key &k1,int dim,int sign)
	{
		type_data_neigh neigh=(*this)[k1];
		type_data_neigh* neigh2=neigh.GetNeighbour(dim,sign);
		if(neigh2==nullptr)
		{
			return false;
		}
		return GetIsFluidAirInterface(neigh.Get(),neigh2->Get());
	}
	Data_Interface_Fluid_Air(const DataBase &data ) : DataBase(data)
	{
	}
};

#endif
