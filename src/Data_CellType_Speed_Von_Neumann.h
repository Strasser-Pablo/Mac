#ifndef DATA_CELLTYPE_SPEED_VON_NEUMANN_H
#define DATA_CELLTYPE_SPEED_VON_NEUMANN_H

#include <bitset>
using std::bitset;

template <typename DataBase>
class Data_CellType_Speed_Von_Neumann
{
    public:
    /**
     * @brief
     * Dimension of the problem.
     **/
    const static int type_dim=DataBase::type_dim;
    private:
    bitset<type_dim> m_bit;
    public:
    void Set_Von_Neumann(int i,bool b=true)
    {
        m_bit[i-1]=b;
    }
    bool Get_Von_Neumann(int i) const
    {
        return m_bit[i-1];
    }
    bool Get_Is_One_Von_Neumann() const
    {
        return m_bit.any();
    }
};

#endif // DATA_CELLTYPE_SPEED_VON_NEUMANN_H
