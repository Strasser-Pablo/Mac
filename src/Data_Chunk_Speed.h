#ifndef Data_Chunk_Speed_H
#define Data_Chunk_Speed_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Speed;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Speed<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Speed : public Data_Chunk_Base<Data_Chunk_Speed<Data,N>,N >
{
	public:
	const Data& m_cop;
	Data* m_data;
	Data_Chunk_Speed(const Data& cop):m_cop(cop),m_data(nullptr)
	{
	}
	Data* Speed_GetPointer()
	{
		return m_data;
	}
	Data& Speed_GetRef()
	{
		return *m_data;
	}
	const Data& Speed_GetRef() const
	{
		return *m_data;
	}
	void Speed_SetPointer(Data* data)
	{
		m_data=data;
	}
};
#endif
