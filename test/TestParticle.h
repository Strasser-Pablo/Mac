#include <cxxtest/TestSuite.h>
#include "../src/Particle.h"
#define eps 1e-10
class Test_Partice : public CxxTest::TestSuite
{
	Particle<double> m_part;
public:
	void testCreation(){
		double x;
		double v;
		m_part.SetPos(2.0);
		m_part.GetPos(x);
		TS_ASSERT_DELTA(x,2.0,eps);
		
		Particle<double> temp(5.0);
		temp.GetPos(x);
		TS_ASSERT_DELTA(x,5.0,eps);
	}
};