#include <cxxtest/TestSuite.h>
#include "../src/Physvector.h"
#include "../src/NeighborsPhysvector.h"
#define eps 1e-10
class Test_NeighborsPhysvector : public CxxTest::TestSuite
{
public:
	void testneigh(){
		Physvector<1,int> v;
		v.SetAll(0);
		NeighborsPhysvector<int,1> N(v);
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
		NeighborsPhysvector<int,2> N2(a);
		Physvector<2,int> a1;
		Physvector<2,int> a2;
		Physvector<2,int> a3;
		Physvector<2,int> a4;
		Physvector<2,int> a5;
		bool ab1;
		bool ab2;
		bool ab3;
		bool ab4;
		bool ab5;
		ab1=N2.GetNext(a1);
		ab2=N2.GetNext(a2);
		ab3=N2.GetNext(a3);
		ab4=N2.GetNext(a4);
		ab5=N2.GetNext(a5);
		TS_ASSERT_EQUALS(ab1,true);
		TS_ASSERT_EQUALS(ab2,true);
		TS_ASSERT_EQUALS(ab3,true);
		TS_ASSERT_EQUALS(ab4,true);
		TS_ASSERT_EQUALS(ab5,false);
		TS_ASSERT_EQUALS((a1.Get(1)),-1);
		TS_ASSERT_EQUALS((a2.Get(1)),1);
		TS_ASSERT_EQUALS((a1.Get(2)),0);
		TS_ASSERT_EQUALS((a2.Get(2)),0);
		
		TS_ASSERT_EQUALS((a3.Get(2)),-1);
		TS_ASSERT_EQUALS((a4.Get(2)),1);
		TS_ASSERT_EQUALS((a3.Get(1)),0);
		TS_ASSERT_EQUALS((a4.Get(1)),0);
		
		Physvector<2,int> b;
		b.Set(1,4);
		b.Set(2,6);
		NeighborsPhysvector<int,2> N3(b);
		Physvector<2,int> vb1;
		Physvector<2,int> vb2;
		Physvector<2,int> vb3;
		Physvector<2,int> vb4;
		Physvector<2,int> vb5;
		bool bb1;
		bool bb2;
		bool bb3;
		bool bb4;
		bool bb5;
		bb1=N3.GetNext(vb1);
		bb2=N3.GetNext(vb2);
		bb3=N3.GetNext(vb3);
		bb4=N3.GetNext(vb4);
		bb5=N3.GetNext(vb5);
		TS_ASSERT_EQUALS(bb1,true);
		TS_ASSERT_EQUALS(bb2,true);
		TS_ASSERT_EQUALS(bb3,true);
		TS_ASSERT_EQUALS(bb4,true);
		TS_ASSERT_EQUALS(bb5,false);
		TS_ASSERT_EQUALS((vb1.Get(1)),3);
		TS_ASSERT_EQUALS((vb2.Get(1)),5);
		TS_ASSERT_EQUALS((vb1.Get(2)),6);
		TS_ASSERT_EQUALS((vb2.Get(2)),6);
		
		TS_ASSERT_EQUALS((vb3.Get(2)),5);
		TS_ASSERT_EQUALS((vb4.Get(2)),7);
		TS_ASSERT_EQUALS((vb3.Get(1)),4);
		TS_ASSERT_EQUALS((vb4.Get(1)),4);
	}
};
