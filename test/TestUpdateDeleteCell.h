#include <cxxtest/TestSuite.h>
#include "../src/UpdateDeleteCell.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#define eps 1e-10
class Test_TestUpdateDeleteCell : public CxxTest::TestSuite
{
	public:
	void testUpdate(){
		typedef Physvector<3,int> keyvect;
		typedef Physvector<3,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<3,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<3,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(USEELLIPSE,0,0,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(-1);
		k1.Set(USEELLIPSE,0,3,4);
		table[k1].SetCellType(1);
		table[k1].SetLayer(-1);
		world w(table,lpart);
		UpdateDeleteCell<world> U(w);
		U.Update();
		TS_ASSERT(w.m_mac_grid.empty());
	}
};