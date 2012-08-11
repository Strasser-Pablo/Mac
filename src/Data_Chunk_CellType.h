#ifndef Data_Chunk_CellType_H
#define Data_Chunk_CellType_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_CellType;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_CellType<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_CellType : public Data_Chunk_Base<Data_Chunk_CellType<Data,N>,N >
{
	public:
	const Data& m_cop;
	Data* m_data;
	Data_Chunk_CellType(const Data& cop):m_cop(cop),m_data(nullptr)
	{
	}
	Data* CellType_GetPointer()
	{
		return m_data;
	}
	Data& CellType_GetRef()
	{
		return *m_data;	
	}
	const Data& CellType_GetRef() const
	{
		return *m_data;	
	}
	void CellType_SetPointer(Data* data)
	{
		m_data=data;
	}
};
#endif
