#include <cxxtest/TestSuite.h>
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Neighbour_List_Empty.h"
#define eps 1e-10

struct empty
{
};
class TestOffset_Base : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
	{
		typedef Offset<int,1,4> type_off_1;
		typedef Neighbour_List_Empty<1,empty> type_neigh;
		typedef Offset_Base<type_off_1,type_neigh> type_off_base;
		type_off_base b;
		type_neigh n1;
		type_neigh n2;
		n1.SetNeighbour(1,-1,&n2);
		b.SetBase(&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetOffset().off,1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetOffset().off,3);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetBase(),&n2);
	}
	void test2()
	{
		typedef Offset<int,2,4> type_off_1;
		typedef Neighbour_List_Empty<2,empty> type_neigh;
		typedef Offset_Base<type_off_1,type_neigh> type_off_base;
		type_off_base b;
		type_neigh n1;
		type_neigh n2;
		type_neigh n3;
		n1.SetNeighbour(1,-1,&n2);
		n1.SetNeighbour(2,-1,&n3);
		b.SetBase(&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetOffset().off,1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetOffset().off,3);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetBase(),&n2);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,1).GetOffset().off,4);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,-1).GetOffset().off,12);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,-1).GetBase(),&n3);
	}
	void test3()
	{
		typedef Offset<int,3,4> type_off_1;
		typedef Neighbour_List_Empty<3,empty> type_neigh;
		typedef Offset_Base<type_off_1,type_neigh> type_off_base;
		type_off_base b;
		type_neigh n1;
		type_neigh n2;
		type_neigh n3;
		type_neigh n4;
		n1.SetNeighbour(1,-1,&n2);
		n1.SetNeighbour(2,-1,&n3);
		n1.SetNeighbour(3,-1,&n4);
		b.SetBase(&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetOffset().off,1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetOffset().off,3);
		TS_ASSERT_EQUALS(b.GetNeighbour(1,-1).GetBase(),&n2);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,1).GetOffset().off,4);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,-1).GetOffset().off,12);
		TS_ASSERT_EQUALS(b.GetNeighbour(2,-1).GetBase(),&n3);
		TS_ASSERT_EQUALS(b.GetNeighbour(3,1).GetOffset().off,16);
		TS_ASSERT_EQUALS(b.GetNeighbour(3,1).GetBase(),&n1);
		TS_ASSERT_EQUALS(b.GetNeighbour(3,-1).GetOffset().off,48);
		TS_ASSERT_EQUALS(b.GetNeighbour(3,-1).GetBase(),&n4);
	}
};
