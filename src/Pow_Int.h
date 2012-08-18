#ifndef Pow_Int_H
#define Pow_Int_H
#include "Singleton.h"
#include <cmath>
template<int N,int Dim,class Type>
class Pow_Int : public Singleton<Pow_Int<N,Dim,Type> >
{
	friend class Singleton<Pow_Int<N,Dim,Type> >;
	Type m_pow[Dim+1];
	Pow_Int();
	Pow_Int(const Pow_Int<N,Dim,Type>&)=delete;
	~Pow_Int() __attribute__ ((const)); 
	public:
	Type Get(int i)
	{
		return m_pow[i];
	}
};
#include "Singleton_Impl.h"
#include "Pow_Int_Impl.h"
#endif
