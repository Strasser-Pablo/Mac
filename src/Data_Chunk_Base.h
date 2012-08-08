#ifndef Data_Chunk_Base_H
#define Data_Chunk_Base_H

#include <iostream>

using namespace std;

template<typename Child>
struct Data_Chunk_Trait
{
};

using namespace std;

template <typename Child,int N>
class Data_Chunk_Base
{
	typedef typename Data_Chunk_Trait<Child>::type_data type_data;
	public:
	void Allocate()
	{
		UnAllocate();
		static_cast<Child&>(*this).m_data=new type_data[N];
	}
	void UnAllocate()
	{
		if(static_cast<Child&>(*this).m_data!=nullptr)
		{
			delete[] static_cast<Child&>(*this).m_data;
		}
	}
};
#endif
