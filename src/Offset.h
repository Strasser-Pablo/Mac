#ifndef OFFSET_H
#define OFFSET_H
#include "Physvector.h"
#include "Pow_Int.h"
#include "Modulo.h"
using namespace std;
template <typename type,int DIM,int N>
struct Offset
{
	static Pow_Int<N,DIM,type>& m_pow;
	type off;
	template <typename Key>
	Offset(const Key& key)
	{
		off=0;
		int B=1;
		for(int i=1;i<=DIM;++i)
		{
			off+=Modulo(key.Get(i),N)*B;
			B*=N;
		}
	}
	Offset(type m_off=0):off(m_off)
	{
	}
	bool GetNeighbour(int i,int dir,Offset<type,DIM,N>& res)
	{
		res.off=off+dir*m_pow.Get(i-1);
		if(res.off<0)
		{
			res.off+=m_pow.Get(i);
			return true;
		}
		else if(dir==1&&((res.off/m_pow.Get(i-1)%N)==0))
		{
			res.off-=m_pow.Get(i);
			return true;
		}
		else if(dir==-1&&((res.off/m_pow.Get(i-1)%N)==N-1))
		{
			res.off+=m_pow.Get(i);
			return true;
		}
		return false;
	}
	Offset<type,DIM,N>& operator++()
	{
		++off;
		return *this;
	}
	template <typename Key>
	void ToKey(Key& key,const Key& key0) const
	{
		type m_off=off;
		for(int i=DIM;i>=1;--i)
		{
			int B=m_pow.Get(i-1);
			key.GetRef(i)=key0.Get(i)*N+m_off/B;
			m_off=m_off%B;
		}
	}
	/**
	 * @brief
	 * Increment the iterator to point to the next element.
	 **/
	Offset<type,DIM,N> operator++(int)
	{
		Offset<type,DIM,N> ret(*this);
		++off;
		return ret;
	}
	bool end()
	{
		return off>=m_pow.Get(DIM);
	}
	static type MaxOffset()
	{
		return m_pow.Get(DIM);
	}
	static type LineN()
	{
		return N;
	}
	void Set(type val)
	{
		off=val;
	}
	type Get() const
	{
		return off;
	}
	typedef type type_type;
	bool operator ==(const Offset<type,DIM,N>& A) const
	{
		return A.off==off;
	}
	bool operator !=(const Offset<type,DIM,N>& A) const
	{
		return A.off!=off;
	}
};

template <typename type,int DIM,int N>
Pow_Int<N,DIM,type>& Offset<type,DIM,N>::m_pow=Singleton<Pow_Int<N,DIM,type> >::GetInstance();
#endif
