
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"

//HashTable+Neighbour
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Hook_Neighbour_List_Chunk.h"

//Data Chunk
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_Bool_Array.h"

//Offset
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"

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
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow.h"
#include "../src/Data_CellType_Domain_Fluid.h"
#include "../src/Data_Grid_CellType_To_Grid_CellType.h"

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
#include "../src/Policy_Output_Grid_Speed.h"
#include "../src/Policy_Output_Grid_Pressure.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Animation.h"
#include "../src/Policy_Upwind_1_Order.h"
#include "../src/Policy_Convection_Apply_If.h"
#include "../src/Policy_Pressure_If_Correction.h"
/// To add Convection

//Algorithms

//Const
#include "../src/Algorithms_Speed_Constant_Mirror.h"
#include "../src/Algorithms_Extrapolate.h"
// Initialisation
#include "../src/Algorithms_Initialize_MacCell.h"
#include "../src/Algorithms_Create_Fluid_Particle.h"
#include "../src/Algorithms_Layer_Initial_With_Particle.h"
#include "../src/Algorithms_Calculate_Time_Step.h"
#include "../src/Algorithms_Delete_MacCell.h"
#include "../src/Algorithms_Update_CellType_Layer.h"
#include "../src/Algorithms_Fluid_To_Layer.h"
#include "../src/Algorithms_Inflow_To_Const.h"
#include "../src/Algorithms_Solid_To_Const.h"

// Solve Grid
#include "../src/Algorithms_Gravity.h"
#include "../src/Algorithms_Viscosity.h"
#include "../src/Algorithms_Solve_Pressure.h"
#include "../src/Algorithms_Convection.h"

//Move Particle
#include "../src/Algorithms_Move_Particles.h"

// Output
#include "../src/Algorithms_Output.h"

#include <sys/times.h>

int main()
{
	const int DIM=2;
	const int N=4;
	const int NStock=pow(N,DIM);
	typedef double type_data_value;

	// Data Type and Grid Type.
	typedef Data_Base_Dim_Type<type_data_value,DIM> type_Data_Type;
	type_Data_Type m_data_type;
	typedef Data_Staggered_Left<type_Data_Type> type_Data_Base;

	type_Data_Base data_base(m_data_type);

	// Data CellType.
	typedef Data_CellType_Fluid_Air_Solid_Inflow<type_Data_Base> type_cell_type2;
	typedef Inversible_Value<type_data_value> type_inversible_value;
	type_inversible_value rho_air(1);
	type_inversible_value rho_fluid(1000);
	type_cell_type2 m_celltype2(data_base);
	m_celltype2.SetRhoAir(rho_air);
	m_celltype2.SetRhoFluid(rho_fluid);
	typedef Data_CellType_Domain_Fluid<type_cell_type2> type_cell_type;
	type_cell_type m_celltype(m_celltype2);
	typedef Data_Grid_CellType_To_Grid_CellType<type_cell_type> type_cell_cell;
	type_cell_cell m_cell_cell(m_celltype);

	// Data Speed.
	typedef Data_Grid_Speed<type_Data_Base> type_grid_speed;
	type_grid_speed m_grid_speed;

	// Data Pressure
	typedef Data_Grid_Pressure<type_Data_Base> type_grid_pressure;
	type_grid_pressure m_grid_pressure;

	// Data Layer
	typedef Data_Grid_Layer<int> type_layer2;
	type_layer2 m_layer2;
	typedef Data_Grid_Layer_Empty<type_layer2> type_layer;
	type_layer m_layer;

	// Vector
	typedef Physvector<DIM,int> vect;
	typedef HashPhysvector<DIM,int> Hash;
	Hash hash;

	// Hookable table + Neighbour
	typedef Data_Chunk_Bool_Array<NStock> type_chunk_bool_array;
	type_chunk_bool_array m_chunk_bool_array;

	typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
	type_chunk_pressure m_chunk_pressure(m_grid_pressure);

	typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
	type_chunk_speed m_chunk_speed(m_grid_speed);

	typedef Data_Chunk_CellType<type_cell_cell,NStock> type_chunk_celltype;
	type_chunk_celltype m_chunk_celltype(m_cell_cell);

	typedef Data_Chunk_Layer<type_layer,NStock> type_chunk_layer;
	type_chunk_layer m_chunk_layer(m_layer);

	typedef Data_Chunk<type_chunk_bool_array,type_chunk_pressure,type_chunk_speed,type_chunk_celltype,type_chunk_layer> type_chunk;
	type_chunk m_chunk(m_chunk_bool_array,m_chunk_pressure,m_chunk_speed,m_chunk_celltype,m_chunk_layer);

	typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
	type_neigh m_neigh(m_chunk);

	typedef Offset<int,DIM,N> type_off;
	typedef Offset_Base<type_off,type_neigh> type_off_base;
	typedef Offset_Base_Layer<type_layer,type_off_base> type_off_base_layer;
	typedef Offset_Base_CellType<type_cell_cell,type_off_base_layer> type_off_base_celltype;
	typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
	typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
	typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;

	typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
	type_chunk_table m_chunk_table(m_neigh,hash);

	// Data Grid
	typedef Data_Viscosity<type_chunk_table> type_data_viscosity;
	type_data_viscosity m_data_viscosity(m_chunk_table);
	m_data_viscosity.m_viscosity=1.3e-6;
	typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value>> type_data_grid;
	type_data_grid m_data_grid(m_data_viscosity);
	Physvector<DIM,type_data_value> h;
	h.Set(1,0.01);
	h.Set(2,0.01);
	m_data_grid.m_h.Set(h);
	typedef Data_Staggered_Left<type_data_grid> type_stag_left;
	type_stag_left m_stag_left(m_data_grid);

	typedef Data_CellType_Interface_Constant<type_stag_left> type_interface_constant;
	type_interface_constant m_type_interface_constant(m_stag_left);
	typedef Data_Grid_Data<type_interface_constant,type_Data_Base> type_grid_data;
	type_grid_data m_grid_data(m_type_interface_constant,data_base);

	// Data Particle
	typedef Data_Particle<type_Data_Base> type_particle;
	typedef Data_Particles_List<type_particle,type_Data_Base> type_particles;
	type_particles particles(data_base);
	typedef Data_Topology<type_particles,type_grid_data> type_topology;
	type_topology m_topology(particles,m_grid_data);

	// Data Timming
	typedef Data_Timing_Time<type_data_value> type_time;
	type_time m_time;
	m_time.m_t=0;
	m_time.m_factor=0.1;
	typedef Data_Timing<type_time,type_topology> type_timing;
	type_timing m_timing(m_time,m_topology);

	//Data Ref
	typedef DataRef<type_timing> type_data_ref;
	type_data_ref m_data_ref(m_timing);

	//Initial Data
	vect v;
	int NS=100;
	for(int i=-NS;i<=NS;++i)
	{
		for(int j=-NS;j<=NS;++j)
		{
			v.Set(1,i);
			v.Set(2,j);

			Physvector<DIM,type_data_value> speed;
			speed.Set(1,10.0+i);
			speed.Set(2,10.0+j);
			m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<DIM,type_data_value>(speed));
			if(i!=NS&&j!=NS)
			{
				m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
				m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
			}
			else
			{
				m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();
			}
		}
	}

	//Policy Init
	typedef Policy_Layer_Max<type_data_ref> type_pol_layer;
	type_pol_layer m_pol_layer(3);
	typedef Policy_CheckDT<type_data_ref> type_pol_check_dt;
	type_pol_check_dt m_pol_check_dt(0.00,0.001);
	typedef Policy_Is_Inbound_Filling_Layer_CellType<type_data_ref> type_pol_is_inbound_filling_layer;
	type_pol_is_inbound_filling_layer m_pol_is_inbound_filling_layer;
	typedef Policies<type_pol_layer,type_pol_check_dt,type_pol_is_inbound_filling_layer> type_pol_init;
	type_pol_init m_pol_init(m_pol_layer,m_pol_check_dt,m_pol_is_inbound_filling_layer);

	//Algorithm Init
	typedef Algorithms_Update_CellType_Layer<type_data_ref,type_pol_init> type_alg_update_celltype;
	type_alg_update_celltype m_alg_update_celltype(m_data_ref,m_pol_init);
	typedef Algorithms_Delete_MacCell<type_data_ref,type_pol_init> type_alg_delete_maccell;
	type_alg_delete_maccell m_alg_delete_maccell(m_data_ref,m_pol_init);
	typedef Algorithms_Calculate_Time_Step<type_data_ref,type_pol_init> type_alg_calculate_time_step;
	type_alg_calculate_time_step m_alg_calculate_time_step(m_data_ref,m_pol_init);
	typedef Algorithms_Extrapolate<type_data_ref,type_pol_init> type_alg_extrapolate_init;
	type_alg_extrapolate_init m_alg_extrapolate_init(m_data_ref,m_pol_init);

	typedef Algorithms<type_alg_update_celltype,type_alg_delete_maccell,type_alg_extrapolate_init,type_alg_calculate_time_step> type_alg_init;
	type_alg_init m_alg_init(m_alg_update_celltype,m_alg_delete_maccell,m_alg_extrapolate_init,m_alg_calculate_time_step);


	// Policy Solve Grid
	typedef Policy_Gravity<type_data_ref> type_pol_gravity;
	type_pol_gravity m_pol_gravity(m_data_ref,-9.81,2);
	typedef Policy_Laplacian<type_data_ref> type_pol_laplacian;
	type_pol_laplacian m_pol_laplacian(m_data_ref);
	typedef Policy_Laplacian_Speed<type_data_ref> type_pol_laplacian_speed;
	type_pol_laplacian_speed m_pol_laplacian_speed(m_data_ref);
	typedef Policy_Viscosity_Apply_If<type_data_ref> type_pol_viscosity_apply_if;
	type_pol_viscosity_apply_if m_pol_viscosity_apply_if;
	typedef Policy_Solve_Linear_Umfpack<double> type_pol_solve_linear;
	type_pol_solve_linear m_pol_solve_linear;
	typedef Policy_Divergence<type_data_ref> type_pol_divergence;
	type_pol_divergence m_pol_divergence(m_data_ref);
	typedef Policy_Gradiant<type_data_ref> type_pol_gradiant;
	type_pol_gradiant m_pol_gradiant(m_data_ref);
	typedef Policy_Von_Neumann_Boundary<type_data_ref> type_pol_von_neumann_boundary;
	type_pol_von_neumann_boundary m_pol_von_neumann_boundary(m_data_ref);
	typedef Policy_Speed_Interpolation_Linear_Symmetric<type_data_ref> type_pol_speed_interpolation;
	type_pol_speed_interpolation m_pol_speed_interpolation(m_data_ref);
	typedef Policy_Convection_Apply_If<type_data_ref> type_pol_convection_apply_if;
	type_pol_convection_apply_if m_pol_convection_apply_if;
	typedef Policy_Upwind_1_Order<type_data_ref,type_pol_speed_interpolation> type_pol_convection;
	type_pol_convection m_pol_convection(m_data_ref,m_pol_speed_interpolation);
	typedef Policy_Pressure_If_Correction<type_data_ref> type_pol_pres_cor_if;
	type_pol_pres_cor_if m_pol_pres_cor_if;

	typedef Policies<type_pol_gravity,type_pol_laplacian,type_pol_laplacian_speed,type_pol_viscosity_apply_if,type_pol_solve_linear,type_pol_divergence,type_pol_gradiant,type_pol_von_neumann_boundary,type_pol_convection_apply_if,type_pol_convection,type_pol_pres_cor_if> type_pol_solve_grid;
	type_pol_solve_grid m_pol_solve_grid(m_pol_gravity,m_pol_laplacian,m_pol_laplacian_speed,m_pol_viscosity_apply_if,m_pol_solve_linear,m_pol_divergence,m_pol_gradiant,m_pol_von_neumann_boundary,m_pol_convection_apply_if,m_pol_convection,m_pol_pres_cor_if);

	//Algorithms Solve Grid
	typedef Algorithms_Gravity<type_data_ref,type_pol_solve_grid> type_alg_gravity;
	type_alg_gravity m_alg_gravity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Viscosity<type_data_ref,type_pol_solve_grid> type_alg_viscosity;
	type_alg_viscosity m_alg_viscosity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Convection<type_data_ref,type_pol_solve_grid> type_alg_convection;
	type_alg_convection m_alg_convection(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Solve_Pressure<type_data_ref,type_pol_solve_grid> type_alg_solve_pressure;
	type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_solve_grid);

	typedef Algorithms<type_alg_gravity,type_alg_viscosity,type_alg_convection,type_alg_solve_pressure> type_alg_solve_grid;
	type_alg_solve_grid m_alg_solve_grid(m_alg_gravity,m_alg_viscosity,m_alg_convection,m_alg_solve_pressure);

	typedef Algorithms<type_alg_init,type_alg_solve_grid> type_alg;
	type_alg m_alg(m_alg_init,m_alg_solve_grid);

	//Policy Fluid To Layer
	typedef Policies<> type_pol_fluid_to_layer;
	type_pol_fluid_to_layer m_pol_fluid_to_layer;

	//Algorithms Fluid to Layer
	typedef Algorithms_Fluid_To_Layer<type_data_ref,type_pol_fluid_to_layer> type_alg_fluid_to_layer;
	type_alg_fluid_to_layer m_alg_fluid_to_layer(m_data_ref,m_pol_fluid_to_layer);

	for(int i=1;i<10;++i)
	{
		m_alg.Do();
		m_data_ref.m_data.GetTimingData().m_t+=m_data_ref.m_data.GetTimingData().m_dt;
		m_alg_fluid_to_layer.Do();
	}
	SingletonManager::Kill();
}
