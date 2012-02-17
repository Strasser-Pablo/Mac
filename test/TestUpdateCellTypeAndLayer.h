#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellTypeAndLayer.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#define eps 1e-10
class Test_TestUpdateCellTypeAndLayer : public CxxTest::TestSuite
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
		table[k1].SetLayer(0);
		world w(table,lpart);
		int m_fluid=1;
		int m_air=0;
		UpdateCellTypeAndLayer<world> Up(w,m_fluid,m_air,2);
		Up.Update();
		int type;
		k1.Set(USEELLIPSE,1,0,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(USEELLIPSE,-1,0,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(USEELLIPSE,0,1,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(USEELLIPSE,0,-1,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(USEELLIPSE,0,0,1);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(USEELLIPSE,0,0,-1);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		
		k1.Set(USEELLIPSE,1,1,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,2);
		
		k1.Set(USEELLIPSE,2,0,0);
		
		w.m_mac_grid[k1].GetCellType(type);
			TS_ASSERT_EQUALS(type,0);
		w.m_mac_grid[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,2);
		}
};