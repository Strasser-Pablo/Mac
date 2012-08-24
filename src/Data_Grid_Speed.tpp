template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Set_Const(int i)
{
	m_const[i-1]=true;
}

template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Set_None_Const(int i)
{
	m_const[i-1]=false;
}

template <typename DataBase,typename Const,typename Speed>
bool Data_Grid_Speed<DataBase,Const,Speed>::Speed_Get_Const(int i) const
{
	return m_const[i-1];
}

template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Set(int i,const type_data_value& val)
{
	if(!m_const[i-1])
	{
		m_speed.Set(i,val);
	}
}
template <typename DataBase,typename Const,typename Speed>
auto Data_Grid_Speed<DataBase,Const,Speed>::Speed_Get(int i) const -> type_data_value
{
	return m_speed.Get(i);
}

template <typename DataBase,typename Const,typename Speed>
auto Data_Grid_Speed<DataBase,Const,Speed>::Speed_Get() const -> type_speed
{
	return m_speed;
}

template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Set(const type_speed &val)
{
	if(m_const.none())
	{
		m_speed=val;
	}
	for(int i=1;i<=type_dim;++i)
	{
		Speed_Set(i,val.Get(i));
	}
}


template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Temp_Set(int i,const type_data_value& val)
{
	if(!m_const[i-1])
	{
		m_temp_speed.Set(i,val);
	}
}
template <typename DataBase,typename Const,typename Speed>
auto Data_Grid_Speed<DataBase,Const,Speed>::Speed_Temp_Get(int i) const -> type_data_value
{
	return m_temp_speed.Get(i);
}

template <typename DataBase,typename Const,typename Speed>
auto Data_Grid_Speed<DataBase,Const,Speed>::Speed_Temp_Get() const -> type_speed
{
	return m_temp_speed;
}

template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Temp_Set(const type_speed &val)
{
	if(m_const.none())
	{
		m_temp_speed=val;
	}
	for(int i=1;i<=type_dim;++i)
	{
		Speed_Temp_Set(i,val.Get(i));
	}
}


template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Temp_To_Speed()
{
	m_speed=m_temp_speed;
}

template <typename DataBase,typename Const,typename Speed>
void Data_Grid_Speed<DataBase,Const,Speed>::Speed_Speed_To_Temp()
{
	m_temp_speed=m_speed;
}

template <typename DataBase,typename Const,typename Speed>
bool Data_Grid_Speed<DataBase,Const,Speed>::Speed_Is_One_Const() const
{
	return m_const.any();
}
