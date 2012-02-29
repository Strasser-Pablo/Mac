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
	void test1dUpdate(){
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		typedef std::function<double(Physvector<1,int>)> type_pres_func;
		list_part lpart;
		order O;
		keytable table(O);
		keyvect k1;
		k1.Set(1,0);
		table[k1].SetCellType(1);
		table[k1].SetLayer(0);
		keyvect k2;
		k2.Set(1,4);
		table[k2].SetCellType(1);
		table[k2].SetLayer(0);
		
		keyvect k3;
		k2.Set(1,8);
		table[k2].SetCellType(1);
		table[k2].SetLayer(0);
		world w(table,lpart);
		int m_fluid=1;
		int m_air=0;
		int m_boundary_fluid=2;
		int m_boundary_air=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		type_getcelltype m_GetCellType(m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air);
		type_pres_func m_pres_func=[](Physvector<1,int> key){return 0;};
		UpdateCellTypeAndLayer3<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
		Up.Update();
		int type;
		k1.Set(1,-1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"-1 "<<type<<endl;
		k1.Set(1,0);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"0 "<<type<<endl;
		k1.Set(1,1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"1 "<<type<<endl;
		
		k1.Set(1,2);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"2 "<<type<<endl;
		
		k1.Set(1,3);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"3 "<<type<<endl;
		
		k1.Set(1,4);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"4 "<<type<<endl;
		
		k1.Set(1,5);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"5 "<<type<<endl;
		
		k1.Set(1,6);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"6 "<<type<<endl;
		
		k1.Set(1,7);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"7 "<<type<<endl;
		
		k1.Set(1,8);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"8 "<<type<<endl;
		
		k1.Set(1,9);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"9 "<<type<<endl;
		}
		
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
		k3.Set(1,0);
		k3.Set(2,-1);
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
		type_getcelltype m_GetCellType(m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air);
		type_pres_func m_pres_func=[](Physvector<2,int> key){return 0;};
		UpdateCellTypeAndLayer3<world,type_getcelltype,type_pres_func> Up(w,m_GetCellType,2,m_pres_func);
		Up.Update();
		int type;
		k1.Set(1,0);
		k1.Set(2,0);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"0 0   "<<type<<endl;
		k1.Set(1,1);
		k1.Set(2,0);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"1 0   "<<type<<endl;
		k1.Set(1,0);
		k1.Set(2,1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"0 1   "<<type<<endl;
		
		k1.Set(1,1);
		k1.Set(2,1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"1 1   "<<type<<endl;
		
		
		k1.Set(1,-1);
		k1.Set(2,0);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"-1 0   "<<type<<endl;
		k1.Set(1,0);
		k1.Set(2,-1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"0 -1   "<<type<<endl;
		
		k1.Set(1,-1);
		k1.Set(2,-1);
		w.m_mac_grid[k1].GetLayer(type);
		cout<<"-1 -1   "<<type<<endl;
		}
};