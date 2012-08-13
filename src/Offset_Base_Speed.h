#ifndef Offset_Base_Speed_H
#define Offset_Base_Speed_H

template <typename Data,typename Base>
class Offset_Base_Speed : public Base
{
	public:
	Data* Speed_GetPointer()
	{
		return this->m_base->Speed_GetPointer()+this->m_off.Get();
	}
	Data& Speed_GetRef()
	{
		return *(this->m_base->Speed_GetPointer()+this->m_off.Get());
	}
	const Data& Speed_GetRef() const
	{
		return *(this->m_base->Speed_GetPointer()+this->m_off.Get());
	}
	Offset_Base_Speed()
	{
	}
	template<typename ... Arg>
	Offset_Base_Speed(Arg ... arg): Base(arg...)
	{
	}
};
#endif