#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellFluid.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Particle.h"
#include "../src/MacGetStagPos.h"
#include "../src/GetCellType.h"
#define eps 1e-10
class Test_UpdateCellFluid : public CxxTest::TestSuite
{
	public:
	void testupdate()
	{
		typedef MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > > type_world;
		typedef MacGetStagPos<type_world>  type_stag;
		typedef GetCellType<type_world> type_getcelltype;
		PhysvectorKeyOrder<3,int> korder;
		
		KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > > grid(korder);
		TableContainerList<Particle<Physvector<3,double> > > list_part;
		
		
		Physvector<3,double> v;
		v.Set(USEELLIPSE,1.0,2.0,3.0);
		Particle<Physvector<3,double> > part(v);
		
		list_part.push_back(part);
		
		v.Set(USEELLIPSE,3.0,2.0,3.0);
		Particle<Physvector<3,double> > part2(v);
		
		list_part.push_back(part2);
		
		type_world world(grid,list_part);
		Physvector<3,double> v_h;
		v_h.SetAll(1.0);
		type_stag m_stag(v_h);
		int m_fluid=1;
		int m_air=0;
		int m_boundary_fluid=2;
		int m_boundary_air=3;
		type_getcelltype m_GetCellType(m_fluid,m_boundary_fluid,m_air,m_boundary_air);
		UpdateCellFluid<type_world,type_stag ,type_getcelltype> U(world,v_h,v_h,m_GetCellType,m_stag);
		U.Update();
		MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > >::type_keytable::const_iterator it=world.m_mac_grid.begin();
		
		TS_ASSERT_EQUALS(it.key().Get(1),1);
		TS_ASSERT_EQUALS(it.key().Get(2),2);
		TS_ASSERT_EQUALS(it.key().Get(3),3);
		int layer;
		it.data().GetLayer(layer);
		TS_ASSERT_EQUALS(layer,0);
		int cell_type;
		it.data().GetCellType(cell_type);
		TS_ASSERT_EQUALS(cell_type,1);
		++it;
		TS_ASSERT_EQUALS(it.key().Get(1),3);
		TS_ASSERT_EQUALS(it.key().Get(2),2);
		TS_ASSERT_EQUALS(it.key().Get(3),3);
		it.data().GetLayer(layer);
		TS_ASSERT_EQUALS(layer,0);
		it.data().GetCellType(cell_type);
		TS_ASSERT_EQUALS(cell_type,1);
	}
};