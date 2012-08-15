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
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Data_Timing.h"
#include "../src/Data_Timing_Time.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Grid_Speed.h"
#include "../src/Policy_Output_Grid_Pressure.h"
#include "../src/Algorithms_Output.h"
#include "../src/Policy_Output_Animation.h"
#define eps 1e-10
class TestAlgorithms_Output : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	~TestAlgorithms_Output()
	{
		SingletonManager::Kill();
	}
	void test1()
	{
		const int DIM=1;
		const int N=2;
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
		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype);

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
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);

		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);

		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);

		vect v;
		v.Set(1,0);
		Physvector<1,double> speed;
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		v.Set(1,1);
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		v.Set(1,-1);
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		type_particle part;
		part.GetParticlePosRef().Set(1,2.2);
		m_data_ref.m_data.GetTopologyData().GetRefToParticleList().push_back(part);
		
		m_data_ref.m_data.GetTimingData().m_t=1;

		typedef Policy_Output_Grid_Speed<type_data_ref> type_pol_speed;
		type_pol_speed m_pol_speed(m_data_ref,"Out_Speed_");
		typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_pressure;
		type_pol_pressure m_pol_pressure(m_data_ref,"Out_Pressure_");
		typedef Policy_Output_Particle<type_data_ref> type_pol_particle;
		type_pol_particle m_pol_particle(m_data_ref,"Out_Particle_");
		typedef Policy_Output_Animation<type_data_ref> type_pol_animation;
		type_pol_animation m_pol_animation(m_data_ref,"Out_Animation.pvd");

		typedef Policies<type_pol_speed,type_pol_pressure,type_pol_particle,type_pol_animation> type_pol;
		type_pol pol(m_pol_speed,m_pol_pressure,m_pol_particle,m_pol_animation);
		typedef Algorithms_Output<type_data_ref,type_pol> type_alg;
		type_alg alg(m_data_ref,pol);
		alg.Do();
		TS_ASSERT(true);
	}
	void xtest2()
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
		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype);

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
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);

		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);

		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);
		
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,1.0);
		speed.Set(2,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(1);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(3);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,3.0);
		speed.Set(2,3.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(4);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,1.0);
		speed.Set(2,3.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].Pressure_GetRef().Pressure_Set(5);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);

		type_particle part;
		part.GetParticlePosRef().Set(1,0.5);
		part.GetParticlePosRef().Set(2,0.5);
		m_data_ref.m_data.GetTopologyData().GetRefToParticleList().push_back(part);
		m_data_ref.m_data.GetTimingData().m_t=1;
		
		typedef Policy_Output_Grid_Speed<type_data_ref> type_pol_speed;
		type_pol_speed m_pol_speed(m_data_ref,"Out_Speed_");
		typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_pressure;
		type_pol_pressure m_pol_pressure(m_data_ref,"Out_Pressure_");
		typedef Policy_Output_Particle<type_data_ref> type_pol_particle;
		type_pol_particle m_pol_particle(m_data_ref,"Out_Particle_");
		typedef Policy_Output_Animation<type_data_ref> type_pol_animation;
		type_pol_animation m_pol_animation(m_data_ref,"Out_Animation.pvd");

		typedef Policies<type_pol_speed,type_pol_pressure,type_pol_particle,type_pol_animation> type_pol;
		type_pol pol(m_pol_speed,m_pol_pressure,m_pol_particle,m_pol_animation);
		typedef Algorithms_Output<type_data_ref,type_pol> type_alg;
		type_alg alg(m_data_ref,pol);
		alg.Do();
		TS_ASSERT(true);
	}
};
