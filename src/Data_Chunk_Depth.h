#ifndef Data_Chunk_Depth_H
#define Data_Chunk_Depth_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Depth;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Depth<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Depth : public Data_Chunk_Base<Data_Chunk_Layer<Data,N>,N >
{
	public:
	const Data& m_cop;
	Data* m_data;
	Data_Chunk_Depth(const Data& cop):m_cop(cop),m_data(nullptr)
	{
	}
	Data* Depth_GetPointer()
	{
		return m_data;
	}
	Data& Depth_GetRef()
	{
		return *m_data;	
	}
	const Data& Depth_GetRef() const
	{
		return *m_data;	
	}
	void Depth_SetPointer(Data* data)
	{
		m_data=data;
	}
	typedef Data type_depth;
};
#endif
