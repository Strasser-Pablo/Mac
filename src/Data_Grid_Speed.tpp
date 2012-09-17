template <typename DataBase,typename Const>
void Data_Grid_Speed<DataBase,Const>::Set_Const(int i)
{
	m_const[i-1]=true;
}

template <typename DataBase,typename Const>
void Data_Grid_Speed<DataBase,Const>::Set_None_Const(int i)
{
	m_const[i-1]=false;
}

template <typename DataBase,typename Const>
bool Data_Grid_Speed<DataBase,Const>::Get_Const(int i) const
{
	return m_const[i-1];
}

template <typename DataBase,typename Const>
void Data_Grid_Speed<DataBase,Const>::Set(int i,const type_data_value& val,bool force)
{
	if(force||!m_const[i-1])
	{
		m_speed.Set(i,val);
	}
}

template <typename DataBase,typename Const>
void Data_Grid_Speed<DataBase,Const>::SetZero(bool force)
{
	if(force||m_const.none())
	{
		m_speed.SetZero();
	}
	else
	{
		for(int i=1;i<=type_dim;++i)
		{
			Set(i,0);
		}
	}
}

template <typename DataBase,typename Const>
auto Data_Grid_Speed<DataBase,Const>::Get(int i) const -> type_data_value
{
	return m_speed.Get(i);
}

template <typename DataBase,typename Const>
auto Data_Grid_Speed<DataBase,Const>::Get() const -> type_speed
{
	return m_speed;
}

template <typename DataBase,typename Const>
void Data_Grid_Speed<DataBase,Const>::Set(const type_speed &val,bool force)
{
	if(force||m_const.none())
	{
		m_speed=val;
	}
	else
	{
		for(int i=1;i<=type_dim;++i)
		{
			Set(i,val.Get(i));
		}
	}
}

template <typename DataBase,typename Const>
bool Data_Grid_Speed<DataBase,Const>::Is_One_Const() const
{
	return m_const.any();
}

template <typename DataBase,typename Const>
const Const& Data_Grid_Speed<DataBase,Const>::GetConstRef() const
{
	return m_const;
}
