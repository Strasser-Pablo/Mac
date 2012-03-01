#define Testing_Partial_Mac
#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#include "../src/MacWorld.h"
#include "../src/CalculateMacMaximalSpeed.h"
#include "../src/ApplyToEveryMacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/TableContainerList.h"
#include "../src/GetCellType.h"
#define eps 1e-10
class Test_MaximalSpeed : public CxxTest::TestSuite
{
	typedef MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > > world;
	MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > >  m_world;
public:
	void Test_Max(){
		typedef GetCellType<world> type_getcelltype;
		KeyTableMap<int,MacCell<3,double,int> > k;
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		k[1]=MacCell<3,double,int>(v,4.0,1,0);
		v.Set(USEELLIPSE,0.5,0.2,0.4);
		k[2]=MacCell<3,double,int>(v,8.0,1,0);
		v.Set(USEELLIPSE,0.01,0.01,0.1);
		k[3]=MacCell<3,double,int>(v,8.0,1,0);
		m_world.m_mac_grid=k;
		int m_air=0;
		int m_fluid=1;
		int m_boundary_air=2;
		int m_boundary_fluid=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		type_getcelltype m_GetCellType(m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air);
		CalculateMacMaximalSpeed<MacCell<3,double,int>,GetCellType<world> > max(m_GetCellType);
		ApplyToEveryMacCell<CalculateMacMaximalSpeed<MacCell<3,double,int>,GetCellType<world> > ,MacWorld<KeyTableMap<int,MacCell<3,double,int> >,TableContainerList<Physvector<3,double> > > >(m_world,max);
		TS_ASSERT_DELTA(1.0,max.GetResult(),eps);
	}
};