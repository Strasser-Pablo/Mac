#ifndef Offset_Base_CellType_H
#define Offset_Base_CellType_H

template <typename Data,typename Base>
class Offset_Base_CellType : public Base
{
	public:
	Data* CellType_GetPointer()
	{
		return this->m_base->CellType_GetPointer()+this->m_off.Get();
	}
	Data& CellType_GetRef()
	{
		return *(this->m_base->CellType_GetPointer()+this->m_off.Get());
	}
	const Data& CellType_GetRef() const
	{
		return *(this->m_base->CellType_GetPointer()+this->m_off.Get());
	}
	Offset_Base_CellType()
	{
	}
	template<typename ... Arg>
	Offset_Base_CellType(Arg ... arg): Base(arg...)
	{
	}
};
#endif
