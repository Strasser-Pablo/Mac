#ifndef DATA_CHUNK_SPEED_VON_NEUMANN_H
#define DATA_CHUNK_SPEED_VON_NEUMANN_H

#include "Data_Chunk_Base.h"

template <typename Data,int N>
class Data_Chunk_Speed_Von_Neumann;

template<typename Data,int N>
struct Data_Chunk_Trait<Data_Chunk_Speed_Von_Neumann<Data,N> >
{
    typedef Data type_data;
};

template <typename Data,int N>
class Data_Chunk_Speed_Von_Neumann : public Data_Chunk_Base<Data_Chunk_Speed_Von_Neumann<Data,N>,N >
{
    public:
    const Data& m_cop;
    Data* m_data;
    Data_Chunk_Speed_Von_Neumann(const Data& cop):m_cop(cop),m_data(nullptr)
    {
    }
    Data* Speed_Von_Neumann_GetPointer()
    {
        return m_data;
    }
    Data& Speed_Von_Neumann_GetRef()
    {
        return *m_data;
    }
    const Data& Speed_Von_Neumann_GetRef() const
    {
        return *m_data;
    }
    void Speed_Von_Neumann_SetPointer(Data* data)
    {
        m_data=data;
    }
    typedef Data type_Speed_Von_Neumann;
};
#endif // DATA_CHUNK_SPEED_VON_NEUMANN_H
