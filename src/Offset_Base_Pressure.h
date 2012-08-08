#ifndef Offset_Base_Pressure_H
#define Offset_Base_Pressure_H

template <typename Data,typename Base>
class Offset_Base_Pressure : public Base
{
	public:
	Data* Pressure_GetPointer()
	{
		return this->m_base->Pressure_GetPointer()+this->m_off.Get();
	}
	Data& Pressure_GetRef()
	{
		return *(this->m_base->Pressure_GetPointer()+this->m_off.Get());
	}
	const Data& Pressure_GetRef() const
	{
		return *(this->m_base->Pressure_GetPointer()+this->m_off.Get());
	}
	Offset_Base_Pressure()
	{
	}
	template<typename ... Arg>
	Offset_Base_Pressure(Arg ... arg): Base(arg...)
	{
	}
};
#endif
