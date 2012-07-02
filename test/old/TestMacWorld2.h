#include <cxxtest/TestSuite.h>
#include "../src/MacWorld2.h"
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
class Test_MacWorld2 : public CxxTest::TestSuite
{
	public:
		void test2d()
	{
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld2<keytable,list_part,2> world;
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
		TS_ASSERT_EQUALS(W.GetNextId(),0);
		TS_ASSERT_EQUALS(W.GetNextId(),1);
		TS_ASSERT_EQUALS(W.GetNextId(),2);
		TS_ASSERT_EQUALS(W.GetNextId(),3);
		W.FreeId(2);
		TS_ASSERT_EQUALS(W.GetNextId(),2);
		TS_ASSERT_EQUALS(W.GetNextId(),4);
	}
	
};
