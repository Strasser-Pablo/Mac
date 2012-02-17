#include <cxxtest/TestSuite.h>
#include "../src/NeighborsVelocity.h"
#define eps 1e-10
class Test_MacCell : public CxxTest::TestSuite
{
public:
	void Test1d()
	{
		NeighborsVelocity<1,int> N;
		Physvector<1,int> k;
		TS_ASSERT(!N.Get(1,k));
		Physvector<1,int> v;
		v.Set(1,1);
		TS_ASSERT(N.Set(1,v));
		TS_ASSERT(N.Get(1,k));
		TS_ASSERT_EQUALS(k.Get(1),1);
		TS_ASSERT(!N.Set(2,v));
		TS_ASSERT(!N.Set(0,v));
		
		TS_ASSERT(!N.Get(2,k));
		TS_ASSERT(!N.Get(0,k));
	}
	
	void Test2d()
	{
		NeighborsVelocity<2,int> N;
		Physvector<2,int> k;
		TS_ASSERT(!N.Get(2,k));
		Physvector<2,int> v;
		v.Set(1,1);
		v.Set(2,1);
		TS_ASSERT(N.Set(1,v));
		TS_ASSERT(N.Get(1,k));
		TS_ASSERT_EQUALS(k.Get(1),1);
		TS_ASSERT_EQUALS(k.Get(2),1);
		
		TS_ASSERT(!N.Set(3,v));
		TS_ASSERT(!N.Set(0,v));
		
		TS_ASSERT(!N.Get(3,k));
		TS_ASSERT(!N.Get(0,k));
	}
};