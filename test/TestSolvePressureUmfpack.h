#include <cxxtest/TestSuite.h>
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/SolvePressureUmfpack.h"
#define eps 1e-10
class Test_SolvePressureUmfpack : public CxxTest::TestSuite
{
	public:
	void test1dconst()
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
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
		mac c1(temp,2,1,0);
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
	}
	
	void test1dvarspeed()
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
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c1(temp,2,1,0);
		mac c2(temp2,0,0,1);
		mac c3(temp2,0,0,1);
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),1.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,1.0,eps);
		
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),1.0,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
	}
	
		void test2dconst()
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
		mac c4(temp,0,0,1);
		mac c5(temp,0,0,1);
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
		Physvector<2,double> vh;
		vh.Set(1,1.0);
		vh.Set(2,1.0);
		SolvePressureUmfpack<world> press(W,vh,1);
		press.Calculate();
		Physvector<2,double> vtemp;
		vkey.Set(1,0);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
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
		temp.Set(2,0.0);
		mac c1(temp,2,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		mac c4(temp,0,0,1);
		mac c5(temp,0,0,1);
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
		Physvector<2,double> vh;
		vh.Set(1,1.0);
		vh.Set(2,1.0);
		SolvePressureUmfpack<world> press(W,vh,1);
		press.Calculate();
		Physvector<2,double> vtemp;
		vkey.Set(1,0);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
	}
	
	void test2dvarspeed()
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
		
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c1(temp,2,1,0);
		mac c2(temp2,0,0,1);
		mac c3(temp2,0,0,1);
		mac c4(temp2,0,0,1);
		mac c5(temp2,0,0,1);
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
		Physvector<2,double> vh;
		vh.Set(1,1.0);
		vh.Set(2,1.0);
		SolvePressureUmfpack<world> press(W,vh,1);
		press.Calculate();
		Physvector<2,double> vtemp;
		vkey.Set(1,0);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),1.5,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),-0.5,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.5,eps);
		
		vkey.Set(1,1);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.5,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0.5,eps);
		
		vkey.Set(1,-1);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0,eps);
		TS_ASSERT_DELTA(vtemp.Get(2),0,eps);
	}
	
	void test1dconst2()
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
		c1.SetConstSpeed(1,true);
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
	}
	
	void test1dvar2()
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
		mac c1(temp,2,1,0);
		c1.SetConstSpeed(1,true);
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		W.m_mac_grid[vkey].GetPressure(ptemp);
	}
	
	void test1dvarspeed2()
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
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c1(temp,2,1,0);
		c1.SetConstSpeed(1,true);
		mac c2(temp2,0,0,1);
		mac c3(temp2,0,0,1);
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
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,2.0,eps);
		
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),2.0,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
	}
		void test1dvarspeed3()
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
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c1(temp,2,1,0);
		mac c2(temp2,2,1,0);
		c2.SetConstSpeed(1,true);
		mac c3(temp2,0,0,1);
		mac c4(temp2,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c3;
		vkey.Set(1,-1);
		k[vkey]=c2;
		vkey.Set(1,-2);
		k[vkey]=c4;
		list_part lp;
		world W(k,lp);
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		SolvePressureUmfpack<world> pres(W,vh,1);
		pres.Calculate();
		Physvector<1,double> vtemp;
		vkey.Set(1,0);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
		double ptemp;
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,0.0,eps);
		
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
		
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetPressure(ptemp);
		TS_ASSERT_DELTA(ptemp,-2.0,eps);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
		
		vkey.Set(1,-2);
		W.m_mac_grid[vkey].GetSpeed(vtemp);
		TS_ASSERT_DELTA(vtemp.Get(1),0.0,eps);
	}
};