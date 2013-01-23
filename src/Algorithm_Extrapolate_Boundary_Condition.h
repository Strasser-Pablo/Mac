#ifndef ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H
#define ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H

#include <cmath>
#include <unordered_map>
#include <stack>
using std::nan;

/**
 * @brief Algorithm witch calculate boundary condition from know speed.
 *
 * @tparam Data
 * @tparam Policy class witch need to define method bool Get_Is_Speed_In_Domain(type_neigh,int i)
 * witch indicate if the given speed need to be considered in the computation domain.
 */
template <typename Data,typename Policy>
struct Linear_Solver_Data
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename Policy::type_linear_solver type_linear_solver;
    int* m_offset;
    int* m_indice;
    int m_n;
    type_speed_data_value* m_value;
    type_linear_solver m_solver;
};

template <typename Data,typename Policy>
struct Plane_3d_stack
{
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename Policy::type_linear_solver type_linear_solver;
    int s1;
    int s2;
    int s3;
    type_neigh neigh;
};

template <typename Data,typename Policy>
class Algorithm_Extrapolate_Boundary_Condition_Common : public Policy
{
public:
    using Policy::Get_Is_Speed_In_Domain;
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef Linear_Solver_Data<Data,Policy> type_lin_solver_data;
    typedef Plane_3d_stack<Data,Policy> type_plane3d;
    static const int type_dim=type_Data_Grid::type_key::type_dim;
    const type_spacing_vector &m_1_h;
    const type_spacing_vector &m_h;
    type_Data_Grid& m_grid;
public:
    /**
     * @brief Algorithm_Extrapolate_Boundary_Condition Constructor.
     * @param data Data to use acces to.
     * @param pol Policy to derivate from.
     */
    Algorithm_Extrapolate_Boundary_Condition_Common(Data data, const Policy& pol): Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_h(data.m_data.GetGridData().m_h.GetRef())
    {
    }
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
     * @brief apply_nan_extrap Extrapolate in boundary speed witch are nan because
     *  they can't be calculated.
     * @param neigh Cell where we do it.
     */
    void apply_nan_extrap(type_neigh neigh)
    {
        int n=0;
        int tab[2][2*type_dim];
        for(int i=1;i<=type_dim;++i)
        {
            type_speed_data_value v1=neigh.Speed_GetRef().Get(i);
            const type_neigh neigh_temp=neigh.GetNeighbour(i,1);
            assert(neigh_temp.IsValid());
            type_speed_data_value v2=neigh_temp.Speed_GetRef().Get(i);
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
};

template <typename Data,typename Policy,int Dim>
class Algorithm_Extrapolate_Boundary_Condition_Dim
{
protected:
    Algorithm_Extrapolate_Boundary_Condition_Dim(Data data, const Policy& pol)
    {

    }
};

template <typename Data,typename Policy>
class Algorithm_Extrapolate_Boundary_Condition_Dim<Data,Policy,2> : public Algorithm_Extrapolate_Boundary_Condition_Common<Data,Policy>
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

public:
    /**
     * @brief Do2d Do the work for the extrapolation for the 2d case.
     */
    void Do()
    {
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            this->apply_set_nan(it.data());
        }
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            int dir[2*type_dim];
            int sign[2*type_dim];
            int n;
            if(this->IsBoundary(it.data(),dir,sign,n))
            {
                Choose_Boundary_Case_2d(it.data(),dir,sign,n);
            }
        }
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            if(this->IsBoundary(it.data()))
            {
                this->apply_nan_extrap(it.data());
            }
        }
    }
protected:
    Algorithm_Extrapolate_Boundary_Condition_Dim(Data data, const Policy& pol): Algorithm_Extrapolate_Boundary_Condition_Common<Data,Policy>(data,pol)
    {

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
                this->IsBoundary(neigh2,dirtemp,signtemp,ntemp);
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
                if(!Get_Is_Speed_In_Domain(neigh,dir[0]))
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
        type_speed_data_value v2=neigh.Speed_GetRef().Get(dir2);
        type_speed_data_value v3=neigh.GetNeighbour(dir2,1).Speed_GetRef().Get(dir2);
        type_speed_data_value res=v-sign*this->m_1_h.Get(dir2)*this->m_h.Get(dir)*(v3-v2);
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
        type_speed_data_value v=-sign*this->m_1_h.Get(dir2)*this->m_h.Get(dir)*(v2-v1)+v3;
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
};

template <typename Data,typename Policy>
class Algorithm_Extrapolate_Boundary_Condition_Dim<Data,Policy,3>:public Algorithm_Extrapolate_Boundary_Condition_Common<Data,Policy>
{
    using Policy::Get_Is_Speed_In_Domain;
    typedef typename Data::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_data_value;
    typedef typename type_Data_Grid::iterator iterator;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename Policy::type_linear_solver type_linear_solver;
    typedef Linear_Solver_Data<Data,Policy> type_lin_solver_data;
    typedef Plane_3d_stack<Data,Policy> type_plane3d;
    static const int type_dim=type_Data_Grid::type_key::type_dim;
public:
    void Do()
    {
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            this->apply_set_nan(it.data());
        }
        Initialize();
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            int dir[2*type_dim];
            int sign[2*type_dim];
            int n;
            if(this->IsBoundary(it.data(),dir,sign,n))
            {
                Choose_Boundary_Case_3d(it.data(),dir,sign,n);
            }
        }
        while(!m_stack.empty())
        {
            type_plane3d plane3d=m_stack.top();
            m_stack.pop();
            Apply_3d_Plane_3d(plane3d.neigh,plane3d.s1,plane3d.s2,plane3d.s3);
        }
        for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
        {
            if(this->IsBoundary(it.data()))
            {
                this->apply_nan_extrap(it.data());
            }
        }
    }
protected:
    Algorithm_Extrapolate_Boundary_Condition_Dim(Data data, const Policy& pol):Algorithm_Extrapolate_Boundary_Condition_Common<Data,Policy>(data,pol)
    {

    }
    std::unordered_map<int,type_lin_solver_data> m_solver;
    std::stack<Plane_3d_stack<Data,Policy> > m_stack;
    ~Algorithm_Extrapolate_Boundary_Condition_Dim()
    {
        Initialize();
    }

    int SignToInt(int s1,int s2,int s3)
    {
        int a1=(s1+1)/2;
        int a2=(s2+1)/2;
        int a3=(s3+1)/2;
        return a1+2*a2+4*a3;
    }

    void CreateMatrix(int s1,int s2,int s3)
    {
        int id=SignToInt(s1,s2,s3);
        m_solver[id].m_offset=new int[4];
        m_solver[id].m_indice=new int[9];
        m_solver[id].m_value=new type_speed_data_value[9];
        m_solver[id].m_n=3;
        for(int i=0;i<4;++i)
        {
            m_solver[id].m_offset[i]=3*i;
        }

        for(int i=0;i<9;++i)
        {
            m_solver[id].m_indice[i]=i%3;
        }

        m_solver[id].m_value[0]=-s1*2*this->m_1_h.Get(1)-s1*0.5*this->m_1_h.Get(3);
        m_solver[id].m_value[3]=s2*2*this->m_1_h.Get(2)+s2*0.5*this->m_1_h.Get(3);
        m_solver[id].m_value[6]=-s3*0.5*this->m_1_h.Get(1)+s2*s3*0.5*this->m_1_h.Get(2);
        m_solver[id].m_value[1]=-s1*0.5*this->m_1_h.Get(3)+s1*0.5*this->m_1_h.Get(2);
        m_solver[id].m_value[4]=s2*2*this->m_1_h.Get(2)+s2*0.5*this->m_1_h.Get(2);
        m_solver[id].m_value[7]=-s3*2*this->m_1_h.Get(3)-s3*0.5*this->m_1_h.Get(1);
        m_solver[id].m_value[2]=s1*this->m_1_h.Get(1);
        m_solver[id].m_value[5]=s2*this->m_1_h.Get(2);
        m_solver[id].m_value[8]=s3*this->m_1_h.Get(3);
        m_solver[SignToInt(s1,s2,s3)].m_solver.Solve_Linear_FactorizeMatrice(3,m_solver[id].m_offset,m_solver[id].m_indice,m_solver[id].m_value);
    }
    void SolveMatrix(int s1,int s2,int s3,type_neigh cell)
    {
        if(m_solver.count(SignToInt(s1,s2,s3))==0)
        {
            CreateMatrix(s1,s2,s3);
        }
        type_speed_data_value b[3];
        type_speed_data_value res[3];
        b[0]=0;
        //term 1
        if(s1==1)
        {
            b[0]+=-2*this->m_1_h.Get(1)*cell.Speed_GetRef().Get(1);
        }
        else
        {
            b[0]+=2*this->m_1_h.Get(1)*cell.GetNeighbour(1,1).Speed_GetRef().Get(1);
        }
        //term 2
        if(s2==1)
        {
            b[0]+=2*this->m_1_h.Get(2)*cell.Speed_GetRef().Get(2);
        }
        else
        {
            b[0]+=-2*this->m_1_h.Get(2)*cell.GetNeighbour(2,1).Speed_GetRef().Get(2);
        }
        //term 3
        if(s3==1)
        {
            b[0]+=0.5*this->m_1_h.Get(1)*cell.Speed_GetRef().Get(3);
        }
        else
        {
            b[0]+=-0.5*this->m_1_h.Get(1)*cell.GetNeighbour(3,1).Speed_GetRef().Get(3);
        }
        //term 4-5
        b[0]+=s3*0.5*this->m_1_h.Get(1)*(-cell.GetNeighbour(1,-s1).Speed_GetRef().Get(3)-cell.GetNeighbour(1,-s1).GetNeighbour(3,1).Speed_GetRef().Get(3));
        //term 6
        if(s1==1)
        {
            b[0]+=0.5*this->m_1_h.Get(3)*cell.Speed_GetRef().Get(1);
        }
        else
        {
            b[0]+=-0.5*this->m_1_h.Get(3)*cell.GetNeighbour(1,1).Speed_GetRef().Get(1);
        }
        //term 7-8
        b[0]+=s1*0.5*this->m_1_h.Get(3)*(-cell.GetNeighbour(3,-s3).Speed_GetRef().Get(1)-cell.GetNeighbour(3,-s3).GetNeighbour(1,1).Speed_GetRef().Get(1));

        //term 9
        if(s3==1)
        {
            b[0]+=-0.5*this->m_1_h.Get(2)*cell.Speed_GetRef().Get(3);
        }
        else
        {
            b[0]+=0.5*this->m_1_h.Get(2)*cell.GetNeighbour(3,1).Speed_GetRef().Get(3);
        }

        //term 10-11
        b[0]+=s3*0.5*this->m_1_h.Get(2)*(cell.GetNeighbour(2,-s2).Speed_GetRef().Get(3)+cell.GetNeighbour(2,-s2).GetNeighbour(3,1).Speed_GetRef().Get(3));

        //term 12
        if(s2==1)
        {
            b[0]+=-0.5*this->m_1_h.Get(3)*cell.Speed_GetRef().Get(2);
        }
        else
        {
            b[0]+=0.5*this->m_1_h.Get(3)*cell.GetNeighbour(2,1).Speed_GetRef().Get(2);
        }
        //term 13-14
        b[0]+=s2*0.5*this->m_1_h.Get(3)*(cell.GetNeighbour(3,-s3).Speed_GetRef().Get(2)+cell.GetNeighbour(3,-s3).GetNeighbour(2,1).Speed_GetRef().Get(2));

        b[1]=0;
        //term 1
        if(s3==1)
        {
            b[1]+=-2*this->m_1_h.Get(3)*cell.Speed_GetRef().Get(3);
        }
        else
        {
            b[1]+=2*this->m_1_h.Get(3)*cell.GetNeighbour(3,-s3).Speed_GetRef().Get(3);
        }
        //term 2
        if(s2==1)
        {
            b[1]+=2*this->m_1_h.Get(2)*cell.Speed_GetRef().Get(2);
        }
        else
        {
            b[1]+=-2*this->m_1_h.Get(2)*cell.GetNeighbour(2,1).Speed_GetRef().Get(2);
        }
        //term 3
        if(s3==1)
        {
            b[1]+=0.5*this->m_1_h.Get(1)*cell.Speed_GetRef().Get(3);
        }
        else
        {
            b[1]+=-0.5*this->m_1_h.Get(1)*cell.GetNeighbour(3,1).Speed_GetRef().Get(3);
        }
        //term 4-5
        b[1]+=s3*0.5*this->m_1_h.Get(1)*(-cell.GetNeighbour(1,-s1).Speed_GetRef().Get(3)-cell.GetNeighbour(1,-s1).GetNeighbour(3,1).Speed_GetRef().Get(3));

        //term 6
        if(s1==1)
        {
            b[1]+=0.5*this->m_1_h.Get(3)*cell.Speed_GetRef().Get(1);
        }
        else
        {
            b[1]+=-0.5*this->m_1_h.Get(3)*cell.GetNeighbour(1,1).Speed_GetRef().Get(1);
        }
        //term 7-8
        b[1]+=s1*0.5*this->m_1_h.Get(3)*(-cell.GetNeighbour(3,-s3).Speed_GetRef().Get(1)-cell.GetNeighbour(3,-s3).GetNeighbour(1,1).Speed_GetRef().Get(1));

        //term 9
        if(s1==1)
        {
            b[1]+=-0.5*this->m_1_h.Get(2)*cell.Speed_GetRef().Get(1);
        }
        else
        {
            b[1]+=-0.5*this->m_1_h.Get(2)*cell.GetNeighbour(1,1).Speed_GetRef().Get(1);
        }

        //term 10-11
        b[1]+=s1*0.5*this->m_1_h.Get(2)*(cell.GetNeighbour(2,-s2).Speed_GetRef().Get(1)+cell.GetNeighbour(2,-s2).GetNeighbour(1,1).Speed_GetRef().Get(1));

        //term 12
        if(s2==1)
        {
            b[1]+=-0.5*this->m_1_h.Get(1)*cell.Speed_GetRef().Get(2);
        }
        else
        {
            b[1]+=0.5*this->m_1_h.Get(1)*cell.GetNeighbour(2,1).Speed_GetRef().Get(2);
        }
        //term 13-14
        b[1]+=s2*0.5*this->m_1_h.Get(1)*(cell.GetNeighbour(1,-s1).Speed_GetRef().Get(2)+cell.GetNeighbour(1,-s1).GetNeighbour(2,1).Speed_GetRef().Get(2));

        b[2]=0;
        if(s1==1)
        {
            b[2]+=this->m_1_h.Get(1)*cell.Speed_GetRef().Get(1);
        }
        else
        {
            b[2]+=-this->m_1_h.Get(1)*cell.GetNeighbour(1,1).Speed_GetRef().Get(1);
        }

        if(s2==1)
        {
            b[2]+=this->m_1_h.Get(2)*cell.Speed_GetRef().Get(2);
        }
        else
        {
            b[2]+=-this->m_1_h.Get(2)*cell.GetNeighbour(2,1).Speed_GetRef().Get(2);
        }

        if(s3==1)
        {
            b[2]+=this->m_1_h.Get(3)*cell.Speed_GetRef().Get(3);
        }
        else
        {
            b[2]+=-this->m_1_h.Get(3)*cell.GetNeighbour(3,1).Speed_GetRef().Get(3);
        }
        int id=SignToInt(s1,s2,s3);
        m_solver[id].m_solver.Solve_Linear(m_solver[id].m_n,m_solver[id].m_offset,m_solver[id].m_indice,m_solver[id].m_value,b,res);
        if(s1==1)
        {
            cell.GetNeighbour(1,1).Speed_GetRef().Set(1,res[0]);
        }
        else
        {
            cell.Speed_GetRef().Set(1,res[0]);
        }
        if(s2==1)
        {
            cell.GetNeighbour(2,1).Speed_GetRef().Set(2,res[1]);
        }
        else
        {
            cell.Speed_GetRef().Set(2,res[1]);
        }
        if(s3==1)
        {
            cell.GetNeighbour(3,1).Speed_GetRef().Set(3,res[2]);
        }
        else
        {
            cell.Speed_GetRef().Set(3,res[2]);
        }
    }
    void Initialize()
    {
        for(typename std::unordered_map<int,type_lin_solver_data>::iterator it=m_solver.begin();it!=m_solver.end();++it)
        {
            it->second.m_solver.Solve_Linear_Clean();
            delete[] it->second.m_value;
            delete[] it->second.m_indice;
            delete[] it->second.m_offset;
        }
        m_solver.clear();
    }

    void Choose_Boundary_Case_3d(type_neigh neigh,int  dir[2*type_dim],int  sign[2*type_dim],int &n)
    {
        if(n==1)
        {
            Apply_Div_3d(neigh,dir[0],sign[0]);

            for(int dir2=1;dir2<=type_dim;++dir2)
            {
                if(dir2==dir[0])
                {
                    continue;
                }
                bool b=true;
                for(int i=-1;i<=1;i+=2)
                {
                    type_neigh neigh2=neigh.GetNeighbour(dir2,i);
                    int  dirtemp[2*type_dim];
                    int  signtemp[2*type_dim];
                    int ntemp;
                    this->IsBoundary(neigh2,dirtemp,signtemp,ntemp);
                    if(ntemp==1)
                    {
                        Apply_Div_3d(neigh2,dirtemp[0],signtemp[0]);
                    }
                    if(ntemp==1&&dirtemp[0]==dir[0])
                    {
                        if(i<0)
                        {
                            Apply_3d_Plane(neigh2,neigh,dir[0],sign[0],dir2);
                        }
                        else if(i>0)
                        {
                            Apply_3d_Plane(neigh,neigh2,dir[0],sign[0],dir2);
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
                    if(!Get_Is_Speed_In_Domain(neigh,dir[0]))
                    {
                        neigh3.Speed_GetRef().Set(dir[0],nan(""));
                    }
                }
            }
        }
        else if(n==2)
        {
            if(dir[0]!=dir[1])
            {
                int sa=sign[0];
                int sb=sign[1];
                int dira=dir[0];
                int dirb=dir[1];
                Apply_3d_Plane_45(neigh,sa,dira,sb,dirb);
            }
        }
        else if(n==3)
        {
            int s1=0;
            int s2=0;
            int s3=0;

            for(int i=0;i<n;++i)
            {
                if(dir[i]==1)
                {
                    s1=sign[i];
                    break;
                }
            }
            for(int i=0;i<n;++i)
            {
                if(dir[i]==2)
                {
                    s2=sign[i];
                    break;
                }
            }
            for(int i=0;i<n;++i)
            {
                if(dir[i]==3)
                {
                    s3=sign[i];
                    break;
                }
            }
            if(s1!=0 && s2!=0 && s3!=0)
            {
                type_plane3d plane3d;
                plane3d.s1=s1;
                plane3d.s2=s2;
                plane3d.s3=s3;
                plane3d.neigh=neigh;
                m_stack.push(plane3d);
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
    void Apply_3d_Plane(type_neigh neigh,type_neigh neigh2,int dir,int sign,int dir2)
    {
        type_speed_data_value v1=neigh.Speed_GetRef().Get(dir);
        type_speed_data_value v2=neigh2.Speed_GetRef().Get(dir);
        type_speed_data_value v3=neigh2.Speed_GetRef().Get(dir2);
        type_speed_data_value v=-sign*this->m_1_h.Get(dir2)*this->m_h.Get(dir)*(v2-v1)+v3;
        type_neigh neigh3=neigh2.GetNeighbour(dir,sign);
        neigh3.Speed_GetRef().Set(dir2,v);
    }
    void Apply_Div_3d(type_neigh neigh,int dir,int sign)
    {
        type_neigh n=neigh.GetNeighbour(dir,1);
        type_speed_data_value v=neigh.Speed_GetRef().Get(dir);
        if(sign==-1)
        {
            v=n.Speed_GetRef().Get(dir);
            n=neigh;
        }
        type_speed_data_value res=0;
        for(int dir2=dir;dir2<=type_dim;++dir2)
        {
            type_speed_data_value v2=neigh.Speed_GetRef().Get(dir2);
            type_speed_data_value v3=neigh.GetNeighbour(dir2,1).Speed_GetRef().Get(dir2);
            res=this->m_1_h.Get(dir2)*(v3-v2);
        }
        res=v-sign*res*this->m_h.Get(dir);
        n.Speed_GetRef().Set(dir,res);
    }

    void Apply_3d_Plane_45(type_neigh neigh,int sa,int dira,int sb,int dirb)
    {
        type_speed_data_value v1=neigh.Speed_GetRef().Get(dira);
        type_speed_data_value v2=neigh.Speed_GetRef().Get(dirb);
        type_neigh n1=neigh.GetNeighbour(dira,1);
        type_neigh n2=neigh.GetNeighbour(dirb,1);
        if(sa==-1)
        {
            v1=neigh.GetNeighbour(dira,1).Speed_GetRef().Get(dira);
            n1=neigh;
        }
        if(sb==-1)
        {
            v2=neigh.GetNeighbour(dirb,1).Speed_GetRef().Get(dirb);
            n2=neigh;
        }
        n1.Speed_GetRef().Set(dira,v1);
        n2.Speed_GetRef().Set(dirb,v2);
    }
    void Apply_3d_Plane_3d(type_neigh neigh,int s1,int s2,int s3)
    {
        SolveMatrix(s1,s2,s3,neigh);
    }
};

template <typename Data,typename Policy>
class Algorithm_Extrapolate_Boundary_Condition : public Algorithm_Extrapolate_Boundary_Condition_Dim<Data,Policy,Data::type_data_struct::type_Data_Grid::type_key::type_dim>
{
public:
    Algorithm_Extrapolate_Boundary_Condition(Data data, const Policy& pol): Algorithm_Extrapolate_Boundary_Condition_Dim<Data,Policy,Data::type_data_struct::type_Data_Grid::type_key::type_dim>(data,pol)
    {
    }
};

#endif // ALGORITHM_EXTRAPOLATE_BOUNDARY_CONDITION_H
