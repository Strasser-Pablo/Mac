#ifndef POLICY_IS_IN_DOMAIN_SPEED_H
#define POLICY_IS_IN_DOMAIN_SPEED_H

template<typename Data>
class Policy_Is_In_Domain_Speed
{
    typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_value;
    public:
    Policy_Is_In_Domain_Speed()
    {
    }
    bool Get_Is_Speed_In_Domain(const type_neigh neigh,int dir)
    {
        const type_neigh neigh2=neigh.GetNeighbour(dir,-1);
        if(!neigh2.IsValid())
        {
            return true;
        }
        if(neigh.CellType_GetRef().GetIsFluid()&&neigh2.CellType_GetRef().GetIsFluid())
        {
            return true;
        }
        if(!neigh.CellType_GetRef().GetIsFluid()&&!neigh2.CellType_GetRef().GetIsFluid())
        {
            return false;
        }
        type_neigh neigh3;
        if(neigh.CellType_GetRef().GetIsFluid())
        {
            neigh3=neigh.GetNeighbour(dir,1);
        }
        else if(neigh2.CellType_GetRef().GetIsFluid())
        {
            neigh3=neigh2.GetNeighbour(dir,-1);
        }

        if(!neigh3.IsValid())
        {
            return true;
        }
        if(!neigh3.CellType_GetRef().GetIsFluid())
        {
            return true;
        }
        return false;
    }
};

#endif // POLICY_IS_IN_DOMAIN_SPEED_H
