#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List_Empty.h"
#define eps 1e-10

struct empty
{
};

class Test_Data_Neighbour_List : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void testInt1d()
	{
		Neighbour_List_Empty<1,empty> N;
		Neighbour_List_Empty<1,empty> N2;
		Neighbour_List_Empty<1,empty> N3;
		N.SetNeighbour(1,1,&N2);
		N.SetNeighbour(1,-1,&N3);
		TS_ASSERT_EQUALS(N.GetNeighbour(1,1),&N2);
		TS_ASSERT_EQUALS(N.GetNeighbour(1,-1),&N3);
	}

	void test2d()
	{
		Neighbour_List_Empty<2,empty> N;
		Neighbour_List_Empty<2,empty> N2;
		Neighbour_List_Empty<2,empty> N3;
		Neighbour_List_Empty<2,empty> N4;
		Neighbour_List_Empty<2,empty> N5;
		N.SetNeighbour(1,1,&N2);
		N.SetNeighbour(2,-1,&N3);
		N.SetNeighbour(2,1,&N4);
		N.SetNeighbour(1,-1,&N5);
		TS_ASSERT_EQUALS(N.GetNeighbour(1,1),&N2);
		TS_ASSERT_EQUALS(N.GetNeighbour(2,-1),&N3);
		TS_ASSERT_EQUALS(N.GetNeighbour(2,1),&N4);
		TS_ASSERT_EQUALS(N.GetNeighbour(1,-1),&N5);
	}
};
