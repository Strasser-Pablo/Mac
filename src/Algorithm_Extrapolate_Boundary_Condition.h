#ifndef ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H
#define ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H

#include <cmath>
using std::nan;


template <typename Data,typename Policy>
class Algorithm_Extrapolate_Boundary_Condition : public Policy
{
    using Policy::Get_Is_Speed_In_Domain;
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    static const int type_dim=type_Data_Grid::type_key::type_dim;
    const type_spacing_vector &m_1_h;
    const type_spacing_vector &m_h;
    type_Data_Grid& m_grid;
public:
    Algorithm_Extrapolate_Boundary_Condition(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_h(data.m_data.GetGridData().m_h.GetRef())
    {
    }
    void Do()
    {
        if(type_dim==2)
        {
            Do2d();
        }
        if(type_dim==3)
        {
            Do3d();
        }
    }
private:

    /**
     * @brief
     * Methode that return true if cell is a boundary between fluid and air.
     * @param neigh Cell to look at.
     * @param dir array witch will return the direction to air. For every direction separing fluid and air.
     * @param sign array witch return the sign the air cell is (below or above)
     * @param n the number of neighbour.
     **/
    bool IsBoundary(const type_neigh& neigh,int  dir[2*type_dim],int  sign[2*type_dim],int &n)
    {
        if(neigh.CellType_GetRef().GetIsAir())
        {
            return false;
        }
        n=0;
        for(int i=1;i<=type_dim;++i)
        {

            for(int s=-1;s<=1;s+=2)
            {
                dir[n]=i;
                sign[n]=s;
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(neigh2.IsValid())
                {
                    if(neigh2.CellType_GetRef().GetIsAir())
                    {
                        ++n;
                    }
                }
            }
        }
        if(n>0)
        {
            return true;
        }
        return false;
    }
    /**
     * @brief IsBoundary Overload of IsBoundary witch only test if it's a boundary.
     * @param neigh Cell to test
     * @return true if it's a boundary none in the contrary.
     */
    bool IsBoundary(const type_neigh& neigh)
    {
        if(neigh.CellType_GetRef().GetIsAir())
        {
            return false;
        }
        for(int i=1;i<=type_dim;++i)
        {

            for(int s=-1;s<=1;s+=2)
            {
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(neigh2.IsValid())
                {
                    if(neigh2.CellType_GetRef().GetIsAir())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    /**
     * @brief Choose_Boundary_Case_2d function witch treat the boundary condition.
     * @param neigh Cell in question.
     * @param dir Direction between air and fluid.
     * @param sign Sign between air and fluid.
     * @param n Number of boundary.
     */
    void Choose_Boundary_Case_2d(type_neigh neigh,int  dir[2*type_dim],int  sign[2*type_dim],int &n)
    {
        if(n==1)
        {
            int dir2=1;
            if(dir[0]==1)
            {
                dir2=2;
            }
            bool b=true;
            for(int i=-1;i<=1;i+=2)
            {
                type_neigh neigh2=neigh.GetNeighbour(dir2,i);
                int  dirtemp[2*type_dim];
                int  signtemp[2*type_dim];
                int ntemp;
                IsBoundary(neigh2,dirtemp,signtemp,ntemp);
                if(ntemp==1&&dirtemp[0]==dir[0])
                {
                    b=false;
                    if(i<0)
                    {
                        Apply_2d_Plane(neigh2,neigh,dir[0],sign[0]);
                    }
                    else if(i>0)
                    {
                        Apply_2d_Plane(neigh,neigh2,dir[0],sign[0]);
                    }
                }
            }
            if(b)
            {
                type_neigh neigh3=neigh;
                if(sign[0]==1)
                {
                    neigh3=neigh.GetNeighbour(dir[0],1);
                }
                if(!Get_Is_Speed_In_Domain(neigh3,dir[0]))
                {
                    neigh3.Speed_GetRef().Set(dir[0],nan(""));
                }
            }
        }
        else if(n==2)
        {
            if(dir[0]!=dir[1])
            {
                int sa=sign[0];
                int sb=sign[1];
                if(dir[0]>dir[1])
                {
                    sa=sign[1];
                    sb=sign[0];
                }
                Apply_2d_Plane_45(neigh,sa,sb);
            }
        }
        else
        {
            for(int i=0;i<n;++i)
            {
                type_neigh neigh2=neigh;
                if(sign[i]==1)
                {
                    neigh2=neigh.GetNeighbour(dir[i],1);
                }
                if(!Get_Is_Speed_In_Domain(neigh2,dir[i]))
                {
                    neigh2.Speed_GetRef().Set(dir[i],nan(""));
                }
            }
        }
    }
    /**
     * @brief Apply_Div_2d fonction witch use the 2d divergence free condition, to solve one unknow.
     * @param neigh Cell to consider
     * @param dir direction of the unknow.
     * @param sign Witch speed in the direction is the unknow. +1 in the positif side, -1 the negatif side.
     */
    void Apply_Div_2d(type_neigh neigh,int dir,int sign)
    {
        type_neigh n=neigh.GetNeighbour(dir,1);
        type_speed_data_value v=neigh.Speed_GetRef().Get(dir);
        if(sign==-1)
        {
            v=n.Speed_GetRef().Get(dir);
            n=neigh;
        }
        int dir2=1;
        if(dir==1)
        {
            dir2=2;
        }
        type_speed_data_value v2=neigh.Speed_GetRef().Get(dir);
        type_speed_data_value v3=neigh.GetNeighbour(dir2,1).Speed_GetRef().Get(dir);
        type_speed_data_value res=v-sign*m_1_h.Get(dir2)*m_h.Get(dir)*(v3-v2);
        n.Speed_GetRef().Set(dir,res);
    }
    /**
     * @brief Apply_2d_Plane Apply the boundary condition for a 2d Plane.
     * @param neigh first cell in the plan.
     * @param neigh2 second cell in the plan.
     * @param dir direction normal to the plan.
     * @param sign sign of the direction.
     */
    void Apply_2d_Plane(type_neigh neigh,type_neigh neigh2,int dir,int sign)
    {
        Apply_Div_2d(neigh,dir,sign);
        Apply_Div_2d(neigh2,dir,sign);
        int dir2=1;
        if(dir==1)
        {
            dir2=2;
        }
        type_speed_data_value v1=neigh.Speed_GetRef().Get(dir);
        type_speed_data_value v2=neigh2.Speed_GetRef().Get(dir);
        type_speed_data_value v3=neigh2.Speed_GetRef().Get(dir2);
        type_speed_data_value v=-sign*m_1_h.Get(dir2)*m_h.Get(dir)*(v2-v1)+v3;
        type_neigh neigh3=neigh2.GetNeighbour(dir,sign);
        neigh3.Speed_GetRef().Set(dir2,v);
    }
    /**
     * @brief Apply_2d_Plane_45 function that apply the boundary condition for a 45 degree plane in 2d.
     * @param neigh cell in witch the plane pass.
     * @param sa sign of the unknown in the first direction
     * @param sb sign of the unknown in the second direction.
     */
    void Apply_2d_Plane_45(type_neigh neigh,int sa,int sb)
    {
        type_speed_data_value v1=neigh.Speed_GetRef().Get(1);
        type_speed_data_value v2=neigh.Speed_GetRef().Get(2);
        type_neigh n1=neigh.GetNeighbour(1,1);
        type_neigh n2=neigh.GetNeighbour(2,1);
        if(sa==-1)
        {
            v1=neigh.GetNeighbour(1,1).Speed_GetRef().Get(1);
            n1=neigh;
        }
        if(sb==-1)
        {
            v2=neigh.GetNeighbour(2,1).Speed_GetRef().Get(2);
            n2=neigh;
        }
        n1.Speed_GetRef().Set(1,v1);
        n2.Speed_GetRef().Set(2,v2);
    }
    /**
     * @brief apply_set_nan Set nan to speed that are between two air cell.
     * @param neigh Cell to look around for nan.
     */
    void apply_set_nan(type_neigh neigh)
    {
        if(!neigh.CellType_GetRef().GetIsAir())
        {
            return;
        }
        for(int i=1;i<=type_dim;++i)
        {
            for(int s=-1;s<=1;s+=2)
            {
                const type_neigh neigh2=neigh.GetNeighbour(i,s);
                if(neigh2.IsValid())
                {
                    if(neigh2.CellType_GetRef().GetIsAir())
                    {
                        type_neigh neigh3=neigh2;
                        if(s==-1)
                        {
                            neigh3=neigh;
                        }
                        neigh3.Speed_GetRef().Set(i,nan(""));
                    }
                }
                else if(s==-1)
                {
                    neigh.Speed_GetRef().Set(i,nan(""));
                }
            }
        }
    }
    /**
     * @brief Do2d Do the work for the extrapolation for the 2d case.
     */
    void Do2d()
    {
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            apply_set_nan(it.data());
        }
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            int dir[2*type_dim];
            int sign[2*type_dim];
            int n;
            if(IsBoundary(it.data(),dir,sign,n))
            {
                Choose_Boundary_Case_2d(it.data(),dir,sign,n);
            }
        }
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            if(IsBoundary(it.data()))
            {
                apply_nan_extrap(it.data());
            }
        }
    }
    /**
     * @brief apply_nan_extrap Extrapolate in boundary speed witch are nan because
     *  they can't be calculated.
     * @param neigh Cell where we do it.
     */
    void apply_nan_extrap(type_neigh neigh)
    {
        auto key=neigh.GetKey();
        int n=0;
        int tab[2][2*type_dim];
        for(int i=1;i<=type_dim;++i)
        {
            type_speed_data_value v1=neigh.Speed_GetRef().Get(i);
            type_speed_data_value v2=neigh.GetNeighbour(i,1).Speed_GetRef().Get(i);
            if(std::isnan(v1))
            {
                tab[0][n]=i;
                tab[1][n]=0;
                ++n;
            }
            if(std::isnan(v2))
            {
                tab[0][n]=i;
                tab[1][n]=1;
                ++n;
            }
        }
        if(n==0)
        {
            return;
        }
        for(int i=0;i<n;++i)
        {
            int dir=tab[0][i];
            int sign=tab[1][i];
            type_neigh neigh2=neigh;
            if(sign==1)
            {
                neigh2=neigh.GetNeighbour(dir,1);
            }
            type_speed_data_value vtemp=0;
            int nb=0;
            for(int dir2=1;dir2<=type_dim;++dir2)
            {
                for(int s=-1;s<=1;++s)
                {
                    type_speed_data_value add=neigh2.Speed_GetRef().Get(dir);
                    if(!std::isnan(add))
                    {
                        vtemp+=add;
                        ++nb;
                    }
                }
            }
            if(nb!=0)
            {
                vtemp/=nb;
            }
            neigh2.Speed_GetRef().Set(dir,vtemp);
        }
        type_speed_data_value div=0;
        for(int i=1;i<=type_dim;++i)
        {
            type_speed_data_value v1=neigh.Speed_GetRef().Get(i);
            type_speed_data_value v2=neigh.GetNeighbour(i,1).Speed_GetRef().Get(i);
            div+=m_1_h.Get(i)*(v2-v1);
        }
        type_speed_data_value cor=div/n;
        for(int i=0;i<n;++i)
        {
            int dir=tab[0][i];
            int sign=tab[1][i];
            type_neigh neigh2=neigh;
            if(sign==1)
            {
                neigh2=neigh.GetNeighbour(dir,1);
            }
            neigh2.Speed_GetRef().Set(dir,neigh2.Speed_GetRef().Get(dir)-(2*sign-1)*m_h.Get(dir)*cor);
        }
    }

    void Do3d()
    {

    }
};

#endif // ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H
