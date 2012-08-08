#ifndef Data_Chunk_Bool_Array_H
#define Data_Chunk_Bool_Array_H

#include <bitset>

using namespace std;

template <int N>
class Data_Chunk_Bool_Array  
{
	bitset<N> m_bit;
	public:
	bitset<N>& GetChunk_Bool_Array()
	{
		return m_bit;
	}
	const bitset<N>& GetChunk_Bool_Array() const
	{
		return m_bit;
	}
	void Allocate()
	{
	}
	void UnAllocate()
	{
	}
	typedef bitset<N> type_value_bool_array;
};

#endif
