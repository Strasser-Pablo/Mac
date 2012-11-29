//Vector
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"

//HashTable+Neighbour
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Hook_Neighbour_List_Chunk.h"

//Data_Chunk
#include "../src/Data_Chunk_Layer.h"
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
#include "../src/Data_CellType_Interface_Constant_With_0_Pres.h"

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

using namespace std;

int main()
{
	const int DIM=2;
	const int NBSpeed=3;
	double length=.10;
	int NBX=10;
	double spacing=length/NBX;
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

	typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
	type_neigh m_neigh(m_chunk);

	typedef Offset<int,DIM,N> type_off;
	typedef Offset_Base<type_off,type_neigh> type_off_base;
	typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
	typedef Offset_Base_Id_Cell<type_empt_id,type_off_base_layer> type_off_base_id;
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
	// watter viscosity at 10 c
	m_data_viscosity.m_viscosity=1.307e-6;
	typedef Data_Grid_Base_Spacing<type_data_viscosity,Physvector<DIM,type_data_value> > type_data_grid;
	type_data_grid m_data_grid(m_data_viscosity);
	Physvector<DIM,type_data_value> h;
	h.Set(1,spacing);
	h.Set(2,spacing);
	m_data_grid.m_h.Set(h);
	typedef Data_Staggered_Left<type_data_grid> type_data_stag_left;
	type_data_stag_left m_data_stag_left(m_data_grid);
	typedef Data_CellType_Interface_Constant_With_0_Pres<type_data_stag_left> type_interface_constant;
	type_interface_constant m_type_interface_constant(m_data_stag_left);
	typedef Data_Grid_Data<type_interface_constant,DataBase> type_grid_data;
	type_grid_data m_grid_data(m_type_interface_constant,base);


	// Data Timming
	typedef Data_Timing_Time<type_data_value> type_time;
	type_time m_time;
	m_time.m_t=0;
	m_time.m_factor=0.1;
	m_time.m_dt=1;
	typedef Data_Timing<type_time,type_grid_data> type_timing;
	type_timing m_timing(m_time,m_grid_data);

	//Data Ref
	typedef DataRef<type_timing> type_data_ref;
	type_data_ref m_data_ref(m_timing);

	//Initial Data
	vect v;
	int imax=NBX-1;
	int jmax=NBX-1;
	for(int i=0;i<=imax;++i)
	{
		for(int j=0;j<=jmax;++j)
		{
			v.Set(1,i);
			v.Set(2,j);

			Physvector<DIM,type_data_value> speed;
			speed.Set(1,0.0);
			if(i<imax/2)
			{
				speed.Set(2,value);
			}
			else
			{
				speed.Set(2,-value);
			}
			m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
			m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		}
	}
	for(int i=-1;i<=imax+1;i+=imax+2)
	{
		for(int j=-1;j<=jmax+1;++j)
		{
			v.Set(1,i);
			v.Set(2,j);

			Physvector<DIM,type_data_value> speed;
			speed.Set(1,0.0);
			if(i<imax/2)
			{
				speed.Set(2,value);
			}
			else
			{
				speed.Set(2,-value);
			}
			m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
			m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(1);
			if(i!=-1)
			{
				m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
				v.Set(1,i-1);
				m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);
			}
			else
			{
				m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
				m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set_Const(2);
			}
		}
	}
	for(int i=-1;i<=imax+1;++i)
	{
		for(int j=-1;j<=jmax+1;j+=jmax+2)
		{
			v.Set(1,i);
			v.Set(2,j);

			Physvector<DIM,type_data_value> speed;
			speed.Set(1,0.0);
			if(i<imax/2)
			{
				speed.Set(2,value);
			}
			else
			{
				speed.Set(2,-value);
			}
			m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Set(Data_Speed_Data<DIM,type_data_value>(speed),true);
			m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetAir();
		}
	}


	//Policy First Init
	typedef Policy_Layer_Max<type_data_ref> type_pol_layer_max;
	type_pol_layer_max m_pol_layer_max(2);
	typedef Policies<type_pol_layer_max> type_pol_init_first;
	type_pol_init_first m_pol_init_first(m_pol_layer_max);

	//Algorithms first init
	typedef Algorithms_Fluid_To_Layer<type_data_ref,type_pol_init_first> type_alg_fluid_to_layer;
	type_alg_fluid_to_layer m_alg_fluid_to_layer(m_data_ref,m_pol_init_first);
	typedef Algorithms_Update_CellType_Layer<type_data_ref,type_pol_init_first> type_alg_layer;
	type_alg_layer m_alg_layer(m_data_ref,m_pol_init_first);

	typedef Algorithms<type_alg_fluid_to_layer,type_alg_layer> type_alg_first_init;
	type_alg_first_init m_alg_first_init(m_alg_fluid_to_layer,m_alg_layer);

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

	typedef Policies<type_pol_gravity,type_pol_laplacian,type_pol_laplacian_speed,type_pol_viscosity_apply_if,type_pol_convection_apply_if,type_pol_convection> type_pol_solve_grid;
	type_pol_solve_grid m_pol_solve_grid(m_pol_gravity,m_pol_laplacian,m_pol_laplacian_speed,m_pol_viscosity_apply_if,m_pol_convection_apply_if,m_pol_convection);

	//Algorithms Solve Grid
	typedef Algorithms_Extrapolate<type_data_ref,type_pol_solve_grid> type_alg_extrapolate;
	type_alg_extrapolate m_alg_extrapolate(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Gravity<type_data_ref,type_pol_solve_grid> type_alg_gravity;
	type_alg_gravity m_alg_gravity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Viscosity<type_data_ref,type_pol_solve_grid> type_alg_viscosity;
	type_alg_viscosity m_alg_viscosity(m_data_ref,m_pol_solve_grid);
	typedef Algorithms_Convection<type_data_ref,type_pol_solve_grid> type_alg_convection;
	type_alg_convection m_alg_convection(m_data_ref,m_pol_solve_grid);

	typedef Algorithms<type_alg_extrapolate,/*type_alg_gravity,*/type_alg_viscosity,type_alg_convection> type_alg_solve_grid;
	type_alg_solve_grid m_alg_solve_grid(m_alg_extrapolate,/*m_alg_gravity,*/m_alg_viscosity,m_alg_convection);


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
	typedef Algorithms_Solve_Pressure_Fixed<type_data_ref,type_pol_pressure> type_alg_solve_pressure;
	type_alg_solve_pressure m_alg_solve_pressure(m_data_ref,m_pol_pressure);

	//Policy ODE integrator
	typedef Policies<type_alg_solve_grid,type_alg_solve_pressure> type_pol_ODE;
	type_pol_ODE m_pol_ODE(m_alg_solve_grid,m_alg_solve_pressure);

	//Algorithms ODE integrator
//	typedef Algorithms_Euler<type_data_ref,type_pol_ODE> type_alg_ODE;
	typedef Algorithms_RungeKutta<type_data_ref,type_pol_ODE> type_alg_ODE;
//	typedef Algorithms_RungeKutta_RK2<type_data_ref,type_pol_ODE> type_alg_ODE;
//	typedef Algorithms_RungeKutta_RK2_TVD<type_data_ref,type_pol_ODE> type_alg_ODE;
	type_alg_ODE m_alg_ODE(m_data_ref,m_pol_ODE);

	//Policy Output
	typedef Policy_Output_Grid_Speed_ID<type_data_ref> type_pol_output_speed;
	type_pol_output_speed m_pol_output_speed(m_data_ref,"out_speed_");
	typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_output_pressure;
	type_pol_output_pressure m_pol_output_pressure(m_data_ref,"out_press_");
	typedef Policy_Output_Animation<type_data_ref> type_pol_output_animation;
	type_pol_output_animation m_pol_output_animation(m_data_ref,"Out_Animation.pvd");
	typedef Policies<type_pol_output_speed,type_pol_output_pressure,type_pol_output_animation> type_pol_output;
	type_pol_output m_pol_output(m_pol_output_speed,m_pol_output_pressure,m_pol_output_animation);

	//Algorithms Output
	typedef Algorithms_Output_Speed_Pressure<type_data_ref,type_pol_output> type_alg_output;
	type_alg_output m_alg_output(m_data_ref,m_pol_output);

	m_alg_first_init.Do();
	m_alg_extrapolate.Do();
    m_alg_output.Do();
	int k=0;
    for(int i=1;i<2;++i)
	{
		cout<<"i "<<i<<endl;
		m_alg_ODE.Do();
		m_data_ref.m_data.GetTimingData().m_t+=m_data_ref.m_data.GetTimingData().m_dt;
		cout<<"dt "<<m_data_ref.m_data.GetTimingData().m_dt<<endl;
		cout<<"t "<<m_data_ref.m_data.GetTimingData().m_t<<endl;
		if(m_data_ref.m_data.GetTimingData().m_t>=k-m_data_ref.m_data.GetTimingData().m_dt/2)
		{
			++k;
			cout<<"out "<<endl;
			m_alg_output.Do();
		}
	}
	SingletonManager::Kill();
    cout<<"finished"<<endl;
    return 0;
}
