#pragma STDC FENV_ACCESS ON

#include <cxxtest/TestSuite.h>

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
#include "../src/Policy_Output_Grid_Pressure.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Animation.h"
#include "../src/Policy_Upwind_1_Order.h"
#include "../src/Policy_Convection_Apply_If.h"
#include "../src/Policy_Pressure_If_Correction.h"
#include "../src/Policy_Is_In_Domain_Speed.h"
/// To add Convection

//Algorithms

#include "../src/Algorithm_Extrapolate_Boundary_Condition.h"

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
#include "../src/Algorithms_Solve_Pressure_Fixed_Neumann.h"
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

#include <cfenv>

using namespace std;



#define eps 1e-10
class Test_Data_CellType_Domain_Fluid : public CxxTest::TestSuite  //LCOV_EXCL_LINE
{
public:
    void test_one_particle()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
    }
    void test_two_particle_plane()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,-1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,-1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),4,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),-1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),-1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

    }
    void test_3_particle_corner()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,3);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));


        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,-1.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,-1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,1.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),-1,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),-1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),1,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));


        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,4.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,-1.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,-1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,1.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),-1,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),-1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),1,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

    }

    void test_square()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));


        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,1.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,3.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,5.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,1.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,6.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,1);
        speed.Set(1,3.0);
        speed.Set(2,7.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        speed.Set(1,5.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        speed.Set(1,3.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,1);
        speed.Set(1,3.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),5,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),5,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),5,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,0);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
    }
    void test_3_align()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();


        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,4.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,2.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,3.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,5.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,8.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,3.0);
        speed.Set(2,6.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        speed.Set(1,9.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        speed.Set(1,6.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        speed.Set(1,3.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),1,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),1,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),3,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),3,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),6,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),7,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
    }

    void test_3_align_1()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,3);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();


        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,5.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,3.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,9.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,8.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,2);
        speed.Set(1,4.0);
        speed.Set(2,10.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,3.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,9.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        speed.Set(1,7.0);
        speed.Set(2,4.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        speed.Set(1,5.0);
        speed.Set(2,6.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,3.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        speed.Set(1,7.0);
        speed.Set(2,7.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),8,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),2,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),9,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),8,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),5,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),9,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),7,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),4,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),8,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
    }

    void test_4_align_2()
    {
        feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
        const int DIM=2;
        const int NBSpeed=3;
        double value=1.0;
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
        m_time.m_factor=1;
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
        speed.Set(1,0.0);
        speed.Set(2,0.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,2);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,3);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,5);
        v.Set(2,0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,-1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,1);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();



        typedef Policy_Is_In_Domain_Speed<type_data_ref> type_pol;
        type_pol pol;
        typedef Algorithm_Extrapolate_Boundary_Condition<type_data_ref,type_pol> type_alg;
        type_alg alg(m_data_ref,pol);
        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,3);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,3);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,4);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),0,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));


        v.Set(1,0);
        v.Set(2,0);
        speed.Set(1,4.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,0);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,6.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,0);
        v.Set(2,-1);
        speed.Set(1,7.0);
        speed.Set(2,9.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,1.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,1);
        speed.Set(1,6.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,1);
        v.Set(2,2);
        speed.Set(1,8.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,1);
        v.Set(2,-1);
        speed.Set(1,7.0);
        speed.Set(2,8.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,0);
        speed.Set(1,5.0);
        speed.Set(2,7.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,1);
        speed.Set(1,2.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,2);
        v.Set(2,2);
        speed.Set(1,1.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,2);
        v.Set(2,-1);
        speed.Set(1,6.0);
        speed.Set(2,7.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,0);
        speed.Set(1,7.0);
        speed.Set(2,8.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

        v.Set(1,3);
        v.Set(2,1);
        speed.Set(1,9.0);
        speed.Set(2,7.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,3);
        v.Set(2,-1);
        speed.Set(1,4.0);
        speed.Set(2,5.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,-1);
        v.Set(2,0);
        speed.Set(1,2.0);
        speed.Set(2,3.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        v.Set(1,4);
        v.Set(2,0);
        speed.Set(1,1.0);
        speed.Set(2,2.0);
        m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
        m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();

        alg.Do();

        v.Set(1,0);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),3,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),5,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,0);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),6,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,0);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,1);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),6,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,1);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),3,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,1);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,2);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),5,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),7,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,2);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),5,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,2);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),5,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,2);
        v.Set(2,-1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),6,eps);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,3);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),7,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),8,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        v.Set(1,3);
        v.Set(2,1);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),2,eps);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2),7,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        v.Set(1,3);
        v.Set(2,-1);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));

        v.Set(1,-1);
        v.Set(2,0);
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));

        v.Set(1,4);
        v.Set(2,0);
        TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1),8,eps);
        TS_ASSERT(!std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(1)));
        TS_ASSERT(std::isnan(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Get(2)));
    }

};
