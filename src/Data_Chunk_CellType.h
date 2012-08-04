#ifndef Data_Chunk_CellType_H
#define Data_Chunk_CellType_H
template <typename Data>
class Data_Chunk_CellType
{
	Data* m_data;
	public:
	Data_Chunk_CellType():m_data(nullptr)
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
