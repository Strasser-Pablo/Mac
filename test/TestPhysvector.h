#define TesThrowIntExcept
#include <cxxtest/TestSuite.h>
#include "../src/Physvector.h"
#define eps 1e-10
class Test_Physvector : public CxxTest::TestSuite
{
	Physvector<2,double> v1;
	Physvector<2,double> v2;
	Physvector<2,double> v2_2;
public:
void setUp(){
	v1.Set(USEELLIPSE,1.0,2.0);
	v2.Set(USEELLIPSE,5.0,3.0);
	v2_2.Set(USEELLIPSE,5.0,3.0);
}
void testassignement(){
	v1=v2;
	TS_ASSERT_DELTA(v1.Get(1),v2.Get(1),eps);
	TS_ASSERT_DELTA(v1.Get(2),v2.Get(2),eps);
	TS_ASSERT(v1==v2);
	TS_ASSERT(!(v1!=v2));
	v1.Set(1,3.15);
	TS_ASSERT_DELTA(v1.Get(1),3.15,eps);
	TS_ASSERT(!(v1==v2));
	TS_ASSERT(v1!=v2);
}
void testarithmetic(){
	Physvector<2,double> vres;
	vres=v1+v2;
	TS_ASSERT_DELTA(vres.Get(1),v1.Get(1)+v2.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),v1.Get(2)+v2.Get(2),eps);
	vres=v1-v2;
	TS_ASSERT_DELTA(vres.Get(1),v1.Get(1)-v2.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),v1.Get(2)-v2.Get(2),eps);
	vres=2.0*v1;
	TS_ASSERT_DELTA(vres.Get(1),2*v1.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),2*v1.Get(2),eps);
	vres=v1*2.0;
	TS_ASSERT_DELTA(vres.Get(1),v1.Get(1)*2,eps);
	TS_ASSERT_DELTA(vres.Get(2),v1.Get(2)*2,eps);
	vres=v1;
	vres+=v2;
	TS_ASSERT_DELTA(vres.Get(1),v1.Get(1)+v2.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),v1.Get(2)+v2.Get(2),eps);
	vres=v1;
	vres-=v2;
	TS_ASSERT_DELTA(vres.Get(1),v1.Get(1)-v2.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),v1.Get(2)-v2.Get(2),eps);
	vres=v1;
	vres*=2.0;
	TS_ASSERT_DELTA(vres.Get(1),2*v1.Get(1),eps);
	TS_ASSERT_DELTA(vres.Get(2),2*v1.Get(2),eps);
}
};
