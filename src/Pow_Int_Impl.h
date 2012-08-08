template<int N,int Dim,class Type>
Pow_Int<N,Dim,Type>::Pow_Int()
{
	Type temp=1;
	for(int i=0;i<=Dim;++i)
	{
		m_pow[i]=temp;
		temp*=N;
	}
}

template<int N,int Dim,class Type>
Pow_Int<N,Dim,Type>::~Pow_Int()
{
}
