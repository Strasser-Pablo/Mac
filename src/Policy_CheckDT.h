#ifndef Policy_CheckDT_H
#define Policy_CheckDT_H

template <typename Data>
class Policy_CheckDT
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_Time_Type m_dt_min;
	type_Time_Type m_dt_max;
	public:
	Policy_CheckDT(type_Time_Type min,type_Time_Type max) : m_dt_max(max), m_dt_min(min)
	{
	}
	type_Time_Type CheckDT(type_Time_Type dt)
	{
		if(dt<m_dt_min)
		{
			return m_dt_min;
		}
		if(dt>m_dt_max)
		{
			return m_dt_max;
		}
		return dt;
	}
};

#endif
