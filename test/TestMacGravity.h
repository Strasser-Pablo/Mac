#include <cxxtest/TestSuite.h>
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/MacGravity.h"
#include "../src/NeighborsVelocity.h"
#include "../src/MacGetStagPos.h"
#include "../src/GetCellType.h"
#define eps 1e-10
class Test_MacGravity : public CxxTest::TestSuite
{
	public:
	void test1d()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
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
		GetCellType<world> m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		Physvector<1,double> g;
		g.Set(1,-9.81);
		MacGravity<world,GetCellType<world> > grav(W,g,0.1,1,m_GetCellType);
		grav.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2-9.81*0.1,eps);
	}
	
		void test2d()
	{
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,0.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
		world W(k,lp);
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
		GetCellType<world> m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		Physvector<2,double> g;
		g.Set(1,-9.81);
		g.Set(2,0);
		MacGravity<world,GetCellType<world> > grav(W,g,0.1,1,m_GetCellType);
		grav.Calculate();
		Physvector<2,double> vtemp;
		vkey.Set(1,0);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2-9.81*0.1,eps);
	}
	
	void test1dneigh()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
		world W(k,lp);
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
		GetCellType<world> m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		MacGetStagPos<world> stagPos(vh);
		Physvector<1,double> g;
		g.Set(1,-9.81);
		MacGravity<world,GetCellType<world> > grav(W,g,0.1,1,m_GetCellType);
		grav.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2-9.81*0.1,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2-9.81*0.1,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2,eps);
	}
	
};
