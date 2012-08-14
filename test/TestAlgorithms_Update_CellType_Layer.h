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
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Algorithms_Update_CellType_Layer.h"
#include "../src/Policy_Layer_Max.h"

#define eps 1e-10
class TestAlgorithms_Update_CellType_Layer : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	~TestAlgorithms_Update_CellType_Layer()
	{
		SingletonManager::Kill();
	}
	void test1()
	{
		const int N=4;
		const int NStock=pow(4,2);
		typedef Data_Base_Dim_Type<double,2> DataBase0;
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

		typedef Data_Chunk_Layer<type_empt_lay,NStock> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<NStock> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk_CellType<type_cell_grid_celltype,NStock> type_chunk_celltype;
		type_chunk_celltype m_chunk_celltype(m_cell_grid_celltype);

		typedef Data_Chunk<type_bool_array,type_chunk_layer,type_chunk_celltype> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer,m_chunk_celltype);

		typedef Neighbour_List_Empty<2,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,2,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_CellType<type_cell_grid_celltype,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<2,int> vect;
		typedef Physvector<2,double> vectdouble;
		typedef HashPhysvector<2,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Base_Spacing<type_chunk_table,vectdouble> type_data_grid_base_spacing;
		type_data_grid_base_spacing m_data_grid_base_spacing(m_chunk_table);
		Physvector<2,double> m_h;
		m_h.Set(1,1);
		m_h.Set(2,1);
		m_data_grid_base_spacing.m_h.Set(m_h);
		typedef Data_Grid_Data<type_data_grid_base_spacing,Empty> type_grid_data;
		type_grid_data m_grid_data(m_data_grid_base_spacing,Empty());
		typedef DataRef<type_grid_data> type_data_ref;
		type_data_ref m_data_ref(m_grid_data);
		
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		m_data_ref.m_data.GetGridData()[v].Layer_GetRef().SetLayer(0);
		
		typedef Policy_Layer_Max<type_data_ref> type_layer_max;
		type_layer_max m_layer_max(1);
		typedef Policies<type_layer_max> type_policies;
		type_policies policies(m_layer_max);
		Algorithms_Update_CellType_Layer<type_data_ref,type_policies> m_alg(m_data_ref,policies);

		v.Set(1,0);
		v.Set(2,0);

		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),0);
		m_alg.Do();

		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),0);
		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),1);
		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),1);
		v.Set(1,-1);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),1);
		v.Set(1,0);
		v.Set(2,-1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),1);
		v.Set(1,2);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),2);
		v.Set(1,1);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),2);
		v.Set(1,1);
		v.Set(2,-1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),2);
		v.Set(1,0);
		v.Set(2,2);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),2);
		v.Set(1,-1);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),2);
	}
};
