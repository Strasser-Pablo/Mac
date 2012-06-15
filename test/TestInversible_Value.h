#include <cxxtest/TestSuite.h>
#include "../src/Inversible_Value.h"
#include "../src/Inversible_Value_Vect.h"
#define eps 1e-10
class Test_Inversible_Value : public CxxTest::TestSuite
{
	public:
	void testscalar()
	{
		Inversible_Value<double> inv(2.3);
		TS_ASSERT_DELTA(inv.Get(),2.3,eps);
		TS_ASSERT_DELTA(inv.Get_Inv(),1/2.3,eps);
		Inversible_Value<double> inv2;
		inv2=inv;
		TS_ASSERT_DELTA(inv2.Get(),2.3,eps);
		TS_ASSERT_DELTA(inv2.Get_Inv(),1/2.3,eps);
	}
	void testvector()
	{
		typedef Physvector<2,double> type_v;
		type_v v;
		v.Set(1,2.3);
		v.Set(2,3.4);
		Inversible_Value<type_v> inv(v);
		TS_ASSERT_DELTA(inv.Get().Get(1),2.3,eps);
		TS_ASSERT_DELTA(inv.Get_Inv().Get(1),1/2.3,eps);
	}
};
