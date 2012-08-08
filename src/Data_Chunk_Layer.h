#ifndef Data_Chunk_Layer_H
#define Data_Chunk_Layer_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Layer;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Layer<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Layer : public Data_Chunk_Base<Data_Chunk_Layer<Data,N>,N >
{
	public:
	Data* m_data;
	Data_Chunk_Layer():m_data(nullptr)
	{
	}
	Data* Layer_GetPointer()
	{
		return m_data;
	}
	Data& Layer_GetRef()
	{
		return *m_data;	
	}
	const Data& Layer_GetRef() const
	{
		return *m_data;	
	}
	void Layer_SetPointer(Data* data)
	{
		m_data=data;
	}
};
#endif
