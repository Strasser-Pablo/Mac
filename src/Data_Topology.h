#ifndef Data_Topology_H
#define Data_Topology_H

template <typename Data,typename Base>
class Data_Topology : public Base
{
	Data m_data;
	public:
	Data_Topology()
	{
	}
	Data_Topology(const Data & data,const Base & base) : Base(base),m_data(data)
	{
	}
	Data& GetTopologyData()
	{
		return m_data;
	}
	const Data& GetTopologyDataConst() const
	{
		return m_data;
	}
	typedef Data type_Data_Topology;
};
#endif
