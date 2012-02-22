#include <cxxtest/TestSuite.h>
#include "../src/Physvector.h"
#include "../src/NeighborsDiagPhysvector.h"
#define eps 1e-10
class Test_NeighborsDiagPhysvector : public CxxTest::TestSuite
{
public:
	void testneigh(){
		Physvector<1,int> v;
		v.SetAll(0);
		NeighborsDiagPhysvector<int,1> N(v);
		Physvector<1,int> v1;
		Physvector<1,int> v2;
		Physvector<1,int> v3;
		bool b1;
		bool b2;
		bool b3;
		b1=N.GetNext(v1);
		b2=N.GetNext(v2);
		b3=N.GetNext(v3);
		TS_ASSERT_EQUALS(b1,true);
		TS_ASSERT_EQUALS(b2,true);
		TS_ASSERT_EQUALS(b3,false);
		TS_ASSERT_EQUALS((v1.Get(1)),-1);
		TS_ASSERT_EQUALS((v2.Get(1)),1);
		
		Physvector<2,int> a;
		a.SetAll(0);
		NeighborsDiagPhysvector<int,2> N2(a);
		Physvector<2,int> a1;
		Physvector<2,int> a2;
		Physvector<2,int> a3;
		Physvector<2,int> a4;
		Physvector<2,int> a5;
		Physvector<2,int> a6;
		Physvector<2,int> a7;
		Physvector<2,int> a8;
		Physvector<2,int> a9;
		bool ab1;
		bool ab2;
		bool ab3;
		bool ab4;
		bool ab5;
		bool ab6;
		bool ab7;
		bool ab8;
		bool ab9;
		ab1=N2.GetNext(a1);
		ab2=N2.GetNext(a2);
		ab3=N2.GetNext(a3);
		ab4=N2.GetNext(a4);
		ab5=N2.GetNext(a5);
		ab6=N2.GetNext(a6);
		ab7=N2.GetNext(a7);
		ab8=N2.GetNext(a8);
		ab9=N2.GetNext(a9);
		TS_ASSERT_EQUALS(ab1,true);
		TS_ASSERT_EQUALS(ab2,true);
		TS_ASSERT_EQUALS(ab3,true);
		TS_ASSERT_EQUALS(ab4,true);
		TS_ASSERT_EQUALS(ab5,true);
		TS_ASSERT_EQUALS(ab6,true);
		TS_ASSERT_EQUALS(ab7,true);
		TS_ASSERT_EQUALS(ab8,true);
		TS_ASSERT_EQUALS(ab9,false);
		TS_ASSERT_EQUALS((a1.Get(1)),-1);
		TS_ASSERT_EQUALS((a1.Get(2)),-1);
		
		TS_ASSERT_EQUALS((a2.Get(1)),0);
		TS_ASSERT_EQUALS((a2.Get(2)),-1);
		
		TS_ASSERT_EQUALS((a3.Get(1)),1);
		TS_ASSERT_EQUALS((a3.Get(2)),-1);
		
		TS_ASSERT_EQUALS((a4.Get(1)),-1);
		TS_ASSERT_EQUALS((a4.Get(2)),0);
		
		TS_ASSERT_EQUALS((a5.Get(1)),1);
		TS_ASSERT_EQUALS((a5.Get(2)),0);
		
		TS_ASSERT_EQUALS((a6.Get(1)),-1);
		TS_ASSERT_EQUALS((a6.Get(2)),1);
		
		TS_ASSERT_EQUALS((a7.Get(1)),0);
		TS_ASSERT_EQUALS((a7.Get(2)),1);
		
		TS_ASSERT_EQUALS((a8.Get(1)),1);
		TS_ASSERT_EQUALS((a8.Get(2)),1);
	}
};
