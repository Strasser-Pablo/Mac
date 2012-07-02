#include <cxxtest/TestSuite.h>
#include "../src/ApplyToEveryPhysvectorData.h"
#include "../src/RundingFunction.h"
#define eps 1e-10
class Test_ApplyToVectorElement : public CxxTest::TestSuite
{
	public:
	void testapply(){
		Physvector<3,double> v;
		v.Set(USEELLIPSE,0.4,0.2,0.2);
		Round<double,int> R;
		Physvector<3,int> vres;
		ApplyToEveryPhysvectorData<double,int,Round<double,int>,3> app;
		app.Transform(v,vres,R);
		TS_ASSERT_EQUALS(vres.Get(1),0);
		TS_ASSERT_EQUALS(vres.Get(2),0);
		TS_ASSERT_EQUALS(vres.Get(3),0);
		v.Set(USEELLIPSE,0.6,0.2,0.6);
		app.Transform(v,vres,R);
		TS_ASSERT_EQUALS(vres.Get(1),1);
		TS_ASSERT_EQUALS(vres.Get(2),0);
		TS_ASSERT_EQUALS(vres.Get(3),1);
	}
};