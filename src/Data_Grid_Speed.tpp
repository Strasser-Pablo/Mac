template <typename DataBase>
void Data_Grid_Speed<DataBase>::Speed_Set_Const(int i)
{
	m_const[i-1]=true;
	m_has_const=true;
}

template <typename DataBase>
void Data_Grid_Speed<DataBase>::Speed_Set_None_Const(int i)
{
	m_const[i-1]=false;
	bool b=false;
	for(int i=0;i<type_dim;++i)
	{
		b=b||m_const[i];
	}
	m_has_const=b;
}

template <typename DataBase>
bool Data_Grid_Speed<DataBase>::Speed_Get_Const(int i) const
{
	return m_const[i-1];
}

template <typename DataBase>
void Data_Grid_Speed<DataBase>::Speed_Set(int i,const type_data_value& val)
{
	if(!m_const[i-1])
	{
		m_speed.Set(i,val);
	}
}
template <typename DataBase>
auto Data_Grid_Speed<DataBase>::Speed_Get(int i) const -> type_data_value
{
	return m_speed.Get(i);
}

template <typename DataBase>
auto Data_Grid_Speed<DataBase>::Speed_Get() const -> type_speed
{
	return m_speed;
}

template <typename DataBase>
void Data_Grid_Speed<DataBase>::Speed_Set(const type_speed &val)
{
	if(!m_has_const)
	{
		m_speed=val;
	}
	for(int i=1;i<=type_dim;++i)
	{
		Speed_Set(i,val.Get(i));
	}
}
