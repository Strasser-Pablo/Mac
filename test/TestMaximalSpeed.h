#define Testing_Partial_Mac
#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#include "../src/MacWorld.h"
#include "../src/CalculateMacMaximalSpeed.h"
#include "../src/ApplyToEveryMacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/TableContainerList.h"
#include "../src/GetCellType.h"
#include "../src/PhysvectorKeyOrder.h"
#define eps 1e-10
class Test_MaximalSpeed : public CxxTest::TestSuite
{
public:
	void Test_Max(){
		typedef MacWorld<KeyTableMap<Physvector<1,int>,MacCell<3,double,int>,PhysvectorKeyOrder<1,int> >,TableContainerList<Physvector<3,double> > > world;
		typedef TableContainerList<Physvector<3,double> > table_cont; 
		typedef GetCellType<world> type_getcelltype;
		PhysvectorKeyOrder<1,int> Ord;
		KeyTableMap<Physvector<1,int>,MacCell<3,double,int>,PhysvectorKeyOrder<1,int> > k(Ord);
		Physvector<3,double> v;
		Physvector<1,int> pos;
		pos.Set(1,1);
		v.Set(USEELLIPSE,1.0,0.0,0.0);
		k[pos]=MacCell<3,double,int>(v,4.0,1,0);
		v.Set(USEELLIPSE,0.5,0.2,0.4);
		pos.Set(1,2);
		k[pos]=MacCell<3,double,int>(v,8.0,1,0);
		v.Set(USEELLIPSE,0.01,0.01,0.1);
		pos.Set(1,3);
		k[pos]=MacCell<3,double,int>(v,8.0,1,0);
		world  m_world(k,table_cont());
		m_world.m_mac_grid=k;
		int m_air=0;
		int m_fluid=1;
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
		type_getcelltype m_GetCellType(m_world,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		CalculateMacMaximalSpeed<MacCell<3,double,int>,GetCellType<world> > max(m_GetCellType);
		ApplyToEveryMacCell<CalculateMacMaximalSpeed<MacCell<3,double,int>,GetCellType<world> > ,world >(m_world,max);
		TS_ASSERT_DELTA(1.0,max.GetResult(),eps);
	}
};
