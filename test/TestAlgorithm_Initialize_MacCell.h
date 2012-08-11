#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List_Empty.h"
#include "../src/ChunkHashTable.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Grid_Layer.h"
#include "../src/DataRef.h"
#include "../src/Policies.h"
#include "../src/Algorithms.h"
#include "../src/Algorithms_Initialize_MacCell.h"
#include "../src/Empty.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Data_Grid_Data.h"
#define eps 1e-10
class TestAlgorithmes_Initialize_MacCell : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
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

		typedef Data_Chunk_Layer<type_empt_lay,N> type_chunk_layer;
		type_chunk_layer m_chunk_layer(m_empt_lay);

		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;

		typedef Data_Chunk<type_bool_array,type_chunk_layer> type_chunk;
		type_chunk m_chunk(m_bool_array,m_chunk_layer);

		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);

		typedef Offset<int,3,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_empt_lay,type_off_base> type_off_base_layer;
		typedef Offset_Base_Neighbour<type_off_base_layer> type_off_base_neighbour;
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,vect,type_neigh,type_off_base_neighbour,Hash> type_chunk_table;
		type_chunk_table m_chunk_table(m_neigh,hash);
		typedef Data_Grid_Data<type_chunk_table,Empty> type_grid_data;
		type_grid_data m_grid_data(m_chunk_table,Empty());
		typedef DataRef<type_grid_data> type_data_ref;
		type_data_ref m_data_ref(m_grid_data);
		Physvector<3,int> v;
		v.Set(1,1);
		v.Set(2,2);
		v.Set(3,3);
		m_data_ref.m_data.GetGridData()[v];
		typedef Policies<> type_pol;
		type_pol pol;
		Algorithms_Initialize_MacCell<type_data_ref,type_pol> m_alg(m_data_ref,pol);
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetLayer(),-1);
		TS_ASSERT(m_data_ref.m_data.GetGridData()[v].Layer_GetRef().GetIsLayerEmpty());
	}
};
