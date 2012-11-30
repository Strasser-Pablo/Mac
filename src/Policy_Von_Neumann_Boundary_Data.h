#ifndef POLICY_VON_NEUMANN_BOUNDARY_DATA_H
#define POLICY_VON_NEUMANN_BOUNDARY_DATA_H

template<typename Data>
class Policy_Von_Neumann_Boundary_Data
{
    typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_offset type_neigh;
    type_Data_Grid& m_grid;
    public:
    Policy_Von_Neumann_Boundary_Data(Data& data) :m_grid(data.m_data.GetGridData())
    {
    }
    bool Get_Is_Von_Neumann_Boundary(type_neigh neigh,int i,int sign)
    {
        if(sign!=-1)
        {
            neigh=neigh.GetNeighbour(i,1);
            if(!neigh.IsValid())
            {
                return false;
            }
        }
        return neigh.Speed_Von_Neumann_GetRef().Get_Von_Neumann(i);
    }
};

#endif // POLICY_VON_NEUMANN_BOUNDARY_DATA_H
