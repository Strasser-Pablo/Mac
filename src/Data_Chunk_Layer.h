#ifndef Data_Chunk_Layer_H
#define Data_Chunk_Layer_H
template <typename Data>
class Data_Chunk_Layer
{
	Data* m_data;
	public:
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
