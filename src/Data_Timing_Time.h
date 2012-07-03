#ifndef Data_Timing_Time_H
#define Data_Timing_Time_H

template<typename TypeTime>
struct Data_Timing_Time
{
	TypeTime m_t;
	TypeTime m_dt;
	TypeTime m_factor;
	typedef TypeTime type_Time_Type;
};

#endif
