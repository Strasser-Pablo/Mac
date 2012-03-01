/**
 * @file Physvector.tpp
 * @brief
 * Implementation file for class Physvector 
 **/

template <int Dim,class TypeData>
Physvector<Dim,TypeData>::Physvector()
{	
}

template <int Dim,class TypeData>
Physvector<Dim,TypeData>::~Physvector()
{	
}



template <int Dim,class TypeData>
void Physvector<Dim,TypeData>::Set(int indice,TypeData value)
{
	if(indice>Dim)
	{
		throw OverFlowException(indice,Dim);
	}
	if(indice<1)
	{
		throw UnderFlowException(indice);
	}
	m_data[indice-1]=value;
}

template <int Dim,class TypeData>
void Physvector<Dim,TypeData>::SetAll(TypeData value)
{
		for(int i=0;i<Dim;++i)
		{
			m_data[i]=value;
		}
}

template <int Dim,class TypeData>
void Physvector<Dim,TypeData>::Set(UseEllipse,TypeData first,...){
	va_list list;
	va_start(list,first);
	m_data[0]=first;
	for(int i=1;i<Dim;i++){
	TypeData next=va_arg(list,TypeData);
	m_data[i]=next;
	}
	va_end(list);
}

template <int Dim,class TypeData>
TypeData Physvector<Dim,TypeData>::Get(int indice)const
{
	if(indice>Dim){
		throw OverFlowException(indice,Dim);
	}
	
	if(indice<1)
	{
		throw UnderFlowException(indice);
	}
	return m_data[indice-1];
}

template <int Dim,class TypeData>
TypeData& Physvector<Dim,TypeData>::GetRef(int indice)
{
	if(indice>Dim){
		throw OverFlowException(indice,Dim);
	}
	
	if(indice<1){
		throw UnderFlowException(indice);
	}
	return m_data[indice-1];
}

template <int Dim,class TypeData>
Physvector<Dim,TypeData> Physvector<Dim,TypeData>::operator+(const Physvector<Dim,TypeData> & B)const
{
	Physvector<Dim,TypeData> res;
	for(int i=0;i<Dim;++i)
	{
		res.m_data[i]=m_data[i]+B.m_data[i];
	}
	return res;
}

template <int Dim,class TypeData>
Physvector<Dim,TypeData> Physvector<Dim,TypeData>::operator-(const Physvector<Dim,TypeData> & B)const
{
	Physvector<Dim,TypeData> res;
	for(int i=0;i<Dim;++i)
	{
		res.m_data[i]=m_data[i]-B.m_data[i];
	}
	return res;
}


template <int Dim,class TypeData>
Physvector<Dim,TypeData>& Physvector<Dim,TypeData>::operator+=(const Physvector<Dim,TypeData> & B)
{
	for(int i=0;i<Dim;++i)
	{
		m_data[i]+=B.m_data[i];
	}
	return *this;
}

template <int Dim,class TypeData>
Physvector<Dim,TypeData>& Physvector<Dim,TypeData>::operator-=(const Physvector<Dim,TypeData> & B)
{
	for(int i=0;i<Dim;++i)
	{
		m_data[i]-=B.m_data[i];
	}
	return *this;
}


template <int Dim,class TypeData>
Physvector<Dim,TypeData> operator*(const TypeData & C,const Physvector<Dim,TypeData> & vect){
	Physvector<Dim,TypeData> res;
	for(int i=0;i<Dim;++i)
	{
		res.m_data[i]=C*vect.m_data[i];
	}
	return res;
}


template <int Dim,class TypeData>
Physvector<Dim,TypeData> operator*(const Physvector<Dim,TypeData> & vect,const TypeData & C){
Physvector<Dim,TypeData> res;
	for(int i=0;i<Dim;++i)
	{
		res.m_data[i]=vect.m_data[i]*C;
	}
	return res;
}

template <int Dim,class TypeData>
ostream& operator<<(ostream& output, Physvector<Dim,TypeData>& v)
{
	output<<"< ";
	for(int i=1;i<Dim;++i)
	{
		output<<v.Get(i)<<" ,";
	}
	output<<v.Get(Dim)<<" >";
	return output;
}

template <int Dim,class TypeData>
Physvector<Dim,TypeData>& Physvector<Dim,TypeData>::operator*=(const TypeData & C){
	for(int i=0;i<Dim;++i)
	{
		m_data[i]*=C;
	}
	return *this;
}

template <int Dim,class TypeData>
bool Physvector<Dim,TypeData>::operator==(const Physvector<Dim,TypeData> & b){
	for(int i=0;i<Dim;++i)
	{
		if(m_data[i]!=b.m_data[i])
		{
			return false;
		}		
	}
	return true;
}

template <int Dim,class TypeData>
bool Physvector<Dim,TypeData>::operator!=(const Physvector<Dim,TypeData> & b){
	for(int i=0;i<Dim;++i)
	{
		if(m_data[i]!=b.m_data[i])
		{
			return true;
		}		
	}
	return false;
}

template <int Dim,class TypeData>
TypeData Physvector<Dim,TypeData>::Norm()
{
	TypeData ret=0;
	for(int i=0;i<Dim;++i)
	{
		ret+=m_data[i]*m_data[i];
	}
	return sqrt(ret);
}

template <int Dim,class TypeData>
TypeData Physvector<Dim,TypeData>::Norm2()
{
	TypeData ret=0;
	for(int i=0;i<Dim;++i)
	{
		ret+=m_data[i]*m_data[i];
	}
	return ret;
}


#ifdef TesThrowIntExcept
template <int Dim,class TypeData>
void Physvector<Dim,TypeData>::Boum()
{
	throw OutOfBoundException();
}
#endif