#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellToInitialLayer.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Particle.h"
#define eps 1e-10
class Test_UpdateCellToInitialLayer: public CxxTest::TestSuite
{
	public:
	void testupdate()
	{
		PhysvectorKeyOrder<3,int> korder;
		
		KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > > grid(korder);
		TableContainerList<Particle<Physvector<3,double> > > list_part;
		
		
		Physvector<3,int> k;
		k.Set(USEELLIPSE,1,2,3);
		grid[k];
		k.Set(USEELLIPSE,1,2,3);
		grid[k];
		
		k.Set(USEELLIPSE,1,2,3);
		grid[k];
		
		MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > > world(grid,list_part);
		UpdateCellToInitialLayer<MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > > > U(world);
		U.Update();
		for(MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > >::type_keytable::const_iterator it=world.m_mac_grid.begin();it!=world.m_mac_grid.end();++it)
		{
		int layer;
		it.data().GetLayer(layer);
		TS_ASSERT_EQUALS(layer,-1);
		}
	}
};