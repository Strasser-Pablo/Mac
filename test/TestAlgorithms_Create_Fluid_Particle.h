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
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow.h"
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
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Data_Grid_Data.h"
#include "../src/Data_Timing.h"
#include "../src/Data_Timing_Time.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Data_Topology.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Algorithms_Create_Fluid_Particle.h"
#include "../src/Policy_Add_Particle_Center.h"
#include "../src/Policy_Is_Inbound_Filling_Layer_Speed.h"
#include "../src/Policy_Is_Inbound_Filling_Layer_CellType.h"
#include "../src/Data_CellType_Const_Inbound.h"

#define eps 1e-10
class TestAlgorithms_Create_Fluid_Particle : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	~TestAlgorithms_Create_Fluid_Particle()
	{
		SingletonManager::Kill();
	}
	void test_Layer_Initial1()
	{
		const int N=4;
		const int NStock=pow(4,3);
		typedef Data_Base_Dim_Type<double,3> DataBase0;
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
		typedef Data_CellType_Const_Inbound<type_grid_speed> type_grid_speed2;
		type_grid_speed2 m_grid_speed2(m_grid_speed);

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

		typedef Data_Chunk_Speed<type_grid_speed2,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed2);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed2,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<3,int> vect;
		typedef Physvector<3,double> vectdouble;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<3,double> m_h;
		m_h.Set(1,1);
		m_h.Set(2,1);
		m_h.Set(3,1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,1);
		v.Set(2,1);
		v.Set(3,1);

		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set_Const(1);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();
		
		typedef Policy_Is_Inbound_Filling_Layer_Speed<type_data_ref> type_inbound_filling;	
		type_inbound_filling m_inbound(m_data_ref);
		typedef Policy_Add_Particle_Center<type_data_ref> type_add_part;
		type_add_part m_addpart(m_data_ref);
		typedef Policies<type_inbound_filling,type_add_part> type_policies;
		type_policies policies(m_inbound,m_addpart);
		Algorithms_Create_Fluid_Particle<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),0)
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),1)
		Physvector<3,double> res=m_data_ref.m_data.GetTopologyData().GetRefToParticleList().front().GetParticlePos();
		TS_ASSERT_DELTA(res.Get(1),1.0,eps);
		TS_ASSERT_DELTA(res.Get(2),1.0,eps);
		TS_ASSERT_DELTA(res.Get(3),1.0,eps);
	}

	void test_Layer_Initial1h()
	{
		const int N=4;
		const int NStock=pow(4,3);
		typedef Data_Base_Dim_Type<double,3> DataBase0;
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
		typedef Data_CellType_Const_Inbound<type_grid_speed> type_grid_speed2;
		type_grid_speed2 m_grid_speed2(m_grid_speed);

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

		typedef Data_Chunk_Speed<type_grid_speed2,NStock> type_chunk_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed2);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed2,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<3,int> vect;
		typedef Physvector<3,double> vectdouble;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<3,double> m_h;
		m_h.Set(1,0.1);
		m_h.Set(2,0.1);
		m_h.Set(3,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,1);
		v.Set(2,1);
		v.Set(3,1);

		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set_Const(1);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();
		
		typedef Policy_Is_Inbound_Filling_Layer_Speed<type_data_ref> type_inbound_filling;	
		type_inbound_filling m_inbound(m_data_ref);
		typedef Policy_Add_Particle_Center<type_data_ref> type_add_part;
		type_add_part m_addpart(m_data_ref);
		typedef Policies<type_inbound_filling,type_add_part> type_policies;
		type_policies policies(m_inbound,m_addpart);
		Algorithms_Create_Fluid_Particle<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),0)
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),1)
		Physvector<3,double> res=m_data_ref.m_data.GetTopologyData().GetRefToParticleList().front().GetParticlePos();
		TS_ASSERT_DELTA(res.Get(1),0.1,eps);
		TS_ASSERT_DELTA(res.Get(2),0.1,eps);
		TS_ASSERT_DELTA(res.Get(3),0.1,eps);
	}

	void test_Layer_Initial2()
	{
		const int N=4;
		const int NStock=pow(4,3);
		typedef Data_Base_Dim_Type<double,3> DataBase0;
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

		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase> type_grid_celltype;
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

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<3,int> vect;
		typedef Physvector<3,double> vectdouble;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<3,double> m_h;
		m_h.Set(1,1);
		m_h.Set(2,1);
		m_h.Set(3,1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,1);
		v.Set(2,1);
		v.Set(3,1);

		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetInflow();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();
		
		typedef Policy_Is_Inbound_Filling_Layer_CellType<type_data_ref> type_inbound_filling;	
		type_inbound_filling m_inbound(m_data_ref);
		typedef Policy_Add_Particle_Center<type_data_ref> type_add_part;
		type_add_part m_addpart(m_data_ref);
		typedef Policies<type_inbound_filling,type_add_part> type_policies;
		type_policies policies(m_inbound,m_addpart);
		Algorithms_Create_Fluid_Particle<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),0)
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),1)
		Physvector<3,double> res=m_data_ref.m_data.GetTopologyData().GetRefToParticleList().front().GetParticlePos();
		TS_ASSERT_DELTA(res.Get(1),1.0,eps);
		TS_ASSERT_DELTA(res.Get(2),1.0,eps);
		TS_ASSERT_DELTA(res.Get(3),1.0,eps);
	}

	void test_Layer_Initial2h()
	{
		const int N=4;
		const int NStock=pow(4,3);
		typedef Data_Base_Dim_Type<double,3> DataBase0;
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

		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase> type_grid_celltype;
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

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype,type_chunk_speed> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype,m_chunk_speed);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base_celltype> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<3,int> vect;
		typedef Physvector<3,double> vectdouble;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<3,double> m_h;
		m_h.Set(1,0.1);
		m_h.Set(2,0.1);
		m_h.Set(3,0.1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,1);
		v.Set(2,1);
		v.Set(3,1);

		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetInflow();
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayerEmpty();
		
		typedef Policy_Is_Inbound_Filling_Layer_CellType<type_data_ref> type_inbound_filling;	
		type_inbound_filling m_inbound(m_data_ref);
		typedef Policy_Add_Particle_Center<type_data_ref> type_add_part;
		type_add_part m_addpart(m_data_ref);
		typedef Policies<type_inbound_filling,type_add_part> type_policies;
		type_policies policies(m_inbound,m_addpart);
		Algorithms_Create_Fluid_Particle<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),0)
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetTopologyData().GetRefToParticleList().size(),1)
		Physvector<3,double> res=m_data_ref.m_data.GetTopologyData().GetRefToParticleList().front().GetParticlePos();
		TS_ASSERT_DELTA(res.Get(1),0.1,eps);
		TS_ASSERT_DELTA(res.Get(2),0.1,eps);
		TS_ASSERT_DELTA(res.Get(3),0.1,eps);
	}
};
