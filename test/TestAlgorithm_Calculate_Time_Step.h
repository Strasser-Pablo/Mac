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

#define eps 1e-10
class TestAlgorithm_Calculate_Time_Step : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
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

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		type_grid_speed m_grid_speed;

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

		typedef Data_Chunk_Speed<type_grid_speed,N> type_chunk_speed;
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
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		m_time.m_t=0;
		m_time.m_factor=1.0;
		typedef Data_Timing<type_time,type_grid_data> type_timing;
		type_timing m_timing(m_time,m_grid_data);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);
		Physvector<3,int> v;
		v.Set(1,1);
		v.Set(2,2);
		v.Set(3,3);
		m_data_ref.m_data.GetGridData()[v].CellType_GetRef().SetFluid();
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(2,1.0);
		m_data_ref.m_data.GetGridData()[v].Speed_GetRef().Speed_Set(3,1.0);

		typedef Policy_CheckDT<type_data_ref> type_check;
		type_check m_check(0,10.0);
		typedef Policies<type_check> type_policies;
		type_policies policies(m_check);
		Algorithms_Calculate_Time_Step<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		m_alg.Do();
		TS_ASSERT_DELTA(m_data_ref.m_data.GetTimingData().m_dt,1/sqrt(3),eps);
	}
};
