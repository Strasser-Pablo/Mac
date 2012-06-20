#ifndef DataRef_H
#define DataRef_H

template <typename Data>
struct DataRef
{
	Data & m_data;
	typedef Data type_data_struct;
	DataRef(Data& data):m_data(data)
	{
	}
};

#endif
