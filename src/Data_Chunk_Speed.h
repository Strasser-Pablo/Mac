#ifndef Data_Chunk_Speed_H
#define Data_Chunk_Speed_H
template <typename Data>
class Data_Chunk_Speed
{
	Data* m_data;
	public:
	Data_Chunk_Speed():m_data(nullptr)
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
