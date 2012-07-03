#ifndef Data_Grid_Data_H
#define Data_Grid_Data_H

template <typename Data,typename Base>
class Data_Grid_Data : public Base
{
	Data m_data;
	public:
	Data_Grid_Data()
	{
	}
	Data_Grid_Data(const Data & data,const Base & base) : Base(base),m_data(data)
	{
	}
	Data& GetGridData()
	{
		return m_data;
	}
	const Data& GetGridDataConst() const
	{
		return m_data;
	}
	typedef Data type_Data_Grid;
};
#endif
