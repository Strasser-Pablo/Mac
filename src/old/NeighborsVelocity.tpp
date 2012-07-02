/**
 * @file NeighborsVelocity.tpp
 * @brief
 * Implementation file for class NeighborsVelocity.
 **/

template<int Dim,class TypeData>
NeighborsVelocity<Dim,TypeData>::NeighborsVelocity()
{
	for(int i=0;i<Dim;++i)
	{
		m_bool[i]=false;
	}
}

template<int Dim,class TypeData>
bool NeighborsVelocity<Dim,TypeData>::Get(int i,Physvector<Dim,TypeData> & vect)
{
	if(i<1)
	{
		return false;
	}
	if(i>Dim)
	{
		return false;
	}
	if(!m_bool[i-1])
	{
		return false;
	}
	else
	{
		vect=m_list[i-1];
		return true;
	}
}

template<int Dim,class TypeData>
bool NeighborsVelocity<Dim,TypeData>::Set(int i,const Physvector<Dim,TypeData> & vect)
{
	if(i<1)
	{
		return false;
	}
	if(i>Dim)
	{
		return false;
	}
	m_bool[i-1]=true;
	m_list[i-1]=vect;
		return true;
}