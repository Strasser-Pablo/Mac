#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Grid_Layer.h"
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_Grid_CellType_To_Grid_CellType.h"
#include "../src/DataRef.h"
#include "../src/Policies.h"
#include "../src/Policy_CheckDT.h"
#include "../src/Algorithms_Calculate_Time_Step.h"
#include "../src/Empty.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Data_Grid_Data.h"
#include "../src/Data_Timing.h"
#include "../src/Data_Timing_Time.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Data_Grid_Pressure.h"
#include "../src/Data_Topology.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"
#include "../src/Policy_Solve_Linear_Umfpack.h"
#include "../src/Policy_Gradiant.h"
#include "../src/Policy_Divergence.h"
#include "../src/Algorithms_Solve_Pressure.h"
#include "../src/Data_CellType_Interface_Constant.h"
#include "../src/Data_CellType_Domain_Fluid.h"
#include "../src/Policy_Von_Neumann_Boundary.h"
#include "../src/Policy_Pressure_If_Correction.h"
#define eps 1e-10
class TestAlgorithms_Solve_Pressure : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	~TestAlgorithms_Solve_Pressure()
	{
		SingletonManager::Kill();
	}
	void test1()
	{
		const int DIM=1;
		const int N=4;
		const int NStock=pow(4,DIM);
		typedef Data_Base_Dim_Type<double,DIM> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
		type_empt_lay m_empt_lay(layer);

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;

		v.Set(1,0);
		Physvector<1,double> speed;
		speed.Set(1,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		v.Set(1,1);
		speed.Set(1,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		v.Set(1,-1);
		speed.Set(1,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(1);
		
		v.Set(1,2);
		speed.Set(1,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(1);

		alg_solve.Do();
		
		v.Set(1,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.0,eps);
		v.Set(1,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.0,eps);
	}

	void test2()
	{
		const int DIM=2;
		const int N=10;
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

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,1);
		m_h.Set(2,1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,2.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,-1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,-1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,-2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,0);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,0);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		alg_solve.Do();
		
		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.25,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.25,eps);

		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.25,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.24999999999999988898,eps);

		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.24999999999999988898,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.25,eps);

		v.Set(1,-1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.75,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.75,eps);

		v.Set(1,0);
		v.Set(2,-1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.75,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.75,eps);
	}

	void test1h()
	{
		const int DIM=1;
		const int N=4;
		const int NStock=pow(4,DIM);
		typedef Data_Base_Dim_Type<double,DIM> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
		type_empt_lay m_empt_lay(layer);

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;
		v.Set(1,0);
		Physvector<1,double> speed;
		speed.Set(1,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		v.Set(1,1);
		speed.Set(1,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		v.Set(1,-1);
		speed.Set(1,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(1);

		v.Set(1,2);
		speed.Set(1,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(1);

		alg_solve.Do();
		
		v.Set(1,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.0,eps);
		v.Set(1,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.0,eps);
	}

	void test2h()
	{
		const int DIM=2;
		const int N=4;
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

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,0.1);
		m_h.Set(2,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,2.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,-1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,-1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,-2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,0);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		
		v.Set(1,0);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		alg_solve.Do();
		
		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.25,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.25,eps);

		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.25,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.25,eps);

		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.25,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.25,eps);

		v.Set(1,-1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.75,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.75,eps);

		v.Set(1,0);
		v.Set(2,-1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),0.75,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),0.75,eps);
	}

	void test3h()
	{
		const int DIM=2;
		const int N=4;
		const int NStock=pow(4,DIM);
		typedef Data_Base_Dim_Type<double,DIM> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
		type_empt_lay m_empt_lay(layer);

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,0.1);
		m_h.Set(2,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,2.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,0);
		speed.Set(1,0.0);
		speed.Set(2,0.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		alg_solve.Do();
		
		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.5,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.5,eps);

		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.5,eps);

		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.5,eps);
	}

	void test4h()
	{
		const int DIM=2;
		const int N=4;
		const int NStock=pow(4,DIM);
		typedef Data_Base_Dim_Type<double,DIM> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
		type_empt_lay m_empt_lay(layer);

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_pressure m_grid_pressure;

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);

		typedef Data_CellType_Domain_Fluid<type_grid_celltype>  type_grid_celltype2;
		type_grid_celltype2 m_grid_celltype2(m_grid_celltype);

		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype2> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype2);

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk_Speed<type_grid_speed,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);

		typedef Data_Chunk_Pressure<type_grid_pressure,NStock> type_chunk_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed,type_chunk_pressure> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed,m_chunk_pressure);

		typedef Neighbour_List_Empty<DIM,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,DIM,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<DIM,int> vect;
		typedef Physvector<DIM,double> vectdouble;
		typedef HashPhysvector<DIM,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<DIM,double> m_h;
		m_h.Set(1,0.1);
		m_h.Set(2,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Staggered_Left<type_data_grid_base_spacing> type_stag_left;
		type_stag_left m_stag_left(m_data_grid_base_spacing);
		typedef Data_CellType_Interface_Constant<type_stag_left> type_celltype_constant;
		type_celltype_constant m_celltype_constant(m_data_grid_base_spacing);

		typedef Data_Grid_Data<type_celltype_constant,Empty> type_grid_data;
		type_grid_data m_grid_data(m_celltype_constant,Empty());
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		typedef Policy_Solve_Linear_Umfpack<double> type_solve; 
		type_solve p_solve;
		typedef Policy_Gradiant<type_data_ref> type_grad;
		type_grad p_grad(m_data_ref);
		typedef Policy_Divergence<type_data_ref> type_div;
		type_div p_div(m_data_ref);
		typedef Policy_Von_Neumann_Boundary<type_data_ref> type_neu;
		type_neu p_neu(m_data_ref);
		typedef Policy_Pressure_If_Correction<type_data_ref> type_pres_cor;
		type_pres_cor p_pres_cor;

		typedef Policies<type_solve,type_grad,type_div,type_neu,type_pres_cor> type_pol;
		type_pol pol(p_solve,p_grad,p_div,p_neu,p_pres_cor);
		Algorithms_Solve_Pressure<type_data_ref,type_pol> alg_solve(m_data_ref,pol);

		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,2.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1);
		speed.Set(2,1);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,0);
		speed.Set(1,0.0);
		speed.Set(2,0.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,-2);
		v.Set(2,0);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,2);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,-1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,1);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-2);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,-2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,2);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,3);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,3);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();

		v.Set(1,1);
		v.Set(2,3);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,4);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set_Const(2);

		v.Set(1,1);
		v.Set(2,4);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,4);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,0);
		v.Set(2,5);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,-1);
		v.Set(2,5);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		v.Set(1,1);
		v.Set(2,5);
		speed.Set(1,0);
		speed.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));

		alg_solve.Do();
		
		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.5,eps);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.5,eps);

		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(1),1.5,eps);

		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_DELTA(m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Get(2),1.5,eps);
	}
};
