#ifndef Data_Grid_Pressure_H
#define Data_Grid_Pressure_H
#include "Data_Pressure_Data.h"
/**
 * @ingroup GR_Data_Pressure
 * @brief
 * Method to store and access pressure.
 **/
template<typename DataBase>
class Data_Grid_Pressure
{
	public:
	/**
	 * @brief
	 * Type to store numeric value.
	 **/
	typedef typename DataBase::type_data_value type_data_value;
	/**
	 * @brief
	 * Type of this class.
	 **/
	typedef Data_Grid_Pressure<DataBase> type_cell_pressure;
	/**
	 * @brief
	 * Type indicating that this class exist, used in SFINAE.
	 **/
	typedef void type_cell_pressure_exist;
	/**
	 * @brief
	 * Pressure Type.
	 **/
	typedef Data_Pressure_Data<type_data_value> type_pressure;
	/**
	 * @brief
	 * Set Pressure.
	 * @param pres Value to set to.
	 **/
	void Pressure_Set(const type_pressure& pres);
	/**
	 * @brief
	 * Get Pressure.
	 * @return Returned Pressure.
	 **/
	auto __attribute__ ((pure)) Pressure_Get() const -> type_pressure;
	private:
	/**
	 * @brief
	 * Stored value for pressure.
	 **/	
	type_pressure m_pres;
};

#include "Data_Grid_Pressure.tpp"
#endif
