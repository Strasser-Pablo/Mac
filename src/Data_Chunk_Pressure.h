#ifndef Data_Chunk_Pressure_H
#define Data_Chunk_Pressure_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Pressure;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Pressure<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Pressure : public Data_Chunk_Base<Data_Chunk_Pressure<Data,N>,N >
{
	public:
	Data* m_data;
	Data_Chunk_Pressure():m_data(nullptr)
	{
	}
	Data* Pressure_GetPointer()
	{
		return m_data;
	}
	Data& Pressure_GetRef()
	{
		return *m_data;	
	}
	const Data& Pressure_GetRef() const
	{
		return *m_data;	
	}
	void Pressure_SetPointer(Data* data)
	{
		m_data=data;
	}
};
#endif
