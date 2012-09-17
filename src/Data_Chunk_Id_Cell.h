#ifndef Data_Chunk_Id_Cell_H
#define Data_Chunk_Id_Cell_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Id_Cell;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Id_Cell<Data,N> >
{
	typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Id_Cell : public Data_Chunk_Base<Data_Chunk_Id_Cell<Data,N>,N >
{
	public:
	const Data& m_cop;
	Data* m_data;
	Data_Chunk_Id_Cell(const Data& cop):m_cop(cop),m_data(nullptr)
	{
	}
	Data* Id_Cell_GetPointer()
	{
		return m_data;
	}
	Data& Id_Cell_GetRef()
	{
		return *m_data;	
	}
	const Data& Id_Cell_GetRef() const
	{
		return *m_data;	
	}
	void Id_Cell_SetPointer(Data* data)
	{
		m_data=data;
	}
	typedef Data type_id_cell;
};
#endif
