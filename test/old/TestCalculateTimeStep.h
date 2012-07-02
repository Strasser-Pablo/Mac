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
#include "../src/PhysvectorKeyOrder.h"
#define eps 1e-10
#define Testing_Partial_Mac
class Test_CalculateTimeStep : public CxxTest::TestSuite
{
	
	
public:
	void testCalculate(){
		typedef MacWorld<KeyTableMap<Physvector<1,int>,MacCell<3,double,int>,PhysvectorKeyOrder<1,int> >,TableContainerList<Physvector<3,double> > > world;
		PhysvectorKeyOrder<1,int> ord;
		KeyTableMap<Physvector<1,int>,MacCell<3,double,int>,PhysvectorKeyOrder<1,int> > k(ord);
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		Physvector<1,int> pos;
		pos.Set(1,1);
		k[pos]=MacCell<3,double,int>(v,4.0,1,0);
		world  m_world(k,TableContainerList<Physvector<3,double> >());
		m_world.m_mac_grid=k;
		double m_h=1.0;
		double m_factor=1.0;
		double m_dt=0.0;
		int m_fluid=1;
		int m_air=0;
		int m_boundary_air=2;
		int m_boundary_fluid=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		GetCellType<world> m_getcelltype(m_world,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		CalculateTimeStep<world,double,GetCellType<world> > timestep(m_world,m_h,m_factor,m_dt,m_getcelltype);
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
		v.Set(USEELLIPSE,0.10,0.20,0.40);
		pos.Set(1,2);
		k[pos]=MacCell<3,double,int>(v,4.0,1,0);
		m_world.m_mac_grid=k;
		timestep.Calculate();
		TS_ASSERT_DELTA(m_dt,1.0,eps);
	}
};
	
