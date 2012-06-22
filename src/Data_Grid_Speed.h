#ifndef Data_Grid_Speed_H
#define Data_Grid_Speed_H
#include "Data_Speed_Data.h"
template <typename DataBase>
class Data_Grid_Speed 
{
	public:
	const static int type_dim=DataBase::type_dim;
	typedef typename DataBase::type_data_value type_data_value;
	typedef Data_Speed_Data<type_dim,type_data_value> type_speed;
	typedef Data_Grid_Speed<DataBase> type_cell_speed;
	type_speed m_speed;
	type_speed m_temp_speed;
	bool m_const[type_dim];
	bool m_has_const; 
	public:
	Data_Grid_Speed(): m_has_const(false)
	{
		for(int i=0;i<type_dim;++i)
		{
			m_const[i]=false;
		}
	}
	void Speed_Set_Const(int i);
	void Speed_Set_None_Const(int i);
	bool Speed_Get_Const(int i) const;
	void Speed_Set(int i,const type_data_value& val);
	auto Speed_Get(int i) const ->type_data_value;
	auto Speed_Get() const ->type_speed;
	void Speed_Set(const type_speed &val);
	void Speed_Temp_Set(int i,const type_data_value& val);
	auto Speed_Temp_Get(int i) const ->type_data_value;
	auto Speed_Temp_Get() const ->type_speed;
	void Speed_Temp_Set(const type_speed &val);
	void Speed_Temp_To_Speed();
	void Speed_Speed_To_Temp();
};
#include "Data_Grid_Speed.tpp"
#endif
