#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List.h"
#define eps 1e-10
struct Data
{
	double m_speed[3];
};
class Test_Data_Neighbour_List : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void testInt1d()
	{
		Neighbour_List<1,int> N(1);
		Neighbour_List<1,int> N2(2);
		Neighbour_List<1,int> N3(3);
		N.SetNeighbour(1,1,&N2);
		N.SetNeighbour(1,-1,&N3);
		TS_ASSERT_EQUALS(N.Get(),1);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,1))->Get(),2);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,-1))->Get(),3);
	}

	void testInt2d()
	{
		Neighbour_List<2,int> N(1);
		Neighbour_List<2,int> N2(2);
		Neighbour_List<2,int> N3(3);
		Neighbour_List<2,int> N4(4);
		Neighbour_List<2,int> N5(5);
		N.SetNeighbour(1,1,&N2);
		N.SetNeighbour(2,-1,&N3);
		N.SetNeighbour(2,1,&N4);
		N.SetNeighbour(1,-1,&N5);
		TS_ASSERT_EQUALS(N.Get(),1);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,1))->Get(),2);
		TS_ASSERT_EQUALS((N.GetNeighbour(2,-1))->Get(),3);
		TS_ASSERT_EQUALS((N.GetNeighbour(2,1))->Get(),4);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,-1))->Get(),5);
	}

	void testSpeed2d()
	{
		Neighbour_List<2,Data> N;
		Neighbour_List<2,Data> N2;
		N.GetRef().m_speed[0]=0;
		N.GetRef().m_speed[1]=1;
		N.GetRef().m_speed[2]=2;
		N2.GetRef().m_speed[0]=3;
		N2.GetRef().m_speed[1]=4;
		N2.GetRef().m_speed[2]=5;
		N.SetNeighbour(1,1,&N2);
		TS_ASSERT_EQUALS(N.Get().m_speed[0],0);
		TS_ASSERT_EQUALS(N.Get().m_speed[1],1);
		TS_ASSERT_EQUALS(N.Get().m_speed[2],2);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,1))->Get().m_speed[0],3);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,1))->Get().m_speed[1],4);
		TS_ASSERT_EQUALS((N.GetNeighbour(1,1))->Get().m_speed[2],5);
	}
};
