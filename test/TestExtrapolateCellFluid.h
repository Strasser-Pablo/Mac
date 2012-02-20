#include <cxxtest/TestSuite.h>
#include "../src/MacGetVelocity.h"
#include "../src/MacInitializeCell.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/ExtrapolateCellFluid.h"
#define eps 1e-10
class Test_MacConvect : public CxxTest::TestSuite
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
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
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
		NeighborsVelocity<1,int> Nv;
		ExtrapolateCellFluid<world>  Ex(W,1,1,Nv);
		Ex.Calculate();
		vkey.Set(1,0);
		int lay;
		Physvector<1,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
	}
	
	void test1dvar()
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
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
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
		NeighborsVelocity<1,int> Nv;
		Physvector<1,int> vv;
		vv.Set(1,1);
		Nv.Set(1,vv);
		ExtrapolateCellFluid<world>  Ex(W,1,1,Nv);
		Ex.Calculate();
		vkey.Set(1,0);
		int lay;
		Physvector<1,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
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
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		mac c5(temp2,0,0,-1);
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
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(2,-1);
		k[vkey]=c5;
		list_part lp;
		world W(k,lp);
		NeighborsVelocity<2,int> Nv;
		ExtrapolateCellFluid<world>  Ex(W,1,1,Nv);
		Ex.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		int lay;
		Physvector<2,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
	}
	
		void test2dvar()
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
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		mac c5(temp2,0,0,-1);
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
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(2,-1);
		k[vkey]=c5;
		list_part lp;
		world W(k,lp);
		NeighborsVelocity<2,int> Nv;
		Physvector<2,int> vvv;
		vvv.Set(1,1);
		vvv.Set(2,0);
		Nv.Set(1,vvv);
		vvv.Set(1,0);
		vvv.Set(2,1);
		Nv.Set(2,vvv);
		ExtrapolateCellFluid<world>  Ex(W,1,1,Nv);
		Ex.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		int lay;
		Physvector<2,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),0.0,eps);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),2.0,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),3.0,eps);
	}
}
;