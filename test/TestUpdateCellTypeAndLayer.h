#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellTypeAndLayer.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/GetCellType.h"
#include <functional>
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
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<double(Physvector<3,int>)> type_pres_func;
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(USEELLIPSE,0,0,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		world w(table,lpart);
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
		type_getcelltype m_GetCellType(w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_pres_func m_pres_func=[](Physvector<3,int> key __attribute__ ((unused))){return 0;};
		UpdateCellTypeAndLayer<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
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
