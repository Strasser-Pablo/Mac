#define Testing_Partial_Mac
#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#include "../src/MacWorld.h"
#include "../src/CalculateMacMaximalSpeed.h"
#include "../src/ApplyToEveryMacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/TableContainerList.h"
#include "../src/CalculateTimeStep.h"
#include "../src/GetCellType.h"
#define eps 1e-10
#define Testing_Partial_Mac
class Test_CalculateTimeStep : public CxxTest::TestSuite
{
	MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > >  m_world;
	
public:
	void testCalculate(){
		typedef MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > > world;
		KeyTableMap<int,MacCell<3,double,int> > k;
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		k[1]=MacCell<3,double,int>(v,4.0,1,0);
		m_world.m_mac_grid=k;
		double m_h=1.0;
		double m_factor=1.0;
		double m_dt=0.0;
		int m_fluid=1;
		int m_air=0;
		int m_boundary_air=2;
		int m_boundary_fluid=3;
		GetCellType<world> m_getcelltype(m_fluid,m_boundary_fluid,m_air,m_boundary_air);
		CalculateTimeStep<world,double,GetCellType<world> > timestep(m_world,m_h,m_factor,m_dt,m_getcelltype);
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
		v.Set(USEELLIPSE,0.10,0.20,0.40);
		k[2]=MacCell<3,double,int>(v,4.0,1,0);
		m_world.m_mac_grid=k;
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
	}
};
	