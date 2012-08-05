#include <cxxtest/TestSuite.h>
#include "../src/Offset.h"
#define eps 1e-10
class TestOffset : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
	{
		typedef Offset<int,1,4> type_off_1;
		type_off_1 off1(0);
		type_off_1 res;
		TS_ASSERT(!off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,1);
		TS_ASSERT(off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,3);
	}
	void test2()
	{
		typedef Offset<int,2,4> type_off_1;
		type_off_1 off1(0);
		type_off_1 res;
		TS_ASSERT(!off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,1);
		TS_ASSERT(off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,3);
		TS_ASSERT(!off1.GetNeighbour(2,1,res));
		TS_ASSERT_EQUALS(res.off,4);
		TS_ASSERT(off1.GetNeighbour(2,-1,res));
		TS_ASSERT_EQUALS(res.off,12);
	}
	void test3()
	{
		typedef Offset<int,3,4> type_off_1;
		type_off_1 off1(0);
		type_off_1 res;
		TS_ASSERT(!off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,1);
		TS_ASSERT(off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,3);
		TS_ASSERT(!off1.GetNeighbour(2,1,res));
		TS_ASSERT_EQUALS(res.off,4);
		TS_ASSERT(off1.GetNeighbour(2,-1,res));
		TS_ASSERT_EQUALS(res.off,12);
		TS_ASSERT(!off1.GetNeighbour(3,1,res));
		TS_ASSERT_EQUALS(res.off,16);
		TS_ASSERT(off1.GetNeighbour(3,-1,res));
		TS_ASSERT_EQUALS(res.off,48);
	}
	void test1_2()
	{
		typedef Offset<int,1,4> type_off_1;
		type_off_1 off1(3);
		type_off_1 res;
		TS_ASSERT(off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,0);
		TS_ASSERT(!off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,2);
	}
	void test2_2()
	{
		typedef Offset<int,2,4> type_off_1;
		type_off_1 off1(13);
		type_off_1 res;
		TS_ASSERT(!off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,14);
		TS_ASSERT(!off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,12);
		TS_ASSERT(off1.GetNeighbour(2,1,res));
		TS_ASSERT_EQUALS(res.off,1);
		TS_ASSERT(!off1.GetNeighbour(2,-1,res));
		TS_ASSERT_EQUALS(res.off,9);
	}
	void test3_2()
	{
		typedef Offset<int,3,4> type_off_1;
		type_off_1 off1(49);
		type_off_1 res;
		TS_ASSERT(!off1.GetNeighbour(1,1,res));
		TS_ASSERT_EQUALS(res.off,50);
		TS_ASSERT(!off1.GetNeighbour(1,-1,res));
		TS_ASSERT_EQUALS(res.off,48);
		TS_ASSERT(!off1.GetNeighbour(2,1,res));
		TS_ASSERT_EQUALS(res.off,53);
		TS_ASSERT(!off1.GetNeighbour(2,-1,res));
		TS_ASSERT_EQUALS(res.off,45);
		TS_ASSERT(off1.GetNeighbour(3,1,res));
		TS_ASSERT_EQUALS(res.off,1);
		TS_ASSERT(!off1.GetNeighbour(3,-1,res));
		TS_ASSERT_EQUALS(res.off,33);
	}
};
