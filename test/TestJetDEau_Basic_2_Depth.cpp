//Vector
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"

//HashTable+Neighbour
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Hook_Neighbour_List_Chunk.h"

//Data_Chunk
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_Depth.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Id_Cell.h"

//Offset
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Depth.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_Id_Cell.h"
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
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow_Interior.h"
#include "../src/Data_CellType_Domain_Fluid.h"
#include "../src/Data_Grid_CellType_To_Grid_CellType.h"

//Data Grid Speed
#include "../src/Data_Grid_Speed.h"

//Data Grid Pressure
#include "../src/Data_Grid_Pressure.h"

//Data Grid Layer
#include "../src/Data_Grid_Layer.h"
#include "../src/Data_Grid_Layer_Empty.h"

//Data Grid Depth
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
#include "../src/Policy_Wind.h"
#include "../src/Policy_Depth.h"
/// To add Convection

//Algorithms

//Const
#include "../src/Algorithms_Speed_Constant_Mirror.h"
#include "../src/Algorithms_Extrapolate.h"
// Initialisation
#include "../src/Algorithms_Initialize_Layer_And_Depth.h"
#include "../src/Algorithms_Create_Fluid_Particle_Depth.h"
#include "../src/Algorithms_Layer_Initial_With_Particle_Depth.h"
#include "../src/Algorithms_Calculate_Time_Step.h"
#include "../src/Algorithms_Delete_MacCell.h"
#include "../src/Algorithms_Update_CellType_Layer_Depth.h"
#include "../src/Algorithms_Inflow_To_Const.h"
#include "../src/Algorithms_Solid_To_Const.h"

// Solve Grid
#include "../src/Algorithms_Gravity.h"
#include "../src/Algorithms_Viscosity.h"
#include "../src/Algorithms_Solve_Pressure.h"
#include "../src/Algorithms_Solve_Pressure_Empty_Pressure.h"
#include "../src/Algorithms_Convection.h"
#include "../src/Algorithms_Apply_Wind.h"

//Integrator
#include "../src/Algorithms_Euler.h"
#include "../src/Algorithms_RungeKutta.h"
#include "../src/Algorithms_RungeKutta_RK2.h"
#include "../src/Algorithms_RungeKutta_RK2_TVD.h"

//Move Particle
#include "../src/Algorithms_Move_Particles.h"

// Output
#include "../src/Algorithms_Output.h"

#include <sys/times.h>
#include <stdlib.h>

#include <bitset>

using namespace std;

int main()
{
	srand(1);
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

	typedef Data_Grid_Depth<int> type_depth;
	type_depth depth;
	typedef Data_Grid_Depth_Empty<type_depth> type_empt_depth;
	type_empt_depth m_empt_depth(depth);

	typedef bitset<DIM> type_const;
	type_const m_const;
	typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
	type_grid_speed m_grid_speed(m_const);

	typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
	type_grid_pressure m_grid_pressure;

	typedef Data_CellType_Fluid_Air_Solid_Inflow_Interior<DataBase> type_grid_celltype;
	type_grid_celltype m_grid_celltype;
	Inversible_Value<type_data_value> rho_air(1);
	Inversible_Value<type_data_value> rho_fluid(1000);
	m_grid_celltype.SetRhoAir(rho_air);
	m_grid_celltype.SetRhoFluid(rho_fluid);

	typedef Data_CellType_Domain_Fluid<type_grid_celltype> type_cell_type;
	type_cell_type m_celltype(m_grid_celltype);

	typedef Data_Grid_CellType_To_Grid_CellType<type_cell_type> type_cell_grid_celltype;
	type_cell_grid_celltype m_cell_grid_celltype(m_celltype);

	typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
	type_chunk_layer m_chunk_layer(m_empt_lay);

	typedef Data_Chunk_Depth<type_empt_depth,NStock> type_chunk_depth;
	type_chunk_depth m_chunk_depth(m_empt_depth);

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

	typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_depth,type_chunk_id,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
	type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_depth,m_chunk_id,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

	typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
	type_neigh m_neigh(m_chunk);

	typedef Offset<int,DIM,N> type_off;
	typedef Offset_Base<type_off,type_neigh> type_off_base;
	typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
	typedef Offset_Base_Depth<type_empt_depth,type_off_base_layer> type_off_base_depth;
	typedef Offset_Base_Id_Cell<type_empt_id,type_off_base_depth> type_off_base_id;
	typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_id> type_off_base_celltype;
	typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
	typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
	typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
	typedef Physvector<DIM,int> vect;
	typedef Physvector<DIM,double> vectdouble;
	typedef HashPhysvector<DIM,int> Hash;
	Hash hash;
	typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
	type_chunk_table m_chunk_table(m_neigh,hash);

	typedef Data_Viscosity<type_chunk_table> type_data_viscosity;
	type_data_viscosity m_data_viscosity(m_chunk_table);
	m_data_viscosity.m_viscosity=1.3e-6;
	typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value> > type_data_grid;
	type_data_grid m_data_grid(m_data_viscosity);
	Physvector<DIM,type_data_value> h;
	h.Set(1,0.002);
	h.Set(2,0.002);
	m_data_grid.m_h.Set(h);
	typedef Data_Staggered_Left<type_data_grid> type_data_stag_left;
	type_data_stag_left m_data_stag_left(m_data_grid);
	typedef Data_CellType_Interface_Constant<type_data_stag_left> type_interface_constant;
	type_interface_constant m_type_interface_constant(m_data_stag_left);
	typedef Data_Grid_Data<type_interface_constant,DataBase> type_grid_data;
	type_grid_data m_grid_data(m_type_interface_constant,base);

	// Data Particle
	typedef Data_Particle<DataBase> type_particle;
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
	vect v;
	int y0=0;
	int imax=10;
	for(int i=-10;i<=imax;++i)
	{
		v.Set(1,i);
		v.Set(2,y0);

		Physvector<DIM,type_data_value> speed;
		speed.Set(1,0.0);
		speed.Set(2,5.0+rand()%100*0.01);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetInflow();
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);

		v.Set(2,y0+1);
		speed.Set(1,0.0);
		speed.Set(2,5+rand()%100*0.01);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed));
	}
	Physvector<DIM,type_data_value> speed;
	v.Set(2,y0);
	v.Set(1,imax+1);
	speed.Set(1,0.0);
	speed.Set(2,0.0);
	m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed));
	m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(1);

	//Policy First Init
	typedef Policies<> type_pol_init_first;
	type_pol_init_first m_pol_init_first;

	//Algorithms first init
	typedef Algorithms_Speed_Constant_Mirror<type_data_ref,type_pol_init_first> type_alg_speed_constant_mirror;
	type_alg_speed_constant_mirror m_alg_speed_constant_mirror(m_data_ref,m_pol_init_first);
	typedef Algorithms_Extrapolate<type_data_ref,type_pol_init_first> type_alg_extrapolate_init;
	type_alg_extrapolate_init m_alg_extrapolate_init(m_data_ref,m_pol_init_first);

	//Policy Init
	typedef Policy_Layer_Max<type_data_ref> type_pol_layer;
	type_pol_layer m_pol_layer(4);
	typedef Policy_Particle_To_Key<type_data_ref> type_pol_part_to_key;
	type_pol_part_to_key m_pol_part_to_key(m_data_ref);
	typedef Policy_CheckDT<type_data_ref> type_pol_check_dt;
	type_pol_check_dt m_pol_check_dt(0.00,0.0001);
	typedef Policy_Add_Particle_Cube<type_data_ref> type_pol_add_particle;
	type_pol_add_particle m_add_particle(m_data_ref,1);
	typedef Policy_Is_Inbound_Filling_Layer_CellType<type_data_ref> type_pol_is_inbound_filling_layer;
	type_pol_is_inbound_filling_layer m_pol_is_inbound_filling_layer;
	typedef Policy_Depth<type_data_ref> type_pol_depth;
	type_pol_depth m_pol_depth(10,1,4);
	typedef Policies<type_pol_layer,type_pol_part_to_key,type_pol_check_dt,type_pol_add_particle,type_pol_is_inbound_filling_layer,type_pol_depth> type_pol_init;
	type_pol_init m_pol_init(m_pol_layer,m_pol_part_to_key,m_pol_check_dt,m_add_particle,m_pol_is_inbound_filling_layer,m_pol_depth);

	//Algorithm Init
	typedef Algorithms_Initialize_Layer_And_Depth<type_data_ref,type_pol_init> type_alg_initialize_mac;
	type_alg_initialize_mac m_alg_initialize_mac(m_data_ref,m_pol_init);
	typedef Algorithms_Layer_Initial_With_Particle_Depth<type_data_ref,type_pol_init> type_alg_layer_initial;
	type_alg_layer_initial m_alg_layer_initial(m_data_ref,m_pol_init);
	typedef Algorithms_Create_Fluid_Particle_Depth<type_data_ref,type_pol_init> type_alg_create_fluid_particle;
	type_alg_create_fluid_particle m_alg_create_fluid_particle(m_data_ref,m_pol_init);
	typedef Algorithms_Update_CellType_Layer_Depth<type_data_ref,type_pol_init> type_alg_update_celltype;
	type_alg_update_celltype m_alg_update_celltype(m_data_ref,m_pol_init);
	typedef Algorithms_Delete_MacCell<type_data_ref,type_pol_init> type_alg_delete_maccell;
	type_alg_delete_maccell m_alg_delete_maccell(m_data_ref,m_pol_init);
	typedef Algorithms_Calculate_Time_Step<type_data_ref,type_pol_init> type_alg_calculate_time_step;
	type_alg_calculate_time_step m_alg_calculate_time_step(m_data_ref,m_pol_init);

	typedef Algorithms<type_alg_initialize_mac,type_alg_layer_initial,type_alg_create_fluid_particle,type_alg_update_celltype,type_alg_delete_maccell,type_alg_calculate_time_step> type_alg_init;
	type_alg_init m_alg_init(m_alg_initialize_mac,m_alg_layer_initial,m_alg_create_fluid_particle,m_alg_update_celltype,m_alg_delete_maccell,m_alg_calculate_time_step);


	typedef Algorithms<type_alg_initialize_mac,type_alg_create_fluid_particle,type_alg_layer_initial,type_alg_update_celltype,type_alg_delete_maccell,type_alg_extrapolate_init> type_alg_first_init;
	type_alg_first_init m_alg_first_init(m_alg_initialize_mac,m_alg_create_fluid_particle,m_alg_layer_initial,m_alg_update_celltype,m_alg_delete_maccell,m_alg_extrapolate_init);

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
	type_pol_convection m_pol_convection(m_data_ref,m_pol_speed_interpolation);
	typedef Policy_Wind<type_data_ref> type_pol_wind;
	type_pol_wind m_pol_wind(100,1,1);

	typedef Policies<type_pol_gravity,type_pol_laplacian,type_pol_laplacian_speed,type_pol_viscosity_apply_if,type_pol_convection_apply_if,type_pol_convection,type_pol_wind> type_pol_solve_grid;
	type_pol_solve_grid m_pol_solve_grid(m_pol_gravity,m_pol_laplacian,m_pol_laplacian_speed,m_pol_viscosity_apply_if,m_pol_convection_apply_if,m_pol_convection,m_pol_wind);


	//Algorithms Solve Grid
	typedef Algorithms_Gravity<type_data_ref,type_pol_solve_grid> type_alg_gravity;
	type_alg_gravity m_alg_gravity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Viscosity<type_data_ref,type_pol_solve_grid> type_alg_viscosity;
	type_alg_viscosity m_alg_viscosity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Convection<type_data_ref,type_pol_solve_grid> type_alg_convection;
	type_alg_convection m_alg_convection(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Apply_Wind<type_data_ref,type_pol_solve_grid> type_alg_wind;
	type_alg_wind m_alg_wind(m_data_ref,m_pol_solve_grid);

	typedef Algorithms<type_alg_gravity,type_alg_viscosity,type_alg_convection,type_alg_wind> type_alg_solve_grid;
	type_alg_solve_grid m_alg_solve_grid(m_alg_gravity,m_alg_viscosity,m_alg_convection,m_alg_wind);


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

	typedef Policies<type_pol_solve_linear,type_pol_pres_cor_if,type_pol_gradiant,type_pol_von_neumann_boundary,type_pol_divergence> type_pol_pressure;
	type_pol_pressure m_pol_pressure(m_pol_solve_linear,m_pol_pres_cor_if,m_pol_gradiant,m_pol_von_neumann_boundary,m_pol_divergence);
	
	//Algorithms Solve Pressure
	typedef Algorithms_Solve_Pressure<type_data_ref,type_pol_pressure> type_alg_solve_pressure;
	//typedef Algorithms_Solve_Pressure_Empty_Pressure<type_data_ref> type_alg_solve_pressure;
	type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_pressure);
	//type_alg_solve_pressure m_alg_solve_pressure(m_data_ref);

	//Policy ODE integrator
	typedef Policies<type_alg_solve_grid,type_alg_solve_pressure> type_pol_ODE;
	type_pol_ODE m_pol_ODE(m_alg_solve_grid,m_alg_solve_pressure);

	//Algorithms ODE integrator
//	typedef Algorithms_Euler<type_data_ref,type_pol_ODE> type_alg_ODE;
	typedef Algorithms_RungeKutta<type_data_ref,type_pol_ODE> type_alg_ODE;
//	typedef Algorithms_RungeKutta_RK2<type_data_ref,type_pol_ODE> type_alg_ODE;
//	typedef Algorithms_RungeKutta_RK2_TVD<type_data_ref,type_pol_ODE> type_alg_ODE;
	type_alg_ODE m_alg_ODE(m_data_ref,m_pol_ODE);

	//Policy Move
	typedef Policy_Advance_Ode_RungeKutta<type_data_ref> type_pol_advance_ode;
	type_pol_advance_ode m_pol_advance_ode;
	typedef Policy_Speed_Interpolation_Linear_Symmetric<type_data_ref> type_pol_interpolation;
	type_pol_interpolation m_pol_interpolation(m_data_ref);
	typedef Policies<type_pol_advance_ode,type_pol_interpolation> type_pol_move;
	type_pol_move m_pol_move(m_pol_advance_ode,m_pol_interpolation);

	//Algorithms Move
	typedef Algorithms_Move_Particles<type_data_ref,type_pol_move> type_alg_move;
	type_alg_move m_alg_move(m_data_ref,m_pol_move);

	//Policy Output
	typedef Policy_Output_Grid_Speed<type_data_ref> type_pol_output_speed;
	type_pol_output_speed m_pol_output_speed(m_data_ref,"out_speed_");
	typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_output_pressure;
	type_pol_output_pressure m_pol_output_pressure(m_data_ref,"out_press_");
	typedef Policy_Output_Particle<type_data_ref> type_pol_output_particle;
	type_pol_output_particle m_pol_output_particle(m_data_ref,"out_part_");
	typedef Policy_Output_Animation<type_data_ref> type_pol_output_animation;
	type_pol_output_animation m_pol_output_animation(m_data_ref,"Out_Animation.pvd");
	typedef Policies<type_pol_output_speed,type_pol_output_pressure,type_pol_output_particle,type_pol_output_animation> type_pol_output;
	type_pol_output m_pol_output(m_pol_output_speed,m_pol_output_pressure,m_pol_output_particle,m_pol_output_animation);

	//Algorithms Output
	typedef Algorithms_Output<type_data_ref,type_pol_output> type_alg_output;
	type_alg_output m_alg_output(m_data_ref,m_pol_output);

	m_alg_first_init.Do();
	for(int i=1;;++i)
	{
		cout<<"i "<<i<<endl;
		struct tms t1;
		struct tms t2;
		struct tms to1;
		struct tms to2;
		struct tms ta1;
		struct tms ta2;
		struct tms tb1;
		struct tms tb2;
		struct tms tc1;
		struct tms tc2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		long ta_deb=times(&ta1);
		long tb_deb=times(&tb1);
		m_alg_init.Do();
		long tb_end=times(&tb2);
		long tc_deb=times(&tc1);
		m_alg_ODE.Do();
		long tc_end=times(&tc2);
		m_alg_extrapolate_init.Do();
		long ta_end=times(&ta2);
		m_alg_move.Do();
		m_data_ref.m_data.GetTimingData().m_t+=m_data_ref.m_data.GetTimingData().m_dt;
		cout<<"dt "<<m_data_ref.m_data.GetTimingData().m_dt<<endl;
		cout<<"t "<<m_data_ref.m_data.GetTimingData().m_t<<endl;
		if(i%20==1)
		{
			long to_deb=times(&to1);
			m_alg_output.Do();
			long to_end=times(&to2);
			cout<<"real output "<<(to_end-to_deb)/conv<<endl;
			cout<<"user output "<<(to2.tms_utime-to1.tms_utime)/conv<<endl;
		}
		long t_end=times(&t2);

		cout<<"real alg solve "<<(tc_end-tc_deb)/conv<<endl;
		cout<<"user alg solve "<<(tc2.tms_utime-tc1.tms_utime)/conv<<endl;

		cout<<"real alg init "<<(tb_end-tb_deb)/conv<<endl;
		cout<<"user alg init "<<(tb2.tms_utime-tb1.tms_utime)/conv<<endl;

		cout<<"real alg "<<(ta_end-ta_deb)/conv<<endl;
		cout<<"user alg "<<(ta2.tms_utime-ta1.tms_utime)/conv<<endl;

		cout<<"real "<<(t_end-t_deb)/conv<<endl;
		cout<<"user "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
	SingletonManager::Kill();
}
