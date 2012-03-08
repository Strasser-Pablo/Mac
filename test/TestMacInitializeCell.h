#include <cxxtest/TestSuite.h>
#include "../src/MacInitializeCell.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/MacGetStagPos.h"
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
		typedef MacGetStagPos<world>  type_stag;
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<bool(Physvector<3,int>)> type_part_cond;
		typedef std::function<double(Physvector<3,int>)> type_pres_func;
		
		list_part lpart;
		order O;
		keytable table(O);
	    vect v;
		v.SetAll(0);
		keyvect k1;
		k1.SetAll(10);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		part p1(v);
		lpart.push_back(p1);
		vect m_v_h;
		m_v_h.SetAll(1);
		world w(table,lpart);
		type_stag m_stag(m_v_h);
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
		type_getcelltype m_GetCellType(w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_rho_inter_bound,m_1_rho_inter,m_1_rho_inter_bound);
		type_part_cond m_part_cond=[](Physvector<3,int> key){return false;};
		type_pres_func m_pres_func=[](Physvector<3,int> key){return 0;};
		MacInitializeCell<world,type_stag,type_getcelltype,type_part_cond,type_pres_func>init(w,m_GetCellType,m_v_h,m_v_h,2,m_stag,m_part_cond,m_pres_func);
		init.Update();
		keytable &res=w.m_mac_grid;
		k1.SetAll(0);
		int type;
		res[k1].GetCellType(type);
		TS_ASSERT_EQUALS(type,1);
		res[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,0);
		k1.Set(1,1);
		res[k1].GetCellType(type);
		TS_ASSERT_EQUALS(type,0);
		res[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,1);
		
		k1.Set(2,1);
		res[k1].GetCellType(type);
		TS_ASSERT_EQUALS(type,0);
		res[k1].GetLayer(type);
		TS_ASSERT_EQUALS(type,2);
		k1.SetAll(10);
		TS_ASSERT(!res.Exist(k1));
		
	}
};
