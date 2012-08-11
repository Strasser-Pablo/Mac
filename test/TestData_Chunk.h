#include <cxxtest/TestSuite.h>
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Neighbour_List_Empty.h"
#include "../src/Data_Chunk.h"

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
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype> type_chunk;
		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_speed m_speed(0);
		type_pressure m_pressure(0);
		type_layer m_layer(0);
		type_celltype m_celltype(0);
		type_chunk m_chunk(m_speed,m_pressure,m_layer,m_celltype);
		int i1=1;
		int i2=2;
		int i3=3;
		int i4=4;

		type_neigh c1(m_chunk);
		type_neigh c2(m_chunk);
		type_neigh c3(m_chunk);
		c1.Speed_SetPointer(&i1);
		c2.Speed_SetPointer(&i2);
		c3.Speed_SetPointer(&i3);

		c1.Pressure_SetPointer(&i3);
		c2.Pressure_SetPointer(&i2);
		c3.Pressure_SetPointer(&i4);

		c1.Layer_SetPointer(&i3);
		c2.Layer_SetPointer(&i1);
		c3.Layer_SetPointer(&i4);

		c1.CellType_SetPointer(&i3);
		c2.CellType_SetPointer(&i2);
		c3.CellType_SetPointer(&i1);

		c1.SetNeighbour(1,1,&c2);
		c1.SetNeighbour(1,-1,&c3);

		TS_ASSERT_EQUALS(c1.Speed_GetRef(),i1);
		TS_ASSERT_EQUALS(c1.Pressure_GetRef(),i3);
		TS_ASSERT_EQUALS(c1.Layer_GetRef(),i3);
		TS_ASSERT_EQUALS(c1.CellType_GetRef(),i3);

		TS_ASSERT_EQUALS(c1.GetNeighbour(1,1)->Speed_GetRef(),i2);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,1)->Pressure_GetRef(),i2);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,1)->Layer_GetRef(),i1);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,1)->CellType_GetRef(),i2);

		TS_ASSERT_EQUALS(c1.GetNeighbour(1,-1)->Speed_GetRef(),i3);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,-1)->Pressure_GetRef(),i4);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,-1)->Layer_GetRef(),i4);
		TS_ASSERT_EQUALS(c1.GetNeighbour(1,-1)->CellType_GetRef(),i1);
	}

	void testAllocate()
	{
		const int N=10;
		typedef Data_Chunk_Speed<int,N> type_speed;
		typedef Data_Chunk_Pressure<int,N> type_pressure;
		typedef Data_Chunk_Layer<int,N> type_layer;
		typedef Data_Chunk_CellType<int,N> type_celltype;
		typedef Data_Chunk<type_speed,type_pressure,type_layer,type_celltype> type_chunk;
		type_speed m_speed(0);
		type_pressure m_pressure(0);
		type_layer m_layer(0);
		type_celltype m_celltype(0);
		type_chunk c(m_speed,m_pressure,m_layer,m_celltype);
		c.Allocate();
		TS_ASSERT(c.Speed_GetPointer()!=nullptr);
		c.UnAllocate();
	}
};
