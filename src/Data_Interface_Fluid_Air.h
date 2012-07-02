#ifndef Data_Interface_Fluid_Air_H
#define Data_Interface_Fluid_Air_H

/**
 * @ingroup GR_Data_Interface_Fluid_Air
 * @brief
 * Class that will return if it's an interface between an air cell and a fluid cell.
 *
 * @pre
 * DataBase need to define the following type:
 * 	- type_data_mac_cell
 * 	- type_data_neigh
 * 	- type_data_key
 * 
 * @tparam DataBase Base class to derive from.
 **/
template<typename DataBase>
class Data_Interface_Fluid_Air : public DataBase
{
	public: 
	/**
	 * @brief
	 * Type for the MacCell.
	 **/
	typedef typename DataBase::type_data_mac_cell type_data_mac_cell;
	/**
	 * @brief
	 * Type for the Neighbour.
	 **/
	typedef typename DataBase::type_data_neigh type_data_neigh;
	/**
	 * @brief
	 * Type for the Key.
	 **/
	typedef typename DataBase::type_data_key type_data_key;
	/**
	 * @brief
	 * Get if it's an interface between air and fluid (that one of the two cell is air and the oher fluid).
	 * @param c1 MacCell 1.
	 * @param c2 MacCell 2.
	 * @return Boolean if it's an interface. 
	 **/
	bool GetIsFluidAirInterface(const type_data_mac_cell &c1,const type_data_mac_cell &c2)
	{
		return (c1.GetIsFluid()&&c2.GetIsAir())||(c2.GetIsFluid()&&c2.GetIsAir());		
	}
	/**
	 * @brief
	 * Get if it's an interface between air and fluid (that one of the two cell is air and the oher fluid).
	 * @param k1 Key to position of cell 1.
	 * @param k2 Key to position of cell 2.
	 * @return Boolean if it's an interface. 
	 **/
	bool GetIsFluidAirInterface(const type_data_key &k1,const type_data_key &k2)
	{
		return GetIsFluidAirInterface((*this)[k1].Get(),(*this)[k2].Get());
	}
	/**
	 * @brief
	 * Get if it's an interface between air and fluid (that one of the two cell is air and the oher fluid).
	 * @param k1 Key to position of cell 1.
	 * @param dim position to move from k1.
	 * @param sign Sign to move from this position.
	 * @return Boolean if it's an interface. 
	 **/
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
	/**
	 * @brief
	 * Constructor.
	 * @param data Data to copy and inherith by.
	 **/
	Data_Interface_Fluid_Air(const DataBase &data ) : DataBase(data)
	{
	}
};

#endif
