#ifndef Data_Timing_h
#define Data_Timing_h

template<typename Data,typename Base>
class Data_Timing : public Base
{
	Data m_data;
	public:
	Data_Timing()
	{
	}
	Data_Timing(const Data & data,const Base & base) : Base(base),m_data(data)
	{
	}
	Data& GetTimingData()
	{
		return m_data;
	}
	const Data& GetTimingDataConst() const
	{
		return m_data;
	}
	typedef Data type_Data_Timing;
};

#endif
