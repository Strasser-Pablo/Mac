#include <cxxtest/TestSuite.h>
#include "../src/ParticleToKey.h"
#include "../src/RundingFunction.h"
#include "../src/Particle.h"
#define eps 1e-10
class Test_ParticleToKey : public CxxTest::TestSuite
{
	public:
	void testToKey(){
		Physvector<3,double> v;
		Physvector<3,int> vk;
		v.Set(USEELLIPSE,1.0,2.0,3.0);
		Particle<Physvector<3,double> > part(v);
		Physvector<3,double> v_h;
		v_h.SetAll(1);
		ParticleToKey<Particle<Physvector<3,double> >,int,double,3> ptk(v_h,v_h);
		vk=ptk.ToKey(part);
		TS_ASSERT_EQUALS(vk.Get(1),1);
		TS_ASSERT_EQUALS(vk.Get(2),2);
		TS_ASSERT_EQUALS(vk.Get(3),3);
	}
};