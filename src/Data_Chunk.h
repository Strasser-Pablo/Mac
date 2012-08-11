#ifndef Data_Chunk_H
#define Data_Chunk_H

template <class ... Chunk>
class Data_Chunk : public Chunk...
{
	public:
	Data_Chunk(const Chunk&...  chunk): Chunk(chunk)...
	{
	}
	void Allocate()
	{
		Allocate_Impl(static_cast<Chunk*>(this) ...);
	}
	template<typename first,class ... Chunk2>
	void Allocate_Impl(first* f,Chunk2* ... c)
	{
		f->Allocate();
		Allocate_Impl(c...);
	}
	template<class ... Chunk2>
	void Allocate_Impl(Chunk2* ... c __attribute__ ((unused)))
	{
	}
	void UnAllocate()
	{
		UnAllocate_Impl(static_cast<Chunk*>(this) ...);
	}
	template<typename first,class ... Chunk2>
	void UnAllocate_Impl(first* f,Chunk2* ... c)
	{
		f->UnAllocate();
		UnAllocate_Impl(c...);
	}
	template<class ... Chunk2>
	void UnAllocate_Impl(Chunk2* ... c __attribute__ ((unused)))
	{
	}
};
#endif
