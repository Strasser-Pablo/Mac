template <int Dim,typename TypeData>
void Data_Speed_Data<Dim,TypeData>::Set(int i,const TypeData& d)
{
	m_speed.Set(i,d);
}

template <int Dim,typename TypeData>
TypeData Data_Speed_Data<Dim,TypeData>::Get(int i) const
{
	return m_speed.Get(i);
}

template <int Dim,typename TypeData>
TypeData& Data_Speed_Data<Dim,TypeData>::GetRef(int i)
{
	return m_speed.GetRef(i);
}

template <int Dim,typename TypeData>
void Data_Speed_Data<Dim,TypeData>::SetPhys(const Physvector<Dim,TypeData>& vect)
{
	m_speed=vect;
}

template <int Dim,typename TypeData>
Physvector<Dim,TypeData> Data_Speed_Data<Dim,TypeData>::GetPhys() const
{
	return m_speed;
}
