#ifndef TEST_ALGORITHMS_SOLVE_PRESSURE_NEUMANN_VAR_H
#define TEST_ALGORITHMS_SOLVE_PRESSURE_NEUMANN_VAR_H

#endif // TEST_ALGORITHMS_SOLVE_PRESSURE_NEUMANN_VAR_H

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
#include "../src/Policy_Add_Particle_Cube.h"
#include "../src/Policy_Is_Inbound_Filling_Layer_CellType.h"
#include "../src/Policy_Advance_ODE_RungeKutta.h"
#include "../src/Policy_Speed_Interpolation_Linear_Symmetric.h"
#include "../src/Policy_Output_Grid_Speed_ID.h"
#include "../src/Policy_Output_Grid_Pressure.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Animation.h"
#include "../src/Policy_Upwind_1_Order.h"
#include "../src/Policy_Convection_Apply_If.h"
#include "../src/Policy_Pressure_If_Correction.h"
#include "../src/Policy_Von_Neumann_Boundary_Data.h"
/// To add Convection

//Algorithms

//Const
#include "../src/Algorithms_Speed_Constant_Mirror.h"
#include "../src/Algorithms_Extrapolate.h"
// Initialisation
#include "../src/Algorithms_Fluid_To_Layer.h"
#include "../src/Algorithms_Initialize_MacCell.h"
#include "../src/Algorithms_Calculate_Time_Step.h"
#include "../src/Algorithms_Update_CellType_Layer.h"
#include "../src/Algorithms_Inflow_To_Const.h"
#include "../src/Algorithms_Solid_To_Const.h"

// Solve Grid
#include "../src/Algorithms_Speed_Repeat_Constant.h"
#include "../src/Algorithms_Gravity.h"
#include "../src/Algorithms_Viscosity.h"
#include "../src/Algorithms_Solve_Pressure_Neumann_Var.h"
#include "../src/Algorithms_Solve_Pressure_Fixed.h"
#include "../src/Algorithms_Solve_Pressure_Empty.h"
#include "../src/Algorithms_Convection.h"

//Integrator
#include "../src/Algorithms_Euler.h"
#include "../src/Algorithms_RungeKutta.h"
#include "../src/Algorithms_RungeKutta_RK2.h"
#include "../src/Algorithms_RungeKutta_RK2_TVD.h"

// Output
#include "../src/Algorithms_Output_Speed_Pressure.h"

#include <sys/times.h>
#include <stdlib.h>

#include <bitset>

#include <stdexcept>

#include <cxxtest/TestSuite.h>

using namespace std;


template <typename Data>
class PolicyVonNeumann_Boundary
{
    typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
    typedef typename type_Data_Grid::type_key type_key;
    typedef typename type_Data_Grid::type_data::type_speed type_speed;
    typedef typename type_speed::type_data_value type_speed_value;
    typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
    typedef typename type_Data_Grid::type_offset type_neigh;
    typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
    typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
    type_Data_Grid& m_grid;
    const type_spacing_vector &m_1_h;
    const type_spacing_vector &m_h;
    type_Time_Type& m_t;
    public:
    PolicyVonNeumann_Boundary(Data data) :m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_t(data.m_data.GetTimingData().m_t)
    {
    }
    type_speed_value GetNeumannGradiantPressure(const type_neigh & neigh,int i,int s)
    {
        if(i!=2)
        {
            return 0;
        }
        if(((neigh.GetKey().Get(2)==0 && s==-1)||(neigh.GetKey().Get(2)==-1 && s==1))&&neigh.GetKey().Get(1)==0)
        {
            return 1;
        }
        throw std::logic_error("Boundary condition access direction bigger than dimension");
    }
};

class Test_Algorithms_Solve_Pressure_Neumann_Var: public CxxTest::TestSuite  //LCOV_EXCL_LINE
{
    public:
    ~Test_Algorithms_Solve_Pressure_Neumann_Var()
    {
            SingletonManager::Kill();
    }
    void test_2d_simple()
    {
        const int DIM=2;
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

        typedef Data_CellType_Domain_Fluid_Without_0_Pres<type_grid_celltype> type_cell_type;
        type_cell_type m_celltype(m_grid_celltype);

        typedef Data_Grid_CellType_To_Grid_CellType<type_cell_type> type_cell_grid_celltype;
        type_cell_grid_celltype m_cell_grid_celltype(m_celltype);

        typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
        type_chunk_layer m_chunk_layer(m_empt_lay);

        typedef Data_Chunk_Id_Cell<type_empt_id,NStock> type_chunk_id;
        type_chunk_id m_chunk_id(m_empt_id);

        typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
        type_bool_array m_bool_array;

        typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
        type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

        typedef Data_Chunk_Speed<type_grid_speed,NBSpeed,1,NStock> type_chunk_speed;
        type_chunk_speed m_chunk_speed(m_grid_speed);

        typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
        type_chunk_pressure m_chunk_pressure(m_grid_pressure);

        typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_id,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
        type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_id,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

        typedef Physvector<DIM,int> vect;

        typedef Neighbour_List_Key<vect,type_chunk> type_neigh_key;
        type_neigh_key m_neigh_key(m_chunk);
        typedef Neighbour_List_Empty<DIM,type_neigh_key> type_neigh;
        type_neigh m_neigh(m_neigh_key);

        typedef Offset<int,DIM,N> type_off;
        typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Key<vect,type_off_base> type_off_key;
        typedef Offset_Base_Layer<type_empt_lay,type_off_key> type_off_base_layer;
        typedef Offset_Base_Id_Cell<type_empt_id,type_off_base_layer> type_off_base_id;
        typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_id> type_off_base_celltype;
        typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
        typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
        typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
        typedef Physvector<DIM,double> vectdouble;
        typedef HashPhysvector<DIM,int> Hash;
        Hash hash;
        typedef ChunkHashTable<Hook_Neighbour_List_Key,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
        type_chunk_table m_chunk_table(m_neigh,hash);

        typedef Data_Viscosity<type_chunk_table> type_data_viscosity;
        type_data_viscosity m_data_viscosity(m_chunk_table);
        m_data_viscosity.m_viscosity=0;
        typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value> > type_data_grid;
        type_data_grid m_data_grid(m_data_viscosity);
        Physvector<DIM,type_data_value> h;
        h.Set(1,0.1);
        h.Set(2,0.1);
        m_data_grid.m_h.Set(h);
        typedef Data_Staggered_Left<type_data_grid> type_data_stag_left;
        type_data_stag_left m_data_stag_left(m_data_grid);
        typedef Data_CellType_Interface_Constant<type_data_stag_left> type_interface_constant;
        type_interface_constant m_type_interface_constant(m_data_stag_left);
        typedef Data_Grid_Data<type_interface_constant,DataBase> type_grid_data;
        type_grid_data m_grid_data(m_type_interface_constant,base);


        // Data Timming
        typedef Data_Timing_Time<type_data_value> type_time;
        type_time m_time;
        m_time.m_t=0;
        m_time.m_factor=0.1;
        typedef Data_Timing<type_time,type_grid_data> type_timing;
        type_timing m_timing(m_time,m_grid_data);

        //Data Ref
        typedef DataRef<type_timing> type_data_ref;
        type_data_ref m_data_ref(m_timing);

        //Initial Data
        vect v;
        v.Set(1,0);
        v.Set(2,0);
        Physvector<DIM,type_data_value> speed;
        speed.Set(1,1.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        //m_data_ref.m_data.GetGridData()[v].CellType_GetRef().Set0_Pres();

        //Policy Solve Pressure;
        typedef Policy_Solve_Linear_Umfpack<double> type_pol_solve_linear;
        type_pol_solve_linear m_pol_solve_linear;
        typedef Policy_Pressure_If_Correction<type_data_ref> type_pol_pres_cor_if;
        type_pol_pres_cor_if m_pol_pres_cor_if;
        typedef Policy_Gradiant<type_data_ref> type_pol_gradiant;
        type_pol_gradiant m_pol_gradiant(m_data_ref);
        typedef Policy_Von_Neumann_Boundary<type_data_ref> type_pol_von_neumann_boundary;
        type_pol_von_neumann_boundary m_pol_von_neumann_boundary(m_data_ref);
        typedef Policy_Divergence<type_data_ref> type_pol_divergence;
        type_pol_divergence m_pol_divergence(m_data_ref);
        typedef PolicyVonNeumann_Boundary<type_data_ref> type_pol_von_neumann2;
        type_pol_von_neumann2 m_pol_von_neumann_boundary2(m_data_ref);

        typedef Policies<type_pol_solve_linear,type_pol_pres_cor_if,type_pol_gradiant,type_pol_von_neumann_boundary,type_pol_divergence,type_pol_von_neumann2> type_pol_pressure;
        type_pol_pressure m_pol_pressure(m_pol_solve_linear,m_pol_pres_cor_if,m_pol_gradiant,m_pol_von_neumann_boundary,m_pol_divergence,m_pol_von_neumann_boundary2);

        //Algorithms Solve Pressure
        typedef Algorithms_Solve_Pressure_Neumann_Var<type_data_ref,type_pol_pressure> type_alg_solve_pressure;
        type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_pressure);

        m_alg_solve_pressure.Init_Iteration();
        m_alg_solve_pressure.Divergence_Projection();
        m_alg_solve_pressure.End_Iteration();
        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_pol_divergence.Get_Divergence(m_data_ref.m_data.GetGridData()[v]).Get(),0,0.000001);
    }
    void test_2d_simple_none_const()
    {
        const int DIM=2;
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

        typedef Data_Chunk_Speed<type_grid_speed,NBSpeed,1,NStock> type_chunk_speed;
        type_chunk_speed m_chunk_speed(m_grid_speed);

        typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
        type_chunk_pressure m_chunk_pressure(m_grid_pressure);

        typedef Data_Chunk_Speed_Von_Neumann<type_speed_von_neumann,NStock> type_chunk_speed_von_neumann;
        type_chunk_speed_von_neumann m_chunk_speed_von_neumann(m_speed_von_neumann);

        typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_id,type_chunk_celltype,type_chunk_speed,type_chunk_pressure,type_chunk_speed_von_neumann> type_chunk;
        type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_id,m_chunk_celltype,m_chunk_speed,m_chunk_pressure,m_chunk_speed_von_neumann);

        typedef Physvector<DIM,int> vect;

        typedef Neighbour_List_Key<vect,type_chunk> type_neigh_key;
        type_neigh_key m_neigh_key(m_chunk);
        typedef Neighbour_List_Empty<DIM,type_neigh_key> type_neigh;
        type_neigh m_neigh(m_neigh_key);

        typedef Offset<int,DIM,N> type_off;
        typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Key<vect,type_off_base> type_off_key;
        typedef Offset_Base_Layer<type_empt_lay,type_off_key> type_off_base_layer;
        typedef Offset_Base_Id_Cell<type_empt_id,type_off_base_layer> type_off_base_id;
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
        m_data_viscosity.m_viscosity=0;
        typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value> > type_data_grid;
        type_data_grid m_data_grid(m_data_viscosity);
        Physvector<DIM,type_data_value> h;
        h.Set(1,0.1);
        h.Set(2,0.1);
        m_data_grid.m_h.Set(h);
        typedef Data_Staggered_Left<type_data_grid> type_data_stag_left;
        type_data_stag_left m_data_stag_left(m_data_grid);
        typedef Data_CellType_Interface_Constant<type_data_stag_left> type_interface_constant;
        type_interface_constant m_type_interface_constant(m_data_stag_left);
        typedef Data_Grid_Data<type_interface_constant,DataBase> type_grid_data;
        type_grid_data m_grid_data(m_type_interface_constant,base);


        // Data Timming
        typedef Data_Timing_Time<type_data_value> type_time;
        type_time m_time;
        m_time.m_t=0;
        m_time.m_factor=0.1;
        typedef Data_Timing<type_time,type_grid_data> type_timing;
        type_timing m_timing(m_time,m_grid_data);

        //Data Ref
        typedef DataRef<type_timing> type_data_ref;
        type_data_ref m_data_ref(m_timing);

        //Initial Data
        vect v;
        v.Set(1,0);
        v.Set(2,0);
        Physvector<DIM,type_data_value> speed;
        speed.Set(1,1.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Speed_Von_Neumann_GetRef().Set_Von_Neumann(2);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();

        //m_data_ref.m_data.GetGridData()[v].CellType_GetRef().Set0_Pres();

        //Policy Solve Pressure;
        typedef Policy_Solve_Linear_Umfpack<double> type_pol_solve_linear;
        type_pol_solve_linear m_pol_solve_linear;
        typedef Policy_Pressure_If_Correction<type_data_ref> type_pol_pres_cor_if;
        type_pol_pres_cor_if m_pol_pres_cor_if;
        typedef Policy_Gradiant<type_data_ref> type_pol_gradiant;
        type_pol_gradiant m_pol_gradiant(m_data_ref);
        typedef Policy_Von_Neumann_Boundary_Data<type_data_ref> type_pol_von_neumann_boundary;
        type_pol_von_neumann_boundary m_pol_von_neumann_boundary(m_data_ref);
        typedef Policy_Divergence<type_data_ref> type_pol_divergence;
        type_pol_divergence m_pol_divergence(m_data_ref);
        typedef PolicyVonNeumann_Boundary<type_data_ref> type_pol_von_neumann2;
        type_pol_von_neumann2 m_pol_von_neumann_boundary2(m_data_ref);

        typedef Policies<type_pol_solve_linear,type_pol_pres_cor_if,type_pol_gradiant,type_pol_von_neumann_boundary,type_pol_divergence,type_pol_von_neumann2> type_pol_pressure;
        type_pol_pressure m_pol_pressure(m_pol_solve_linear,m_pol_pres_cor_if,m_pol_gradiant,m_pol_von_neumann_boundary,m_pol_divergence,m_pol_von_neumann_boundary2);

        //Algorithms Solve Pressure
        typedef Algorithms_Solve_Pressure_Neumann_Var<type_data_ref,type_pol_pressure> type_alg_solve_pressure;
        type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_pressure);

        m_alg_solve_pressure.Init_Iteration();
        m_alg_solve_pressure.Divergence_Projection();
        m_alg_solve_pressure.End_Iteration();
        v.Set(1,0);
        v.Set(2,0);

        TS_ASSERT_DELTA(m_pol_divergence.Get_Divergence(m_data_ref.m_data.GetGridData()[v]).Get(),0,0.000001);
    }
};
