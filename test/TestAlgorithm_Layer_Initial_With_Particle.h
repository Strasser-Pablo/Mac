#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Grid_Layer.h"
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_Grid_CellType_To_Grid_CellType.h"
#include "../src/DataRef.h"
#include "../src/Policies.h"
#include "../src/Policy_CheckDT.h"
#include "../src/Empty.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Data_Grid_Data.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Algorithms_Layer_Initial_With_Particle.h"
#include "../src/Data_Topology.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"

#define eps 1e-10
class TestAlgorithm_Layer_Initial_With_Particle : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test_Layer_Initial1()
	{
		const int N=4;
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_empt_lay;
		type_empt_lay m_empt_lay(layer);

		typedef Data_CellType_Fluid_Air<DataBase> type_grid_celltype;
		type_grid_celltype m_grid_celltype;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		m_grid_celltype.SetRhoAir(rho_air);
		m_grid_celltype.SetRhoFluid(rho_fluid);
		typedef Data_Grid_CellType_To_Grid_CellType<type_grid_celltype> type_cell_grid_celltype;
		type_cell_grid_celltype m_cell_grid_celltype(m_grid_celltype);

		typedef Data_Chunk_Layer<type_empt_lay,N> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,N> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
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
		
		type_particle part;
		part.GetParticlePosRef().Set(1,2.2);
		part.GetParticlePosRef().Set(2,4.3);
		part.GetParticlePosRef().Set(3,5.4);
		m_data_ref.m_data.GetTopologyData().GetRefToParticleList().push_back(part);

		typedef Policy_Particle_To_Key<type_data_ref> pol_part_to_key;
		pol_part_to_key m_pol_part_to_key(m_data_ref);
		typedef Policies<pol_part_to_key> type_policies;
		type_policies policies(m_pol_part_to_key);
		Algorithms_Layer_Initial_With_Particle<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		Physvector<3,int> v;
		v.Set(1,2);
		v.Set(2,4);
		v.Set(3,5);
		TS_ASSERT(!m_data_ref.m_data.GetGridData().Exist(v));
		m_alg.Do();
		TS_ASSERT(m_data_ref.m_data.GetGridData().Exist(v));
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),0);
	}
};
