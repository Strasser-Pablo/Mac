#define Testing_Partial_Mac
#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#include "../src/MacWorld.h"
#include "../src/CalculateMacMaximalSpeed.h"
#include "../src/ApplyToEveryMacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/TableContainerList.h"
#define eps 1e-10
class Test_MaximalSpeed : public CxxTest::TestSuite
{
	MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > >  m_world;
public:
	void Test_Max(){
		KeyTableMap<int,MacCell<3,double,int> > k;
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		k[1]=MacCell<3,double,int>(v,4.0,1,0);
		v.Set(USEELLIPSE,0.5,0.2,0.4);
		k[2]=MacCell<3,double,int>(v,8.0,1,0);
		v.Set(USEELLIPSE,0.01,0.01,0.1);
		k[3]=MacCell<3,double,int>(v,8.0,1,0);
		m_world.m_mac_grid=k;
		int m_fluid=1;
		CalculateMacMaximalSpeed<MacCell<3,double,int> > max(m_fluid);
		ApplyToEveryMacCell<CalculateMacMaximalSpeed<MacCell<3,double,int> > ,MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > > >(m_world,max);
		TS_ASSERT_DELTA(1.0,max.GetResult(),eps);
	}
};