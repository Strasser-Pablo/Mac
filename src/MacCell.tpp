
/**
 * @file MacCell.tpp
 * @brief 
 * Implementation file for class MacCell.
 **/

template <int DIM,class TypeData, class TypeCell>
MacCell<DIM,TypeData,TypeCell>::MacCell():m_layer(-1)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
}


template <int DIM,class TypeData, class TypeCell>
MacCell<DIM,TypeData,TypeCell>::MacCell(Physvector<DIM,TypeData> &speed,const TypeData &pressure,const int layer):m_speed(speed),m_pressure(pressure),m_layer(layer)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
}

template <int DIM,class TypeData, class TypeCell>
MacCell<DIM,TypeData,TypeCell>::MacCell(Physvector<DIM,TypeData> &speed,const TypeData &pressure, const TypeCell &type,const int layer):m_speed(speed),m_pressure(pressure),m_cell_type(type),m_layer(layer)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
}

template <int DIM,class TypeData, class TypeCell>
MacCell<DIM,TypeData,TypeCell>::~MacCell(){
}


template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetSpeed(Physvector<DIM,TypeData> &speed)
{
	if(!m_one_const)
	{
	m_speed=speed;
	}
	else
	{
		for(int i=1;i<=DIM;++i)
		{
			if(!m_const_speed[i-1])
			{
				m_speed.Set(i,speed.Get(i));
			}
		}
	}
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetSpeed(Physvector<DIM,TypeData> &speed) const
{
	speed=m_speed;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetTempSpeed(Physvector<DIM,TypeData> &speed)
{
	if(!m_one_const)
	{
	m_speedTemp=speed;
	}
	else
	{
		for(int i=1;i<=DIM;++i)
		{
			if(!m_const_speed[i-1])
			{
				m_speedTemp.Set(i,speed.Get(i));
			}

		}
	}
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetTempSpeed(Physvector<DIM,TypeData> &speed)
{
	speed=m_speedTemp;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::TempToSpeed()
{
	m_speed=m_speedTemp;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SpeedToTemp()
{
	m_speedTemp=m_speed;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetPressure(const TypeData &pressure)
{
	m_pressure=pressure;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetPressure(TypeData &pressure)
{
	pressure=m_pressure;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetCellType(const TypeCell & type)
{
	m_cell_type=type;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetCellType(TypeCell & type)const
{
	type=m_cell_type;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetLayer(const int layer)
{
	m_layer=layer;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetLayer(int & layer)const
{
	layer=m_layer;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetConstSpeed(int i,bool b)
{
	m_const_speed[i-1]=b;
	m_one_const=true;
	m_speedTemp.GetRef(i)=m_speed.Get(i);
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetConstSpeed(int i,bool &b)
{
	b=m_const_speed[i-1];
	m_one_const=true;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetInterSpeed(int i,TypeData &speed_comp)
{
	speed_comp=m_speed.GetRef(i);
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetInterSpeed(int i,TypeData &speed_comp)
{
	m_speed.GetRef(i)=speed_comp;
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::GetInterTempSpeed(int i,TypeData &speed_comp)
{
	speed_comp=m_speedTemp.GetRef(i);
}

template <int DIM,class TypeData, class TypeCell>
void MacCell<DIM,TypeData,TypeCell>::SetInterTempSpeed(int i,TypeData &speed_comp)
{
	m_speedTemp.GetRef(i)=speed_comp;
}
