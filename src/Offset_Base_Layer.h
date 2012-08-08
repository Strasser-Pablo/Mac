#ifndef Offset_Base_Layer_H
#define Offset_Base_Layer_H

template <typename Data,typename Base>
class Offset_Base_Layer : public Base
{
	public:
	Data* Layer_GetPointer()
	{
		return this->m_base->Layer_GetPointer()+this->m_off.Get();
	}
	Data& Layer_GetRef()
	{
		return *(this->m_base->Layer_GetPointer()+this->m_off.Get());
	}
	const Data& Layer_GetRef() const
	{
		return *(this->m_base->Layer_GetPointer()+this->m_off.Get());
	}
	Offset_Base_Layer()
	{
	}
	template<typename ... Arg>
	Offset_Base_Layer(Arg ... arg): Base(arg...)
	{
	}
};
#endif
