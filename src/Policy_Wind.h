#ifndef Policy_Wind_H
#define Policy_Wind_H

template <typename Data>
class Policy_Wind
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_data::type_speed::type_data_value type_speed_value;
	const type_speed_value m_val;
	const int m_dir;
	const int m_idir;
	public:
	Policy_Wind(type_speed_value val,int idir,int dir):m_val(val),m_dir(dir),m_idir(idir)
	{
	}
	int GetWindDirection()
	{
		return m_idir;
	}
	type_speed_value GetWindIntensity()
	{
		return m_val;
	}
	int GetWindSens()
	{
		return m_dir;
	}
};
#endif
