#ifndef Data_Chunk_Pressure_H
#define Data_Chunk_Pressure_H
template <typename Data>
class Data_Chunk_Pressure
{
	Data* m_data;
	public:
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
