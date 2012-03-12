#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellTypeAndLayer3.h"
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
		void test2dUpdate(){
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<double(Physvector<2,int>)> type_pres_func;
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(1,0);
		k1.Set(2,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		world w(table,lpart);
		int m_fluid=1;
		int m_air=0;
		int m_boundary_fluid=2;
		int m_boundary_air=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		type_getcelltype m_GetCellType(w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_pres_func m_pres_func=[](Physvector<2,int> key){return 0;};
		UpdateCellTypeAndLayer3<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
		Up.Update();
		keyvect k;
		k.Set(1,1);
		k.Set(2,0);
		int c;
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));
		k.Set(1,1);
		k.Set(2,1);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));
		k.Set(1,0);
		k.Set(2,0);
		TS_ASSERT(m_GetCellType.GetIsFluid(k));
		}

		void test2dUpdate2(){
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<double(Physvector<2,int>)> type_pres_func;
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(1,1);
		k1.Set(2,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		keyvect k2;
		k2.Set(1,0);
		k2.Set(2,1);
		table[k2].SetCellType(1);
		table[k2].SetLayer(0);
		
		keyvect k3;
		k3.Set(1,-1);
		k3.Set(2,0);
		table[k3].SetCellType(1);
		table[k3].SetLayer(0);
		
		keyvect k4;
		k4.Set(1,0);
		k4.Set(2,-1);
		table[k4].SetCellType(1);
		table[k4].SetLayer(0);
		world w(table,lpart);
		int m_fluid=1;
		int m_air=0;
		int m_boundary_fluid=2;
		int m_boundary_air=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		type_getcelltype m_GetCellType(w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_pres_func m_pres_func=[](Physvector<2,int> key){return 0;};
		UpdateCellTypeAndLayer3<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
		Up.Update();
		
		keyvect k;
		k.Set(1,0);
		k.Set(2,0);
		int c;
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsBoundaryAir(c));

		k.Set(1,1);
		k.Set(2,1);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));

		k.Set(1,0);
		k.Set(2,2);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));
		k.Set(1,1);
		k.Set(2,0);
		TS_ASSERT(m_GetCellType.GetIsFluid(k));
		}

		void test2dUpdate3(){
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<double(Physvector<2,int>)> type_pres_func;
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(1,1);
		k1.Set(2,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		keyvect k2;
		k2.Set(1,0);
		k2.Set(2,1);
		table[k2].SetCellType(1);
		table[k2].SetLayer(0);
		
		keyvect k3;
		k3.Set(1,-1);
		k3.Set(2,0);
		table[k3].SetCellType(1);
		table[k3].SetLayer(0);
		
		keyvect k4;
		k4.Set(1,0);
		k4.Set(2,-1);
		table[k4].SetCellType(1);
		table[k4].SetLayer(0);
		
		keyvect k5;
		k5.Set(1,0);
		k5.Set(2,-9);
		table[k5].SetCellType(1);
		table[k5].SetLayer(0);

		keyvect k6;
		k6.Set(1,0);
		k6.Set(2,-11);
		table[k6].SetCellType(1);
		table[k6].SetLayer(0);

		keyvect k7;
		k7.Set(1,1);
		k7.Set(2,-10);
		table[k7].SetCellType(1);
		table[k7].SetLayer(0);

		keyvect k8;
		k8.Set(1,-1);
		k8.Set(2,-10);
		table[k8].SetCellType(1);
		table[k8].SetLayer(0);

		world w(table,lpart);
		int m_fluid=1;
		int m_air=0;
		int m_boundary_fluid=2;
		int m_boundary_air=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		type_getcelltype m_GetCellType(w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_pres_func m_pres_func=[](Physvector<2,int> key){return 0;};
		UpdateCellTypeAndLayer3<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
		Up.Update();


		keyvect k;
		k.Set(1,0);
		k.Set(2,0);
		int c;
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsBoundaryAir(c));

		k.Set(1,1);
		k.Set(2,1);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));

		k.Set(1,0);
		k.Set(2,2);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));


		k.Set(1,0);
		k.Set(2,-10);
		
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsBoundaryAir(c));

		k.Set(1,1);
		k.Set(2,-9);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));

		k.Set(1,0);
		k.Set(2,-8);
		w.m_mac_grid[k].GetCellType(c);
		TS_ASSERT(m_GetCellType.GetIsAirOnly(c));
		k.Set(1,1);
		k.Set(2,0);
		TS_ASSERT(m_GetCellType.GetIsFluid(k));
		}
};
