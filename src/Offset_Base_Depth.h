#ifndef Offset_Base_Depth_H
#define Offset_Base_Depth_H

template <typename Data,typename Base>
class Offset_Base_Depth : public Base
{
	public:
	Data* Depth_GetPointer()
	{
		return this->m_base->Depth_GetPointer()+this->m_off.Get();
	}
	Data& Depth_GetRef()
	{
		return *(this->m_base->Depth_GetPointer()+this->m_off.Get());
	}
	const Data& Depth_GetRef() const
	{
		return *(this->m_base->Depth_GetPointer()+this->m_off.Get());
	}
	Offset_Base_Depth()
	{
	}
	template<typename ... Arg>
	Offset_Base_Depth(Arg ... arg): Base(arg...)
	{
	}
};
#endif
