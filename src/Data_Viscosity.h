#ifndef Data_Viscosity_H
#define Data_Viscosity_H

template <typename Base>
class Data_Viscosity : public Base
{
	public:
	typedef typename Base::type_data_value type_data_value;
	Data_Viscosity(const Base& base):Base(base)
	{
	}
	type_data_value m_viscosity;
};

#endif
