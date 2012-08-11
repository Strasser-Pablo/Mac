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
		static_cast<Child&>(*this).m_data=reinterpret_cast<type_data*>(::operator new (N*sizeof(type_data)));
		for(int i=0;i<N;++i)
		{
			new  (static_cast<Child&>(*this).m_data+i) type_data(static_cast<Child&>(*this).m_cop);
		}
	
	}
	void UnAllocate()
	{
		if(static_cast<Child&>(*this).m_data!=nullptr)
		{
			for(int i=0;i<N;++i)
			{
				static_cast<Child&>(*this).m_data[i].~type_data();
			}
			if(static_cast<Child&>(*this).m_data!=nullptr)
			{
				::operator delete(reinterpret_cast<void*>(static_cast<Child&>(*this).m_data));
			}
		}
	}
};
#endif
