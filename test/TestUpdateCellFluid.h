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
#include <functional>
#define eps 1e-10
class Test_UpdateCellFluid : public CxxTest::TestSuite
{
	public:
	void testupdate()
	{
		typedef MacWorld<KeyTableMap<Physvector<3,int>,MacCell<3,double,int>,PhysvectorKeyOrder<3,int > >, TableContainerList<Particle<Physvector<3,double> > > > type_world;
		typedef MacGetStagPos<type_world>  type_stag;
		typedef GetCellType<type_world> type_getcelltype;
		typedef std::function<bool(Physvector<3,int>)> type_part_cond;
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
		type_getcelltype m_GetCellType(world,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_part_cond m_part_cond=[](Physvector<3,int> key __attribute__ ((unused))){return false;};
		UpdateCellFluid<type_world,type_stag ,type_getcelltype,type_part_cond> U(world,v_h,v_h,m_GetCellType,m_stag,m_part_cond);
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
