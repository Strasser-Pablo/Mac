#ifndef Offset_Base_Id_Cell_H
#define Offset_Base_Id_Cell_H

template <typename Data,typename Base>
class Offset_Base_Id_Cell : public Base
{
	public:
	Data* Id_Cell_GetPointer()
	{
		return this->m_base->Id_Cell_GetPointer()+this->m_off.Get();
	}
	Data& Id_Cell_GetRef()
	{
		return *(this->m_base->Id_Cell_GetPointer()+this->m_off.Get());
	}
	const Data& Id_Cell_GetRef() const
	{
		return *(this->m_base->Id_Cell_GetPointer()+this->m_off.Get());
	}
	Offset_Base_Id_Cell()
	{
	}
	template<typename ... Arg>
	Offset_Base_Id_Cell(Arg ... arg): Base(arg...)
	{
	}
};
#endif
