#include <cxxtest/TestSuite.h>
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Neighbour_List_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Hookable_Hash_Table.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/ChunkHashTable.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"

class TestData_Chunk : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void test1d()
	{
		const int N=10;
		typedef Data_Chunk_Speed<int,N> type_speed;
		typedef Data_Chunk_Pressure<int,N> type_pressure;
		typedef Data_Chunk_Layer<int,N> type_layer;
		typedef Data_Chunk_CellType<int,N> type_celltype;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Speed<int,type_off_base> type_off_base_speed;
		typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
		typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(hash);
		
		type_vect v;
		v.Set(1,4);

		TS_ASSERT(m_table[v].Speed_GetPointer()!=nullptr);
		m_table[v].Speed_GetRef()=10;
		TS_ASSERT_EQUALS(m_table[v].Speed_GetRef(),10);

		TS_ASSERT(m_table[v].Pressure_GetPointer()!=nullptr);
		m_table[v].Pressure_GetRef()=12;
		TS_ASSERT_EQUALS(m_table[v].Pressure_GetRef(),12);

		TS_ASSERT(m_table[v].Layer_GetPointer()!=nullptr);
		m_table[v].Layer_GetRef()=16;
		TS_ASSERT_EQUALS(m_table[v].Layer_GetRef(),16);

		TS_ASSERT(m_table[v].CellType_GetPointer()!=nullptr);
		m_table[v].CellType_GetRef()=16;
		TS_ASSERT_EQUALS(m_table[v].CellType_GetRef(),16);
	}
	void test1dNeighbour()
	{
		const int N=2;
		typedef Data_Chunk_Speed<int,N> type_speed;
		typedef Data_Chunk_Pressure<int,N> type_pressure;
		typedef Data_Chunk_Layer<int,N> type_layer;
		typedef Data_Chunk_CellType<int,N> type_celltype;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Speed<int,type_off_base> type_off_base_speed;
		typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
		typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(hash);
		
		type_vect v;
		v.Set(1,4);
		m_table[v].Speed_GetRef()=10;
		m_table[v].Pressure_GetRef()=12;
		m_table[v].Layer_GetRef()=16;
		m_table[v].CellType_GetRef()=16;

		v.Set(1,5);
		m_table[v].Speed_GetRef()=3;
		m_table[v].Pressure_GetRef()=5;
		m_table[v].Layer_GetRef()=2;
		m_table[v].CellType_GetRef()=5;

		v.Set(1,3);
		m_table[v].Speed_GetRef()=87;
		m_table[v].Pressure_GetRef()=3;
		m_table[v].Layer_GetRef()=8;
		m_table[v].CellType_GetRef()=2;

		v.Set(1,2);
		m_table[v].Speed_GetRef()=5;
		m_table[v].Pressure_GetRef()=2;
		m_table[v].Layer_GetRef()=5;
		m_table[v].CellType_GetRef()=1;

		v.Set(1,4);
		
		type_off_base_celltype it=m_table[v].GetNeighbour(1,1);

		TS_ASSERT_EQUALS(it.Speed_GetRef(),3);
		TS_ASSERT_EQUALS(it.Pressure_GetRef(),5);
		TS_ASSERT_EQUALS(it.Layer_GetRef(),2);
		TS_ASSERT_EQUALS(it.CellType_GetRef(),5);

		type_off_base_celltype it2=m_table[v].GetNeighbour(1,-1);

		TS_ASSERT_EQUALS(it2.Speed_GetRef(),87);
		TS_ASSERT_EQUALS(it2.Pressure_GetRef(),3);
		TS_ASSERT_EQUALS(it2.Layer_GetRef(),8);
		TS_ASSERT_EQUALS(it2.CellType_GetRef(),2);

		type_off_base_celltype it4=it2.GetNeighbour(1,-1);

		TS_ASSERT_EQUALS(it4.Speed_GetRef(),5);
		TS_ASSERT_EQUALS(it4.Pressure_GetRef(),2);
		TS_ASSERT_EQUALS(it4.Layer_GetRef(),5);
		TS_ASSERT_EQUALS(it4.CellType_GetRef(),1);
	}
};
