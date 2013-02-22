#pragma STDC FENV_ACCESS ON
#undef SPLIT
#define VISCOSITY
//Vector
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"

//HashTable+Neighbour
#include "../src/Neighbour_List_Empty.h"
#include "../src/Neighbour_List_Key.h"
#include "../src/ChunkHashTable.h"
#include "../src/Hook_Neighbour_List_key.h"
#include "../src/Hook_Neighbour_List_Chunk.h"

//Data_Chunk
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Id_Cell.h"
#include "../src/Data_Chunk_Speed_Von_Neumann.h"
#include "../src/Data_Chunk_Depth.h"

//Offset
#include "../src/Offset.h"
#include "../src/Offset_Key.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_Id_Cell.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Offset_Base_Speed_Von_Neumann.h"
#include "../src/Offset_Base_Depth.h"

//DataBase
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"

//Data GRID
#include "../src/Data_Grid_Data.h"
#include "../src/Data_Grid_Table.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Data_Viscosity.h"
#include "../src/Data_CellType_Interface_Constant.h"

//Data CellType
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres.h"
#include "../src/Data_CellType_Domain_Fluid_Without_0_Pres.h"
#include "../src/Data_Grid_CellType_To_Grid_CellType.h"
#include "../src/Data_CellType_Speed_Von_Neumann.h"

//Data Grid Speed
#include "../src/Data_Grid_Speed.h"

//Data Grid Pressure
#include "../src/Data_Grid_Pressure.h"

//Data Grid Layer
#include "../src/Data_Grid_Layer.h"
#include "../src/Data_Grid_Layer_Empty.h"

#include "../src/Data_Grid_Depth.h"
#include "../src/Data_Grid_Depth_Empty.h"

//Data Topology
#include "../src/Data_Topology.h"

//Particle
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"

//Data Timming
#include "../src/Data_Timing.h"
#include "../src/Data_Timing_Time.h"

//Miscellanus
#include "../src/Empty.h"
//Datas
#include "../src/Datas.h"
#include "../src/DataRef.h"

//Policies
#include "../src/Policies.h"

//Algorithms
#include "../src/Algorithms.h"
#include "../src/Algorithms_After.h"
#include "../src/Algorithms_After_From_Algorithms.h"

//Policy
#include "../src/Policy_Layer_Max.h"
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Policy_CheckDT.h"
#include "../src/Policy_Gravity.h"
#include "../src/Policy_Laplacian.h"
#include "../src/Policy_Laplacian_Speed.h"
#include "../src/Policy_Viscosity_Apply_If.h"
#include "../src/Policy_Solve_Linear_Umfpack.h"
#include "../src/Policy_Divergence.h"
#include "../src/Policy_Gradiant.h"
#include "../src/Policy_Von_Neumann_Boundary.h"
#include "../src/Policy_Von_Neumann_Boundary_Data.h"
#include "../src/Policy_Add_Particle_Cube.h"
#include "../src/Policy_Is_Inbound_Filling_Layer_CellType.h"
#include "../src/Policy_Advance_ODE_RungeKutta.h"
#include "../src/Policy_Speed_Interpolation_Linear_Symmetric.h"
#include "../src/Policy_Output_Grid_Speed_ID.h"
#include "../src/Policy_Output_Grid_Pressure_ID.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Animation.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Upwind_1_Order.h"
#include "../src/Policy_Convection_Center.h"
#include "../src/Policy_Convection_Apply_If.h"
#include "../src/Policy_Pressure_If_Correction.h"
#include "../src/Policy_Is_In_Domain_Speed.h"
#include "../src/Policy_Wind.h"
#include "../src/Policy_Move_Particle.h"
#include "../src/Policy_Depth.h"
#include "../src/Policy_Dirichlet_Boundary.h"
/// To add Convection

//Algorithms

//Const
#include "../src/Algorithms_Speed_Constant_Mirror.h"
#include "../src/Algorithms_Extrapolate.h"
#include "../src/Algorithms_Extrapolate_Nan.h"
#include "../src/Algorithm_Extrapolate_Boundary_Condition.h"
// Initialisation
#include "../src/Algorithms_Fluid_To_Layer.h"
#include "../src/Algorithms_Initialize_MacCell.h"
#include "../src/Algorithms_Calculate_Time_Step.h"
#include "../src/Algorithms_Update_CellType_Layer.h"
#include "../src/Algorithms_Inflow_To_Const.h"
#include "../src/Algorithms_Solid_To_Const.h"
#include "../src/Algorithms_Layer_Initial_With_Particle.h"
#include "../src/Algorithms_Delete_MacCell.h"
#include "../src/Algorithms_Accel_To_Speed.h"
#include "../src/Algorithms_Initialize_Layer_And_Depth.h"
#include "../src/Algorithms_Update_CellType_Layer_Depth.h"
#include "../src/Algorithms_Layer_Initial_With_Particle_Depth.h"
#include "../src/Algorithms_Create_Fluid_Particle_Depth.h"
#include "../src/Algorithms_Create_Interior_Depth.h"

// Solve Grid
#include "../src/Algorithms_Speed_Repeat_Constant.h"
#include "../src/Algorithms_Gravity.h"
#include "../src/Algorithms_Viscosity.h"
#include "../src/Algorithms_Solve_Pressure_Fixed_Neumann.h"
#include "../src/Algorithms_Solve_Pressure_Empty.h"
#include "../src/Algorithms_Solve_Pressure.h"
#include "../src/Algorithms_Solve_Pressure_Pyamg.h"
#include "../src/Algorithms_Convection.h"
#include "../src/Algorithms_Move_Particles.h"
#include "../src/Algorithms_Solve_Pressure_Force.h"
#include "../src/Algorithms_Do_Pressure.h"
#include "../src/Algorithms_Solve_Pressure_Dirichlet.h"
#include "../src/Algorithmes_Solve_Pressure_Dirichlet_Pyamg.h"

//Integrator
#include "../src/Algorithms_Euler.h"
#include "../src/Algorithms_RungeKutta.h"
#include "../src/Algorithms_RungeKutta_Force.h"
#include "../src/Algorithms_Euler_Force.h"
#include "../src/Algorithms_RungeKutta_RK2.h"
#include "../src/Algorithms_RungeKutta_RK2_TVD.h"
#include "../src/Algorithms_RungeKutta_all.h"

// Output
#include "../src/Algorithms_Output_Speed_Pressure.h"
#include "../src/Algorithms_Output.h"

#include <sys/times.h>
#include <stdlib.h>

#include <bitset>

#include <stdexcept>

#include <cfenv>

using namespace std;
/*
template <typename Data,typename Policy>
class Algorithm_Init_Perturbation : public Policy
{
    typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_key type_key;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_value;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    typedef typename type_Data_Grid::iterator iterator;
    static const int type_dim=type_Data_Grid::type_key::type_dim;
    type_Data_Grid& m_grid;
    const type_spacing_vector &m_1_h;
    const type_spacing_vector &m_h;
    type_Time_Type& m_t;
    type_Time_Type& m_dt;
    type_speed_value m_speedx;
    type_speed_value m_epsit;
    type_speed_value m_epsmax;
    int m_y;
    type_speed_value Rand()
    {
        return (rand()%200000)*1./100000.-1;
    }

public:
    Algorithm_Init_Perturbation(Data data, const Policy& pol,type_speed_value speedx,type_speed_value epsit,type_speed_value epsmax,int ymax): Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_t(data.m_data.GetTimingData().m_t),m_dt(data.m_data.GetTimingData().m_dt)
      ,m_speedx(speedx),m_epsit(epsit),m_epsmax(epsmax),m_y(ymax)
    {
        srand(1);
    }
    void Do()
    {
        type_key v;
        v.Set(1,0);
        for(int i=0;i<m_y;++i)
        {
            v.Set(2,i);
            type_speed_value v10=m_grid[v].Speed_GetRef().Get(1);
            type_speed_value v20=m_grid[v].Speed_GetRef().Get(2);
            type_speed_value eps;
            do{
                eps=m_epsit*m_dt*Rand();
            }while(abs(v10+eps-m_speedx)>m_epsmax);
            type_speed_value v1=v10+eps;

            do{
                eps=m_epsit*m_dt*Rand();
            }while(abs(v20+eps)>m_epsmax);
            type_speed_value v2=v20+eps;

            m_grid[v].Speed_GetRef().Set(1,v1,true);
            m_grid[v].Speed_GetRef().Set(2,v2,true);

        }
        v.Set(2,m_y);
        type_speed_value v20=m_grid[v].Speed_GetRef().Get(2);
        type_speed_value eps;

        do{
            eps=m_epsit*m_dt*Rand();
        }while(abs(v20+eps)>m_epsmax);
        type_speed_value v2=v20+eps;
        m_grid[v].Speed_GetRef().Set(2,v2,true);
    }
};
*/

int main()
{
    feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
    const int DIM=3;
    const int NBSpeed=3;
    //	const int NBSpeed=1;
    //	const int NBSpeed=2;
    typedef double type_data_value;
    const int N=2;
    const int NStock=pow(N,DIM);
    typedef Data_Base_Dim_Type<double,DIM> DataBase0;
    DataBase0 base0;
    typedef Data_Staggered_Left<DataBase0> DataBase;
    DataBase base(base0);
    typedef typename DataBase::type_data_value type_data_value;
    typedef Data_Grid_Layer<int> type_layer;
    type_layer layer;
    typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
    type_empt_lay m_empt_lay(layer);
    m_empt_lay.SetLayerEmpty();

    typedef Data_Grid_Layer<int> type_id;
    type_id m_id;
    typedef Data_Grid_Layer_Empty<type_id> type_empt_id;
    type_empt_id m_empt_id(m_id);
    m_empt_id.SetLayerEmpty();

    typedef bitset<DIM> type_const;
    type_const m_const;
    typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
    type_grid_speed m_grid_speed(m_const);

    typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
    type_grid_pressure m_grid_pressure;

    typedef Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> type_grid_celltype;
    type_grid_celltype m_grid_celltype;
    Inversible_Value<type_data_value> rho_air(1);
    Inversible_Value<type_data_value> rho_fluid(1000);
    m_grid_celltype.SetRhoAir(rho_air);
    m_grid_celltype.SetRhoFluid(rho_fluid);

    typedef Data_Grid_Depth<int> type_depth;
    type_depth depth;
    typedef Data_Grid_Depth_Empty<type_depth> type_empt_depth;
    type_empt_depth m_empt_depth(depth);

    typedef Data_CellType_Domain_Fluid_Without_0_Pres<type_grid_celltype> type_cell_type;
    type_cell_type m_celltype(m_grid_celltype);

    typedef Data_Grid_CellType_To_Grid_CellType<type_cell_type> type_cell_grid_celltype;
    type_cell_grid_celltype m_cell_grid_celltype(m_celltype);

    typedef Data_CellType_Speed_Von_Neumann<DataBase> type_speed_von_neumann;
    type_speed_von_neumann m_speed_von_neumann;

    typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
    type_chunk_layer m_chunk_layer(m_empt_lay);

    typedef Data_Chunk_Id_Cell<type_empt_id,NStock> type_chunk_id;
    type_chunk_id m_chunk_id(m_empt_id);

    typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
    type_bool_array m_bool_array;

    typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
    type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

    typedef Data_Chunk_Depth<type_empt_depth,NStock> type_chunk_depth;
    type_chunk_depth m_chunk_depth(m_empt_depth);

    typedef Data_Chunk_Speed<type_grid_speed,NBSpeed,1,NStock> type_chunk_speed;
    type_chunk_speed m_chunk_speed(m_grid_speed);

    typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
    type_chunk_pressure m_chunk_pressure(m_grid_pressure);

    typedef Data_Chunk_Speed_Von_Neumann<type_speed_von_neumann,NStock> type_chunk_speed_von_neumann;
    type_chunk_speed_von_neumann m_chunk_speed_von_neumann(m_speed_von_neumann);

    typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_depth,type_chunk_id,type_chunk_celltype,type_chunk_speed,type_chunk_pressure,type_chunk_speed_von_neumann> type_chunk;
    type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_depth,m_chunk_id,m_chunk_celltype,m_chunk_speed,m_chunk_pressure,m_chunk_speed_von_neumann);

    typedef Physvector<DIM,int> vect;

    typedef Neighbour_List_Key<vect,type_chunk> type_neigh_key;
    type_neigh_key m_neigh_key(m_chunk);
    typedef Neighbour_List_Empty<DIM,type_neigh_key> type_neigh;
    type_neigh m_neigh(m_neigh_key);

    typedef Offset<int,DIM,N> type_off;
    typedef Offset_Base<type_off,type_neigh> type_off_base;
    typedef Offset_Key<vect,type_off_base> type_off_key;
    typedef Offset_Base_Layer<type_empt_lay,type_off_key> type_off_base_layer;
    typedef Offset_Base_Depth<type_empt_depth,type_off_base_layer> type_off_base_depth;
    typedef Offset_Base_Id_Cell<type_empt_id,type_off_base_depth> type_off_base_id;
    typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_id> type_off_base_celltype;
    typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
    typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
    typedef Offset_Base_Speed_Von_Neumann<type_speed_von_neumann,type_off_base_pressure> type_off_base_speed_von_neumann;
    typedef Offset_Base_Neighbour<type_off_base_speed_von_neumann> type_off_base_neighbour;

    typedef Physvector<DIM,double> vectdouble;
    typedef HashPhysvector<DIM,int> Hash;
    Hash hash;
    typedef ChunkHashTable<Hook_Neighbour_List_Key,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
    type_chunk_table m_chunk_table(m_neigh,hash);

    typedef Data_Viscosity<type_chunk_table> type_data_viscosity;
    type_data_viscosity m_data_viscosity(m_chunk_table);
#ifndef VISCOSITY
    m_data_viscosity.m_viscosity=0;
#else
    m_data_viscosity.m_viscosity=1.307e-6;
    //m_data_viscosity.m_viscosity=0;
#endif
    typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value> > type_data_grid;
    type_data_grid m_data_grid(m_data_viscosity);
    Physvector<DIM,type_data_value> h;
    h.Set(1,0.0004);
    h.Set(2,0.0004);
    h.Set(3,0.0004);
    m_data_grid.m_h.Set(h);
    typedef Data_Staggered_Left<type_data_grid> type_data_stag_left;
    type_data_stag_left m_data_stag_left(m_data_grid);
    typedef Data_CellType_Interface_Constant<type_data_stag_left> type_interface_constant;
    type_interface_constant m_type_interface_constant(m_data_stag_left);
    typedef Data_Grid_Data<type_interface_constant,DataBase> type_grid_data;
    type_grid_data m_grid_data(m_type_interface_constant,base);

    // Data Particle
    typedef Data_Particle<DataBase,NBSpeed> type_particle;
    typedef Data_Particles_List<type_particle,DataBase> type_particles;
    type_particles particles(base);
    typedef Data_Topology<type_particles,type_grid_data> type_topology;
    type_topology m_topology(particles,m_grid_data);

    // Data Timming
    typedef Data_Timing_Time<type_data_value> type_time;
    type_time m_time;
    m_time.m_t=0;
    m_time.m_factor=0.5;
    typedef Data_Timing<type_time,type_topology> type_timing;
    type_timing m_timing(m_time,m_topology);

    //Data Ref
    typedef DataRef<type_timing> type_data_ref;
    type_data_ref m_data_ref(m_timing);

    //Initial Data

    Physvector<DIM,type_data_value> speed;
    type_data_value val_speed=1.0;

    int ymax=50;
    bool breload=false;
    int ireload=0;
    for(int y=0;y<ymax;++y)
    {
        for(int z=0;z<ymax;++z)
        {
        vect v;
        speed.Set(1,val_speed);
        speed.Set(2,0.0);
        speed.Set(3,0.0);
        v.Set(1,0);
        v.Set(2,y);
        v.Set(3,z);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetInflow();
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(3);

        speed.Set(1,val_speed);
        speed.Set(2,0.0);
        speed.Set(3,0.0);

        v.Set(1,1);
        v.Set(2,y);
        v.Set(3,z);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,y);
        v.Set(3,z);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
        }
        vect v;
        v.Set(1,0);
        v.Set(2,y);
        v.Set(3,ymax);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(3);

        v.Set(1,0);
        v.Set(2,y);
        v.Set(3,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
    }
    for(int z=0;z<ymax;++z)
    {
    vect v;
    v.Set(1,0);
    v.Set(2,ymax);
    v.Set(3,z);
    m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
    m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
    m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);

    v.Set(1,0);
    v.Set(2,-1);
    v.Set(3,z);
    m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
    m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
    }

    //Policy Init
    typedef Policy_Layer_Max<type_data_ref> type_pol_layer;
    type_pol_layer m_pol_layer(10);
    typedef Policy_Particle_To_Key<type_data_ref> type_pol_part_to_key;
    type_pol_part_to_key m_pol_part_to_key(m_data_ref);
    typedef Policy_CheckDT<type_data_ref> type_pol_check_dt;
    type_pol_check_dt m_pol_check_dt(0.00,0.01);
    typedef Policy_Add_Particle_Cube<type_data_ref> type_pol_add_particle;
    type_pol_add_particle m_add_particle(m_data_ref,1);
    typedef Policy_Is_Inbound_Filling_Layer_CellType<type_data_ref> type_pol_is_inbound_filling_layer;
    type_pol_is_inbound_filling_layer m_pol_is_inbound_filling_layer;
    typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol_is_in_domain_speed;
    type_pol_is_in_domain_speed m_pol_is_in_domain_speed;
    typedef Policy_Depth<type_data_ref> type_pol_depth;
    type_pol_depth m_pol_depth(4,3,3);
    typedef Policy_Solve_Linear_Umfpack<double> type_pol_solve_linear2;
    type_pol_solve_linear2 m_pol_solve_linear2;
    typedef Policies<type_pol_layer,type_pol_part_to_key,type_pol_check_dt,type_pol_add_particle,type_pol_is_inbound_filling_layer,type_pol_is_in_domain_speed,type_pol_depth,type_pol_solve_linear2> type_pol_init;
    type_pol_init m_pol_init(m_pol_layer,m_pol_part_to_key,m_pol_check_dt,m_add_particle,m_pol_is_inbound_filling_layer,m_pol_is_in_domain_speed,m_pol_depth,m_pol_solve_linear2);

    //Algorithm Init
    typedef Algorithms_Initialize_Layer_And_Depth<type_data_ref,type_pol_init> type_alg_initialize_mac;
    type_alg_initialize_mac m_alg_initialize_mac(m_data_ref,m_pol_init);
    typedef Algorithms_Layer_Initial_With_Particle_Depth<type_data_ref,type_pol_init> type_alg_layer_initial;
    type_alg_layer_initial m_alg_layer_initial(m_data_ref,m_pol_init);
    typedef Algorithms_Create_Fluid_Particle_Depth<type_data_ref,type_pol_init> type_alg_part_create;
    type_alg_part_create m_alg_part_create(m_data_ref,m_pol_init);
    typedef Algorithms_Create_Interior_Depth<type_data_ref,type_pol_init> type_alg_part_create_interior;
    type_alg_part_create_interior m_alg_part_create_interior(m_data_ref,m_pol_init);
    typedef Algorithms_Update_CellType_Layer_Depth<type_data_ref,type_pol_init> type_alg_update_celltype;
    type_alg_update_celltype m_alg_update_celltype(m_data_ref,m_pol_init);
    typedef Algorithms_Delete_MacCell<type_data_ref,type_pol_init> type_alg_delete_maccell;
    type_alg_delete_maccell m_alg_delete_maccell(m_data_ref,m_pol_init);
    typedef Algorithms_Calculate_Time_Step<type_data_ref,type_pol_init> type_alg_calculate_time_step;
    type_alg_calculate_time_step m_alg_calculate_time_step(m_data_ref,m_pol_init);
    //typedef Algorithm_Init_Perturbation<type_data_ref,type_pol_init> type_alg_perturb;
    //type_alg_perturb m_alg_perturb(m_data_ref,m_pol_init,val_speed,1.0,0.01,ymax);
    typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol_init> type_alg_extrap_bound;
    type_alg_extrap_bound m_alg_extrap_bound(m_data_ref,m_pol_init);
    typedef Algorithms_Extrapolate<type_data_ref,type_pol_init> type_alg_extrap;
    type_alg_extrap m_alg_extrap(m_data_ref,m_pol_init);

    typedef Algorithms<type_alg_initialize_mac,type_alg_layer_initial,type_alg_part_create,type_alg_update_celltype,type_alg_delete_maccell,type_alg_calculate_time_step/*,type_alg_perturb*/,type_alg_extrap_bound,type_alg_extrap> type_alg_init;
    type_alg_init m_alg_init(m_alg_initialize_mac,m_alg_layer_initial,m_alg_part_create,m_alg_update_celltype,m_alg_delete_maccell,m_alg_calculate_time_step/*,m_alg_perturb*/,m_alg_extrap_bound,m_alg_extrap);

    typedef Algorithms<type_alg_initialize_mac,type_alg_layer_initial,type_alg_part_create_interior,type_alg_update_celltype,type_alg_delete_maccell/*,type_alg_perturb*/,type_alg_extrap_bound,type_alg_extrap> type_alg_init2;
    type_alg_init2 m_alg_init2(m_alg_initialize_mac,m_alg_layer_initial,m_alg_part_create_interior,m_alg_update_celltype,m_alg_delete_maccell/*,m_alg_perturb*/,m_alg_extrap_bound,m_alg_extrap);

    // Policy Solve Grid
    typedef Policy_Gravity<type_data_ref> type_pol_gravity;
    type_pol_gravity m_pol_gravity(m_data_ref,-9.81,2);
    typedef Policy_Laplacian<type_data_ref> type_pol_laplacian;
    type_pol_laplacian m_pol_laplacian(m_data_ref);
    typedef Policy_Laplacian_Speed<type_data_ref> type_pol_laplacian_speed;
    type_pol_laplacian_speed m_pol_laplacian_speed(m_data_ref);
    typedef Policy_Viscosity_Apply_If<type_data_ref> type_pol_viscosity_apply_if;
    type_pol_viscosity_apply_if m_pol_viscosity_apply_if;
    typedef Policy_Speed_Interpolation_Linear_Symmetric<type_data_ref> type_pol_speed_interpolation;
    type_pol_speed_interpolation m_pol_speed_interpolation(m_data_ref);
    typedef Policy_Convection_Apply_If<type_data_ref> type_pol_convection_apply_if;
    type_pol_convection_apply_if m_pol_convection_apply_if;
    typedef Policy_Upwind_1_Order<type_data_ref,type_pol_speed_interpolation> type_pol_convection;
    //typedef Policy_Convection_Center<type_data_ref,type_pol_speed_interpolation> type_pol_convection;
    type_pol_convection m_pol_convection(m_data_ref,m_pol_speed_interpolation);

    typedef Policy_Wind<type_data_ref> type_pol_wind;
    type_pol_wind m_pol_wind(100,1,1);



    typedef Policies<type_pol_gravity,type_pol_laplacian,type_pol_laplacian_speed,type_pol_viscosity_apply_if,type_pol_convection_apply_if,type_pol_convection,type_pol_wind> type_pol_solve_grid;
    type_pol_solve_grid m_pol_solve_grid(m_pol_gravity,m_pol_laplacian,m_pol_laplacian_speed,m_pol_viscosity_apply_if,m_pol_convection_apply_if,m_pol_convection,m_pol_wind);

    //Algorithms Solve Grid
    typedef Algorithms_Gravity<type_data_ref,type_pol_solve_grid> type_alg_gravity;
    type_alg_gravity m_alg_gravity(m_data_ref,m_pol_solve_grid);
    typedef Algorithms_Convection<type_data_ref,type_pol_solve_grid> type_alg_convection;
    type_alg_convection m_alg_convection(m_data_ref,m_pol_solve_grid);
#ifdef VISCOSITY
    typedef Algorithms_Viscosity<type_data_ref,type_pol_solve_grid> type_alg_viscosity;
    type_alg_viscosity m_alg_viscosity(m_data_ref,m_pol_solve_grid);
#endif

#ifdef SPLIT
#ifdef VISCOSITY
    typedef Algorithms<type_alg_gravity,type_alg_convection,type_alg_viscosity> type_alg_solve_grid;
    type_alg_solve_grid m_alg_solve_grid(m_alg_gravity,m_alg_convection,m_alg_viscosity);
#else
    typedef Algorithms<type_alg_gravity,type_alg_convection> type_alg_solve_grid;
    type_alg_solve_grid m_alg_solve_grid(m_alg_gravity,m_alg_convection);
#endif
#else
    #ifdef VISCOSITY
    typedef Algorithms<type_alg_init2,type_alg_gravity,type_alg_convection,type_alg_viscosity> type_alg_solve_grid;
    type_alg_solve_grid m_alg_solve_grid(m_alg_init2,m_alg_gravity,m_alg_convection,m_alg_viscosity);
#else
    typedef Algorithms<type_alg_init2,type_alg_gravity,type_alg_convection> type_alg_solve_grid;
    type_alg_solve_grid m_alg_solve_grid(m_alg_init2,m_alg_gravity,m_alg_convection);
#endif
#endif

    //Policy Pressure
    typedef Policy_Solve_Linear_Umfpack<double> type_pol_solve_linear;
    type_pol_solve_linear m_pol_solve_linear;
    typedef Policy_Divergence<type_data_ref> type_pol_divergence;
    type_pol_divergence m_pol_divergence(m_data_ref);
    typedef Policy_Gradiant<type_data_ref> type_pol_gradiant;
    type_pol_gradiant m_pol_gradiant(m_data_ref);
    typedef Policy_Von_Neumann_Boundary<type_data_ref> type_pol_von_neumann_boundary;
    type_pol_von_neumann_boundary m_pol_von_neumann_boundary(m_data_ref);
    typedef Policy_Pressure_If_Correction<type_data_ref> type_pol_pres_cor_if;
    type_pol_pres_cor_if m_pol_pres_cor_if;
    typedef Policy_Dirichlet_Boundary<type_data_ref> type_pol_dirichlet_bound;
    type_pol_dirichlet_bound m_pol_dirichlet_bound(m_data_ref);

    typedef Policies<type_pol_solve_linear,type_pol_divergence,type_pol_gradiant,type_pol_von_neumann_boundary,type_pol_pres_cor_if,type_pol_dirichlet_bound> type_pol_pres;
    type_pol_pres m_pol_pres(m_pol_solve_linear,m_pol_divergence,m_pol_gradiant,m_pol_von_neumann_boundary,m_pol_pres_cor_if,m_pol_dirichlet_bound);

    //Algorithm Solve Pressure
#ifndef VISCOSITY
    typedef Algorithms_Solve_Pressure<type_data_ref,type_pol_pres> type_alg_solve_pressure;
    #else
    typedef Algorithms_Solve_Pressure_Dirichlet_Pyamg<type_data_ref,type_pol_pres> type_alg_solve_pressure;
#endif
    type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_pres);

    typedef Algorithms_Solve_Pressure_Pyamg<type_data_ref,type_pol_pres> type_alg_solve_pressure2;
    type_alg_solve_pressure2 m_alg_solve_pressure2(m_data_ref,m_pol_pres);

    typedef Algorithms_Solve_Pressure_Force<type_data_ref,type_alg_solve_pressure> type_alg_solve_force_pressure;
    type_alg_solve_force_pressure m_alg_solve_force_pressure(m_data_ref,m_alg_solve_pressure);
#ifndef SPLIT
    typedef Algorithms<type_alg_extrap_bound,type_alg_extrap> type_alg_extrapolate;
    type_alg_extrapolate m_alg_extrapolate(m_alg_extrap_bound,m_alg_extrap);

    typedef Algorithms_Accel_To_Speed<type_data_ref,type_alg_extrapolate> type_alg_extrapolate_force;
    type_alg_extrapolate_force m_alg_extrapolate_force(m_data_ref,m_alg_extrapolate);

    typedef Algorithms<type_alg_solve_grid,type_alg_solve_force_pressure,type_alg_extrapolate_force> type_alg_solve_grid_force;
    type_alg_solve_grid_force m_alg_solve_grid_force(m_alg_solve_grid,m_alg_solve_force_pressure,m_alg_extrapolate_force);
#else
    typedef Algorithms<type_alg_solve_grid,type_alg_solve_force_pressure> type_alg_solve_grid_force;
    type_alg_solve_grid_force m_alg_solve_grid_force(m_alg_solve_grid,m_alg_solve_force_pressure);
#endif

    //typedef Algorithms_Do_Pressure<type_data_ref,type_alg_solve_pressure2> type_alg_do_pres;
    //type_alg_do_pres m_alg_do_pres(m_data_ref,m_alg_solve_pressure2);
#ifndef SPLIT
    //Policy ODE
    typedef Policy_Speed_Interpolation_Linear_Symmetric<type_data_ref> type_pol_interpolation;
    type_pol_interpolation m_pol_interpolation(m_data_ref);
    typedef Policies<type_pol_interpolation> type_pol_move;
    type_pol_move m_pol_move(m_pol_interpolation);

    typedef Policy_Move_Particle<type_data_ref,type_pol_move> type_pol_move2;
    type_pol_move2 m_pol_move2(m_data_ref,m_pol_move);

    typedef Policies<type_alg_solve_grid_force,type_pol_move2> type_pol_ODE;
    type_pol_ODE m_pol_ODE(m_alg_solve_grid_force,m_pol_move2);
#else
    typedef Algorithms<type_alg_solve_grid_force,/*type_alg_do_pres*/> type_pol_ODE;
    type_pol_ODE m_pol_ODE(m_alg_solve_grid_force,m_alg_do_pres);
#endif

    //Algorithms ODE
    //typedef Algorithms_Euler<type_data_ref,type_pol_ODE> type_alg_ODE;
#ifdef SPLIT
    typedef Algorithms_RungeKutta_Force<type_data_ref,type_pol_ODE> type_alg_ODE;
    //typedef Algorithms_Euler_Force<type_data_ref,type_pol_ODE> type_alg_ODE;
    type_alg_ODE m_alg_ODE(m_data_ref,m_pol_ODE);
#else
    typedef Algorithms_RungeKutta_all<type_data_ref,type_pol_ODE> type_alg_ODE;
    type_alg_ODE m_alg_ODE(m_data_ref,m_pol_ODE);
#endif

    typedef Algorithms<type_alg_ODE/*,type_alg_do_pres*/> type_alg_ODE2;
    type_alg_ODE2 m_alg_ODE2(m_alg_ODE/*,m_alg_do_pres*/);

    //Policy Move
#ifdef SPLIT
    typedef Policy_Advance_Ode_RungeKutta<type_data_ref> type_pol_advance_ode;
    type_pol_advance_ode m_pol_advance_ode;
    typedef Policy_Speed_Interpolation_Linear_Symmetric<type_data_ref> type_pol_interpolation;
    type_pol_interpolation m_pol_interpolation(m_data_ref);
    typedef Policies<type_pol_advance_ode,type_pol_interpolation> type_pol_move;
    type_pol_move m_pol_move(m_pol_advance_ode,m_pol_interpolation);

    //Algorithms Move
    typedef Algorithms_Move_Particles<type_data_ref,type_pol_move> type_alg_move;
    type_alg_move m_alg_move(m_data_ref,m_pol_move);
#endif

    //Policy Output
    typedef Policy_Output_Grid_Speed_ID<type_data_ref> type_pol_output_speed;
    type_pol_output_speed m_pol_output_speed(m_data_ref,"out_speed_");
    typedef Policy_Output_Grid_Pressure_ID<type_data_ref> type_pol_output_pressure;
    type_pol_output_pressure m_pol_output_pressure(m_data_ref,"out_press_");
    typedef Policy_Output_Animation<type_data_ref> type_pol_output_animation;
    type_pol_output_animation m_pol_output_animation(m_data_ref,"Out_Animation.pvd");
    typedef Policy_Output_Particle<type_data_ref> type_pol_output_topo;
    type_pol_output_topo m_pol_output_topo(m_data_ref,"out_topo_");
    typedef Policies<type_pol_output_speed,type_pol_output_pressure,type_pol_output_animation,type_pol_output_topo> type_pol_output;
    type_pol_output m_pol_output(m_pol_output_speed,m_pol_output_pressure,m_pol_output_animation,m_pol_output_topo);

    //Algorithms Output
    typedef Algorithms_Output<type_data_ref,type_pol_output> type_alg_output;
    type_alg_output m_alg_output(m_data_ref,m_pol_output,ireload,breload);


    m_alg_init.Do();
    m_alg_solve_pressure.Init_Iteration();
    m_alg_solve_pressure.Divergence_Projection();
    m_alg_solve_pressure.End_Iteration();
    m_alg_output.Do();

    for(int i=1;;++i)
    {
        cout<<"i "<<i<<endl;
        m_alg_init.Do();
        m_alg_ODE2.Do();
#ifdef SPLIT
        m_alg_move.Do();
#endif
        cout<<"dt "<<m_data_ref.m_data.GetTimingData().m_dt<<endl;
        cout<<"t "<<m_data_ref.m_data.GetTimingData().m_t<<endl;
        if(i%5==0)
        {
            cout<<"out "<<endl;
#ifndef SPLIT
            m_alg_extrap_bound.Do();
            m_alg_extrap.Do();
#endif
            m_alg_output.Do();
        }
    }
    SingletonManager::Kill();
}


