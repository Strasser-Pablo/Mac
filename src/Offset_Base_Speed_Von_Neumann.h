#ifndef OFFSET_BASE_SPEED_VON_NEUMANN_H
#define OFFSET_BASE_SPEED_VON_NEUMANN_H

template <typename Data,typename Base>
class Offset_Base_Speed_Von_Neumann : public Base
{
    public:
    Data* Speed_Von_Neumann_GetPointer()
    {
        return this->m_base->Speed_Von_Neumann_GetPointer()+this->m_off.Get();
    }
    Data& Speed_Von_Neumann_GetRef()
    {
        return *(this->m_base->Speed_Von_Neumann_GetPointer()+this->m_off.Get());
    }
    const Data& Speed_Von_Neumann_GetRef() const
    {
        return *(this->m_base->Speed_Von_Neumann_GetPointer()+this->m_off.Get());
    }
    Offset_Base_Speed_Von_Neumann()
    {
    }
    template<typename ... Arg>
    Offset_Base_Speed_Von_Neumann(Arg ... arg): Base(arg...)
    {
    }
};

#endif // OFFSET_BASE_SPEED_VON_NEUMANN_H
