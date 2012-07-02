/**
 * @file MacCell.tpp
 * @brief 
 * Implementation file for class MacCell.
 **/
template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetCirculation(const TypeData &circulation)
{
	m_circulation=circulation;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetCirculation(TypeData & Circulation)
{
	Circulation=m_circulation;
}

template <int DIM,class TypeData, class TypeCell,int ID>
MacCell<DIM,TypeData,TypeCell,ID>::MacCell():m_div(0),m_viscosity_force(0),m_layer(-1)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
	m_speedTemp.SetAll(0);
}


template <int DIM,class TypeData, class TypeCell,int ID>
MacCell<DIM,TypeData,TypeCell,ID>::MacCell(Physvector<DIM,TypeData> &speed,const TypeData &pressure,const int layer):m_speed(speed),m_pressure(pressure),m_div(0),m_viscosity_force(0),m_layer(layer)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
	m_speedTemp.SetAll(0);
}

template <int DIM,class TypeData, class TypeCell,int ID>
MacCell<DIM,TypeData,TypeCell,ID>::MacCell(Physvector<DIM,TypeData> &speed,const TypeData &pressure, const TypeCell &type,const int layer):m_speed(speed),m_pressure(pressure),m_cell_type(type),m_layer(layer)
{
	for(int i=0;i<DIM;++i)
	{
		m_const_speed[i]=false;
	}
	m_one_const=false;
	m_speedTemp.SetAll(0);
}

template <int DIM,class TypeData, class TypeCell,int ID>
MacCell<DIM,TypeData,TypeCell,ID>::~MacCell(){
}


template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetSpeed(Physvector<DIM,TypeData> &speed)
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

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetSpeed(Physvector<DIM,TypeData> &speed) const
{
	speed=m_speed;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetTempSpeed(Physvector<DIM,TypeData> &speed)
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

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetTempSpeed(Physvector<DIM,TypeData> &speed)
{
	speed=m_speedTemp;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::TempToSpeed()
{
	m_speed=m_speedTemp;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SpeedToTemp()
{
	m_speedTemp=m_speed;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetPressure(const TypeData &pressure)
{
	m_pressure=pressure;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetPressure(TypeData &pressure)
{
	pressure=m_pressure;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetCellType(const TypeCell & type)
{
	m_cell_type=type;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetCellType(TypeCell & type)const
{
	type=m_cell_type;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetLayer(const int layer)
{
	m_layer=layer;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetLayer(int & layer)const
{
	layer=m_layer;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetConstSpeed(int i,bool b)
{
	m_const_speed[i-1]=b;
	m_one_const=true;
	m_speedTemp.GetRef(i)=m_speed.Get(i);
	++m_nb_const_speed;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetConstSpeed(int i,bool &b) const
{
	b=m_const_speed[i-1];
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetInterSpeed(int i,TypeData &speed_comp)
{
	speed_comp=m_speed.GetRef(i);
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetInterSpeed(int i,TypeData &speed_comp)
{
	if(!m_const_speed[i-1])
	{
		m_speed.GetRef(i)=speed_comp;
	}
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetInterTempSpeed(int i,TypeData &speed_comp)
{
	speed_comp=m_speedTemp.GetRef(i);
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetInterTempSpeed(int i,TypeData &speed_comp)
{
	if(!m_const_speed[i-1])
	{
		m_speedTemp.GetRef(i)=speed_comp;
	}
}


template <int DIM,class TypeData, class TypeCell,int ID>
template <class Archive>
void MacCell<DIM,TypeData,TypeCell,ID>::serialize(Archive & Ar,const unsigned int version)
{
	Ar & boost::serialization::make_nvp("Speed",m_speed);
	Ar & boost::serialization::make_nvp("Pressure",m_pressure);
	Ar & boost::serialization::make_nvp("Cell_Type",m_cell_type);
	Ar & boost::serialization::make_nvp("Const_Speed",m_const_speed);
	Ar & boost::serialization::make_nvp("One_Const_Speed",m_one_const);
	Ar & boost::serialization::make_nvp("Layer",m_layer);
}

template <int DIM,class TypeData, class TypeCell,int ID>
int MacCell<DIM,TypeData,TypeCell,ID>::m_nb_const_speed=0;

template <int DIM,class TypeData, class TypeCell,int ID>
int MacCell<DIM,TypeData,TypeCell,ID>::GetNBConstSpeed()
{
	return m_nb_const_speed;
}
template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetDivergence(const TypeData &  div)
{
	m_div=div;
}


template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetDivergence(TypeData & div)
{
	div=m_div;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::SetViscosityForce(const TypeData &Viscosity)
{
	m_viscosity_force=Viscosity;
}

template <int DIM,class TypeData, class TypeCell,int ID>
void MacCell<DIM,TypeData,TypeCell,ID>::GetViscosityForce(TypeData & Viscosity)
{
	Viscosity=m_viscosity_force;
}
