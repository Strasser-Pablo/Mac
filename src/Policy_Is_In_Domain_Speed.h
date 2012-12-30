#ifndef POLICY_IS_IN_DOMAIN_SPEED_H
#define POLICY_IS_IN_DOMAIN_SPEED_H

template<typename Data>
class Policy_Is_In_Domain_Speed
{
    typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_value;
    const type_Data_Grid& m_grid;

    bool NeedToApply(const type_neigh neigh)
    {
        if(neigh.CellType_GetRef().GetIsFluid())
        {
            return true;
        }
        if(neigh.Layer_GetRef().GetIsLayerEmpty())
        {
            return false;
        }
        type_neigh neigh2=neigh.GetNeighbour(m_i,-1);
        if(!neigh2.IsValid())
        {
            return false;
        }
        if(neigh2.CellType_GetRef().GetIsFluid())
        {
            return true;
        }
        return false;
    }
    public:
    Policy_Is_In_Domain_Speed(const Data& data):m_grid(data.m_data.GetGridData())
    {
    }
    bool Get_Is_Speed_In_Domain(const type_neigh neigh,int dir)
    {
        const type_neigh neigh2=neigh.GetNeighbour(dir,-1);
        if(neigh.CellType_GetRef().GetIsFluid()&&neigh2.CellType_GetRef().GetIsFluid())
        {
            return true;
        }
        const type_neigh neigh3=neigh.GetNeighbour(dir,1);
        if((!neigh2.CellType_GetRef().GetIsFluid())&&(!neigh3.CellType_GetRef().GetIsFluid()))
        {
            return true;
        }
        return false;
    }
};

#endif // POLICY_IS_IN_DOMAIN_SPEED_H
