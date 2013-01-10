#ifndef ALGORITHMS_SOLVE_PRESSURE_DIRICHLET_H
#define ALGORITHMS_SOLVE_PRESSURE_DIRICHLET_H

#include <cmath>
#include <map>
#include <deque>
#include <sys/times.h>

using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Solve_Pressure_Dirichlet: public Policy
{
    using Policy::Solve_Linear;
    using Policy::Get_Divergence;
    using Policy::Get_Gradiant;
    using Policy::Get_Is_Von_Neumann_Boundary;
    using Policy::Get_Pressure_If_Correction;
    using Policy::Solve_Linear_Clean;
    using Policy::Solve_Linear_FactorizeMatrice;
    using Policy::GetIsDirichletBoundary;
    using Policy::GetIsDirichletBoundaryNeighbour;
    using Policy::GetDirichletSumBoundaryPressure;
    using Policy::GetDirichletBoundaryPressure;
    typedef typename DataType::type_data_struct type_data;
    typedef typename type_data::type_Data_Grid type_grid;
    typedef typename type_grid::type_data type_data_data;
    typedef typename type_data_data::type_pressure::type_pressure type_pressure;
    typedef typename type_grid::type_offset type_neigh;
    typedef typename type_data_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_value;
    typedef typename type_speed::type_speed::type_vector type_speed_vector;
    typedef typename type_grid::type_spacing_vector type_spacing_vector;
    typedef typename type_grid::iterator iterator;
    typedef typename type_data::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    static const int type_dim=type_speed::type_dim;
    type_grid& m_grid;
    const type_spacing_vector& m_1_h;
    int m_n;
    int* m_offset;
    int* m_indice;
    type_speed_value* m_value;
    public:
    Algorithms_Solve_Pressure_Dirichlet(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv())
    {
    }
    void Init_Iteration()
    {
        struct tms t1;
        struct tms t2;
        double conv=double(sysconf(_SC_CLK_TCK));
        long t_deb=times(&t1);

        // Upper bound of memory usage.
        m_n=m_grid.size_upper();
        int nEntry=(2*type_dim+1)*m_grid.size_upper();
        m_offset=new int[m_n+1];
        m_indice=new int[nEntry];
        m_value=new type_speed_value[nEntry];

        //Set every layer to empty.
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            it.data().Id_Cell_GetRef().SetLayerEmpty();
        }
        m_offset[0]=0;
        int lay=0;
        int lay_cur;
        int off=0;
        deque<type_neigh>next;
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            type_neigh  neigh;
            if(!it.data().Id_Cell_GetRef().GetIsLayerEmpty())
            {
                continue;
            }
            next.push_back(it.data());
            while(!next.empty())
            {
                type_neigh next_neigh=next.front();
                next.pop_front();
                //For every cell in domain. Where we assign a unic number.
                if(next_neigh.CellType_GetRef().GetIsInDomain())
                {
                    //Cell has no number assign one.
                    if(next_neigh.Id_Cell_GetRef().GetIsLayerEmpty())
                    {
                        next_neigh.Id_Cell_GetRef().SetLayer(lay);
                        lay_cur=lay;
                        ++lay;
                    }

                    //We have a number, use it.
                    else
                    {
                        lay_cur=next_neigh.Id_Cell_GetRef().GetLayer();
                    }

                    //Ordered map to store indice value relation.
                    map<int,type_speed_value> m_map;
                    typedef typename map<int,type_speed_value>::value_type type_pair;
                    typedef typename map<int,type_speed_value>::const_iterator const_iterator;
                    type_speed_value temp_diag_value=0;
                    //For every direction and every sign.
                    for(int i=1;i<=type_dim;++i)
                    {
                        for(int s=-1;s<=1;s+=2)
                        {
                            temp_diag_value-=pow(m_1_h.Get(i),2);
                            int lay_cur2;
                            neigh=next_neigh.GetNeighbour(i,s);
                            //Test if we have a neighbour.
                            if(neigh.IsValid())
                            {
                                if(Get_Is_Von_Neumann_Boundary(next_neigh,i,s))
                                {
                                    temp_diag_value+=pow(m_1_h.Get(i),2);
                                }
                                //NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
                                else if(neigh.CellType_GetRef().GetIsInDomain())
                                {
                                    if(neigh.Id_Cell_GetRef().GetIsLayerEmpty())
                                    {
                                        neigh.Id_Cell_GetRef().SetLayer(lay);
                                        lay_cur2=lay;
                                        ++lay;
                                        next.push_back(neigh);
                                    }
                                    else
                                    {
                                        lay_cur2=neigh.Id_Cell_GetRef().GetLayer();
                                    }
                                    m_map.insert(type_pair(lay_cur2,pow(m_1_h.Get(i),2)));
                                }
                            }
                        }
                    }
                    //Insert the diagonal value in the map.
                    m_map.insert(type_pair(lay_cur,temp_diag_value));
                    //Insert the value of the map. The map is ordered.
                    for(const_iterator it=m_map.begin();it!=m_map.end();++it)
                    {
                        m_value[off]=it->second;
                        m_indice[off]=it->first;
                        ++off;
                    }
                    //Add current offset.
                    m_offset[lay_cur+1]=off;
                }
            };
        }
        m_n=lay;
        Solve_Linear_FactorizeMatrice(m_n,m_offset,m_indice,m_value);

        long t_end=times(&t2);
        cout<<"real Pressure_Prepare+Factorize "<<(t_end-t_deb)/conv<<endl;
        cout<<"real Pressure_Prepare+Factorize "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
    }
    void End_Iteration()
    {
        delete[] m_offset;
        delete[] m_indice;
        delete[] m_value;
        m_offset=nullptr;
        m_indice=nullptr;
        m_value=nullptr;
        Solve_Linear_Clean();
    }
    void Divergence_Projection()
    {
        type_speed_value* b=new type_speed_value[m_n];
        type_speed_value* res=new type_speed_value[m_n];
        // Set b to divergence.
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            int lay_cur;
            if(it.data().CellType_GetRef().GetIsInDomain())
            {
                lay_cur=it.data().Id_Cell_GetRef().GetLayer();
                b[lay_cur]=Get_Divergence(it.data()).Get();
                if(this->GetIsDirichletBoundaryNeighbour(it.data()))
                {
                    b[lay_cur]-=this->GetDirichletSumBoundaryPressure(it.data());
                }
            }
        }
        // Solve the linear system.
        Solve_Linear(m_n,m_offset,m_indice,m_value,b,res);
        // Set the pressure of cell from the result.
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            int lay_cur;
            if(it.data().CellType_GetRef().GetIsInDomain())
            {
                lay_cur=it.data().Id_Cell_GetRef().GetLayer();
                it.data().Pressure_GetRef().Pressure_Set(type_pressure(res[lay_cur]));
            }
            else if(this->GetIsDirichletBoundary(it.data()))
            {
                it.data().Pressure_GetRef().Pressure_Set(type_pressure(this->GetDirichletBoundaryPressure(it.data())));
            }
            else
            {
                it.data().Pressure_GetRef().Pressure_Set(type_pressure(0));
            }
        }
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            for(int i=1;i<=type_dim;++i)
            {
                if(Get_Pressure_If_Correction(it.data(),i))
                {
                    it.data().Speed_GetRef().Set(i,it.data().Speed_GetRef().Get(i)-Get_Gradiant(it.data(),i));
                }
            }
        }
        for(iterator it=m_grid.begin();it!=m_grid.end();++it)
        {
            if(it.data().CellType_GetRef().GetIsInDomain())
            {
                type_speed_value div=Get_Divergence(it.data()).Get();
                if(abs(div)>0.0000000001)
                {
                    cout<<"key "<<it.key()<<endl;
                    cout<<"div "<<Get_Divergence(it.data()).Get()<<endl;
                }
            }
        }
        delete[] b;
        delete[] res;
    }
};

#endif // ALGORITHMS_SOLVE_PRESSURE_DIRICHLET_H
