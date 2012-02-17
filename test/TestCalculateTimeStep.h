#define Testing_Partial_Mac
#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#include "../src/MacWorld.h"
#include "../src/CalculateMacMaximalSpeed.h"
#include "../src/ApplyToEveryMacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/TableContainerList.h"
#include "../src/CalculateTimeStep.h"
#define eps 1e-10
#define Testing_Partial_Mac
class Test_CalculateTimeStep : public CxxTest::TestSuite
{
	MacWorld<KeyTableMap<int,MacCell<3,double,double> >,TableContainerList<Physvector<3,double> > >  m_world;
	
public:
	void testCalculate(){
		KeyTableMap<int,MacCell<3,double,double> > k;
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		k[1]=MacCell<3,double,double>(v,4.0);
		m_world.m_mac_grid=k;
		double m_h=1.0;
		double m_factor=1.0;
		double m_dt=0.0;
		CalculateTimeStep<MacWorld<KeyTableMap<int,MacCell<3,double,double> >,TableContainerList<Physvector<3,double> > >,double> timestep(m_world,m_h,m_factor,m_dt);
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
		v.Set(USEELLIPSE,0.10,0.20,0.40);
		k[2]=MacCell<3,double,double>(v,4.0);
		m_world.m_mac_grid=k;
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
	}
};
	