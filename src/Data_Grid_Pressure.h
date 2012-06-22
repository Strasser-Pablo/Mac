#ifndef Data_Grid_Pressure_H
#define Data_Grid_Pressure_H
#include "Data_Pressure_Data.h"
template<typename DataBase>
class Data_Grid_Pressure
{
	public:
	
	typedef typename DataBase::type_data_value type_data_value;
	typedef Data_Grid_Pressure<DataBase> type_cell_pressure;
	typedef void type_cell_pressure_exist;
	typedef Data_Pressure_Data<type_data_value> type_pressure;
	void Pressure_Set(const type_pressure& pres);
	auto Pressure_Get() const -> type_pressure;
	private:
	
	type_pressure m_pres;
};

#include "Data_Grid_Pressure.tpp"
#endif
