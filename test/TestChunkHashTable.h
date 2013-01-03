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
#include "../src/Hook_Neighbour_List_key.h"
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
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"

class TestData_Chunk : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	~TestData_Chunk()
	{
		SingletonManager::Kill();
	}
	void test1d()
	{
		const int N=10;
        typedef Data_Base_Dim_Type<double,1> DataBase0;
        DataBase0 base0;
        typedef Data_Staggered_Left<DataBase0> DataBase;
        DataBase base(base0);
        typedef bitset<1> type_const;
        type_const m_const;
        typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
        type_grid_speed m_grid_speed(m_const);

        typedef Data_Chunk_Speed<type_grid_speed,1,1,N> type_speed;
		typedef Data_Chunk_Pressure<int,N> type_pressure;
		typedef Data_Chunk_Layer<int,N> type_layer;
		typedef Data_Chunk_CellType<int,N> type_celltype;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
        type_speed m_speed(m_grid_speed);
		type_pressure m_pressure(0);
		type_layer m_layer(0);
		type_celltype m_celltype(0);
		type_bool_array m_bool_array;
		type_chunk m_chunk(m_speed,m_pressure,m_layer,m_celltype,m_bool_array);
		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Base_Speed<type_grid_speed,type_off_base> type_off_base_speed;
		typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
		typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		
		type_vect v;
		v.Set(1,4);

		TS_ASSERT(m_table[v].Speed_GetPointer()!=nullptr);
        m_table[v].Speed_GetRef().Set(1,10);
        TS_ASSERT_EQUALS(m_table[v].Speed_GetRef().Get(1),10);

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

        typedef Data_Base_Dim_Type<double,1> DataBase0;
        DataBase0 base0;
        typedef Data_Staggered_Left<DataBase0> DataBase;
        DataBase base(base0);
        typedef bitset<1> type_const;
        type_const m_const;
        typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
        type_grid_speed m_grid_speed(m_const);

        typedef Data_Chunk_Speed<type_grid_speed,1,1,N> type_speed;
		typedef Data_Chunk_Pressure<int,N> type_pressure;
		typedef Data_Chunk_Layer<int,N> type_layer;
		typedef Data_Chunk_CellType<int,N> type_celltype;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
        type_speed m_speed(m_grid_speed);
		type_pressure m_pressure(0);
		type_layer m_layer(0);
		type_celltype m_celltype(0);
		type_bool_array m_bool_array;
		type_chunk m_chunk(m_speed,m_pressure,m_layer,m_celltype,m_bool_array);
		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Base_Speed<type_grid_speed,type_off_base> type_off_base_speed;
		typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
		typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		
		type_vect v;
		v.Set(1,4);
        m_table[v].Speed_GetRef().Set(1,10);
		m_table[v].Pressure_GetRef()=12;
		m_table[v].Layer_GetRef()=16;
		m_table[v].CellType_GetRef()=16;

		v.Set(1,5);
        m_table[v].Speed_GetRef().Set(1,3);
		m_table[v].Pressure_GetRef()=5;
		m_table[v].Layer_GetRef()=2;
		m_table[v].CellType_GetRef()=5;

		v.Set(1,3);
        m_table[v].Speed_GetRef().Set(1,87);
		m_table[v].Pressure_GetRef()=3;
		m_table[v].Layer_GetRef()=8;
		m_table[v].CellType_GetRef()=2;

		v.Set(1,2);
        m_table[v].Speed_GetRef().Set(1,5);
		m_table[v].Pressure_GetRef()=2;
		m_table[v].Layer_GetRef()=5;
		m_table[v].CellType_GetRef()=1;

		v.Set(1,4);
		
		type_off_base_celltype it=m_table[v].GetNeighbour(1,1);

        TS_ASSERT_EQUALS(it.Speed_GetRef().Get(1),3);
		TS_ASSERT_EQUALS(it.Pressure_GetRef(),5);
		TS_ASSERT_EQUALS(it.Layer_GetRef(),2);
		TS_ASSERT_EQUALS(it.CellType_GetRef(),5);

		type_off_base_celltype it2=m_table[v].GetNeighbour(1,-1);

        TS_ASSERT_EQUALS(it2.Speed_GetRef().Get(1),87);
		TS_ASSERT_EQUALS(it2.Pressure_GetRef(),3);
		TS_ASSERT_EQUALS(it2.Layer_GetRef(),8);
		TS_ASSERT_EQUALS(it2.CellType_GetRef(),2);

		type_off_base_celltype it4=it2.GetNeighbour(1,-1);

        TS_ASSERT_EQUALS(it4.Speed_GetRef().Get(1),5);
		TS_ASSERT_EQUALS(it4.Pressure_GetRef(),2);
		TS_ASSERT_EQUALS(it4.Layer_GetRef(),5);
		TS_ASSERT_EQUALS(it4.CellType_GetRef(),1);
	}
	void test2dNeighbour()
	{
		const int N=2;
		const int NStor=4;

        typedef Data_Base_Dim_Type<double,2> DataBase0;
        DataBase0 base0;
        typedef Data_Staggered_Left<DataBase0> DataBase;
        DataBase base(base0);
        typedef bitset<2> type_const;
        type_const m_const;
        typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
        type_grid_speed m_grid_speed(m_const);

        typedef Data_Chunk_Speed<type_grid_speed,1,1,NStor> type_speed;
		typedef Data_Chunk_Pressure<int,NStor> type_pressure;
		typedef Data_Chunk_Layer<int,NStor> type_layer;
		typedef Data_Chunk_CellType<int,NStor> type_celltype;
		typedef Data_Chunk_Bool_Array<NStor> type_bool_array;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
        type_speed m_speed(m_grid_speed);
		type_pressure m_pressure(0);
		type_layer m_layer(0);
		type_celltype m_celltype(0);
		type_bool_array m_bool_array;
		type_chunk m_chunk(m_speed,m_pressure,m_layer,m_celltype,m_bool_array);
		typedef Neighbour_List_Empty<2,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,2,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Base_Speed<type_grid_speed,type_off_base> type_off_base_speed;
		typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
		typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
		typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<2,int> type_vect;
		typedef HashPhysvector<2,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		
		type_vect v;

		v.Set(1,0);
		v.Set(2,0);

        m_table[v].Speed_GetRef().Set(1,10);
		m_table[v].Pressure_GetRef()=12;
		m_table[v].Layer_GetRef()=16;
		m_table[v].CellType_GetRef()=16;

		v.Set(1,0);
		v.Set(2,1);

        m_table[v].Speed_GetRef().Set(1,3);
		m_table[v].Pressure_GetRef()=5;
		m_table[v].Layer_GetRef()=2;
		m_table[v].CellType_GetRef()=5;

		v.Set(1,1);
		v.Set(2,0);

        m_table[v].Speed_GetRef().Set(1,87);
		m_table[v].Pressure_GetRef()=3;
		m_table[v].Layer_GetRef()=8;
		m_table[v].CellType_GetRef()=2;

		v.Set(1,1);
		v.Set(2,1);

        m_table[v].Speed_GetRef().Set(1,5);
		m_table[v].Pressure_GetRef()=2;
		m_table[v].Layer_GetRef()=5;
		m_table[v].CellType_GetRef()=1;

		v.Set(1,0);
		v.Set(2,0);

        TS_ASSERT_EQUALS(m_table[v].Speed_GetRef().Get(1),10);
		TS_ASSERT_EQUALS(m_table[v].Pressure_GetRef(),12);
		TS_ASSERT_EQUALS(m_table[v].Layer_GetRef(),16);
		TS_ASSERT_EQUALS(m_table[v].CellType_GetRef(),16);

		v.Set(1,0);
		v.Set(2,1);

        TS_ASSERT_EQUALS(m_table[v].Speed_GetRef().Get(1),3);
		TS_ASSERT_EQUALS(m_table[v].Pressure_GetRef(),5);
		TS_ASSERT_EQUALS(m_table[v].Layer_GetRef(),2);
		TS_ASSERT_EQUALS(m_table[v].CellType_GetRef(),5);

		v.Set(1,1);
		v.Set(2,0);

        TS_ASSERT_EQUALS(m_table[v].Speed_GetRef().Get(1),87);
		TS_ASSERT_EQUALS(m_table[v].Pressure_GetRef(),3);
		TS_ASSERT_EQUALS(m_table[v].Layer_GetRef(),8);
		TS_ASSERT_EQUALS(m_table[v].CellType_GetRef(),2);

		v.Set(1,1);
		v.Set(2,1);

        TS_ASSERT_EQUALS(m_table[v].Speed_GetRef().Get(1),5);
		TS_ASSERT_EQUALS(m_table[v].Pressure_GetRef(),2);
		TS_ASSERT_EQUALS(m_table[v].Layer_GetRef(),5);
		TS_ASSERT_EQUALS(m_table[v].CellType_GetRef(),1);
	}

    void test2dErase()
    {
        const int N=2;
        const int NStor=4;

        typedef Data_Base_Dim_Type<double,2> DataBase0;
        DataBase0 base0;
        typedef Data_Staggered_Left<DataBase0> DataBase;
        DataBase base(base0);
        typedef bitset<2> type_const;
        type_const m_const;
        typedef Data_Grid_Speed<DataBase,type_const> type_grid_speed;
        type_grid_speed m_grid_speed(m_const);

        typedef Data_Chunk_Speed<type_grid_speed,1,1,NStor> type_speed;
        typedef Data_Chunk_Pressure<int,NStor> type_pressure;
        typedef Data_Chunk_Layer<int,NStor> type_layer;
        typedef Data_Chunk_CellType<int,NStor> type_celltype;
        typedef Data_Chunk_Bool_Array<NStor> type_bool_array;
        typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype,type_bool_array> type_chunk;
        type_speed m_speed(m_grid_speed);
        type_pressure m_pressure(0);
        type_layer m_layer(0);
        type_celltype m_celltype(0);
        type_bool_array m_bool_array;
        type_chunk m_chunk(m_speed,m_pressure,m_layer,m_celltype,m_bool_array);
        typedef Neighbour_List_Empty<2,type_chunk> type_neigh;
        type_neigh m_neigh(m_chunk);
        typedef Offset<int,2,N> type_off;
        typedef Offset_Base<type_off,type_neigh> type_off_base;
        typedef Offset_Base_Speed<type_grid_speed,type_off_base> type_off_base_speed;
        typedef Offset_Base_Pressure<int,type_off_base_speed> type_off_base_pressure;
        typedef Offset_Base_Layer<int,type_off_base_pressure> type_off_base_layer;
        typedef Offset_Base_CellType<int,type_off_base_layer> type_off_base_celltype;
        typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
        typedef Physvector<2,int> type_vect;
        typedef HashPhysvector<2,int> type_hash;
        typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
        type_hash hash;
        type_chunk_table m_table(m_neigh,hash);

        type_vect v;

        v.Set(1,0);
        v.Set(2,0);

        m_table[v].Speed_GetRef().Set(1,10);
        m_table[v].Pressure_GetRef()=12;
        m_table[v].Layer_GetRef()=16;
        m_table[v].CellType_GetRef()=16;

        v.Set(1,0);
        v.Set(2,1);

        m_table[v].Speed_GetRef().Set(1,3);
        m_table[v].Pressure_GetRef()=5;
        m_table[v].Layer_GetRef()=2;
        m_table[v].CellType_GetRef()=5;

        v.Set(1,0);
        v.Set(2,0);

        m_table.erase(m_table.begin());
        v.Set(1,0);
        v.Set(2,1);

        TS_ASSERT(!m_table[v].GetNeighbour(2,-1).IsValid())
    }
};
