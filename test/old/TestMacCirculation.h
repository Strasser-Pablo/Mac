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
#include "../src/MacCalculateCirculation.h"

#define eps 1e-10

class TestMacCalculateCirculation : public CxxTest::TestSuite
{

	public:
	void testCirculationMax()
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
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c1(temp,0,1,0);
		temp.Set(1,0.0);
		temp.Set(2,2.0);
		mac c2(temp,0,1,0);
		temp.Set(1,-2.0);
		temp.Set(2,2.0);
		mac c3(temp,0,1,0);
		temp.Set(1,-2.0);
		temp.Set(2,0.0);
		mac c4(temp,0,0,1);
		temp.Set(1,-2.0);
		temp.Set(2,-2.0);
		mac c5(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,-2.0);
		mac c6(temp,0,0,1);
		temp.Set(1,2.0);
		temp.Set(2,-2.0);
		mac c7(temp,0,0,1);
		temp.Set(1,2.0);
		temp.Set(2,0.0);
		mac c8(temp,0,0,1);
		temp.Set(1,2.0);
		temp.Set(2,2.0);
		mac c9(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		vkey.Set(2,0);
		k[vkey]=c2;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(1,-1);
		vkey.Set(2,1);
		k[vkey]=c5;
		vkey.Set(1,-1);
		vkey.Set(2,0);
		k[vkey]=c6;
		vkey.Set(1,-1);
		vkey.Set(2,-1);
		k[vkey]=c7;
		vkey.Set(1,0);
		vkey.Set(2,-1);
		k[vkey]=c8;
		vkey.Set(1,1);
		vkey.Set(2,-1);
		k[vkey]=c9;
		list_part lp;
		world W(k,lp);
		Physvector<2,double> m_v_h;
		m_v_h.Set(1,1.0);
		m_v_h.Set(2,1.0);
		MacCalculateCirculation<world> m_circ(W,m_v_h);
		m_circ.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		double d_circ;
		W.m_mac_grid[vkey].GetCirculation(d_circ);
		TS_ASSERT_DELTA(d_circ,8.0,eps);
	}
	void testCirculationOp()
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
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c1(temp,0,1,0);
		temp.Set(1,0.0);
		temp.Set(2,-2.0);
		mac c2(temp,0,1,0);
		temp.Set(1,+2.0);
		temp.Set(2,-2.0);
		mac c3(temp,0,1,0);
		temp.Set(1,+2.0);
		temp.Set(2,0.0);
		mac c4(temp,0,0,1);
		temp.Set(1,+2.0);
		temp.Set(2,+2.0);
		mac c5(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,+2.0);
		mac c6(temp,0,0,1);
		temp.Set(1,-2.0);
		temp.Set(2,+2.0);
		mac c7(temp,0,0,1);
		temp.Set(1,-2.0);
		temp.Set(2,0.0);
		mac c8(temp,0,0,1);
		temp.Set(1,-2.0);
		temp.Set(2,-2.0);
		mac c9(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		vkey.Set(2,0);
		k[vkey]=c2;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(1,-1);
		vkey.Set(2,1);
		k[vkey]=c5;
		vkey.Set(1,-1);
		vkey.Set(2,0);
		k[vkey]=c6;
		vkey.Set(1,-1);
		vkey.Set(2,-1);
		k[vkey]=c7;
		vkey.Set(1,0);
		vkey.Set(2,-1);
		k[vkey]=c8;
		vkey.Set(1,1);
		vkey.Set(2,-1);
		k[vkey]=c9;
		list_part lp;
		world W(k,lp);
		Physvector<2,double> m_v_h;
		m_v_h.Set(1,1.0);
		m_v_h.Set(2,1.0);
		MacCalculateCirculation<world> m_circ(W,m_v_h);
		m_circ.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		double d_circ;
		W.m_mac_grid[vkey].GetCirculation(d_circ);
		TS_ASSERT_DELTA(d_circ,-8.0,eps);
	}

	void testCirculationNoCirc()
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
		temp.Set(2,-2.0);
		mac c1(temp,0,1,0);
		temp.Set(1,2.0);
		temp.Set(2,0.0);
		mac c2(temp,0,1,0);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c3(temp,0,1,0);
		temp.Set(1,0.0);
		temp.Set(2,-2.0);
		mac c4(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c5(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c6(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c7(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c8(temp,0,0,1);
		temp.Set(1,0.0);
		temp.Set(2,0.0);
		mac c9(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		vkey.Set(2,0);
		k[vkey]=c2;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(1,-1);
		vkey.Set(2,1);
		k[vkey]=c5;
		vkey.Set(1,-1);
		vkey.Set(2,0);
		k[vkey]=c6;
		vkey.Set(1,-1);
		vkey.Set(2,-1);
		k[vkey]=c7;
		vkey.Set(1,0);
		vkey.Set(2,-1);
		k[vkey]=c8;
		vkey.Set(1,1);
		vkey.Set(2,-1);
		k[vkey]=c9;
		list_part lp;
		world W(k,lp);
		Physvector<2,double> m_v_h;
		m_v_h.Set(1,1.0);
		m_v_h.Set(2,1.0);
		MacCalculateCirculation<world> m_circ(W,m_v_h);
		m_circ.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		double d_circ;
		W.m_mac_grid[vkey].GetCirculation(d_circ);
		TS_ASSERT_DELTA(d_circ,0.0,eps);
	}

};
