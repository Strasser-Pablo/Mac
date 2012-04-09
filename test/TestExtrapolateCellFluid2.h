#include <cxxtest/TestSuite.h>
#include "../src/MacGetVelocity.h"
#include "../src/MacInitializeCell.h"
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/ExtrapolateCellFluid2.h"
#include "../src/GetCellType.h"
#include "../src/KeyTableUnorderedMap.h"
#include "../src/HashPhysvector.h"
#define eps 1e-10
class Test_Extrapolate2 : public CxxTest::TestSuite
{
	public:
	void test1d()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef HashPhysvector<1,int> Hash;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		Hash hash;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		keytable k(hash);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,2);
		k[vkey]=c4;
		vkey.Set(1,-1);
		k[vkey]=c3;		
		list_part lp;
		world W(k,lp);
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
		type_getcelltype m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		ExtrapolateCellFluid2<world,type_getcelltype>  Ex(W,m_GetCellType,1);
		Ex.Calculate();
		vkey.Set(1,0);
		int lay;
		Physvector<1,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);

		vkey.Set(1,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
	}
	
	void test1dvar()
	{
		typedef Physvector<1,int> keyvect;
		typedef HashPhysvector<1,int> Hash;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		Hash hash;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		Physvector<1,double> temp2;
		temp2.Set(1,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		keytable k(hash);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
		world W(k,lp);
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
		type_getcelltype m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		ExtrapolateCellFluid2<world,type_getcelltype>  Ex(W,m_GetCellType,1);
		Ex.Calculate();
		vkey.Set(1,0);
		int lay;
		Physvector<1,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,eps);
	}
	
	void test2d()
	{
		typedef Physvector<2,int> keyvect;
		typedef HashPhysvector<2,int> Hash;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		Hash hash;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		mac c5(temp2,0,0,-1);
		keytable k(hash);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(2,-1);
		k[vkey]=c5;
		list_part lp;
		world W(k,lp);
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
		type_getcelltype m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		ExtrapolateCellFluid2<world,type_getcelltype>  Ex(W,m_GetCellType,1);
		Ex.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		int lay;
		Physvector<2,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.25,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.25,eps);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
	}
	
		void test2dvar()
	{
		typedef Physvector<2,int> keyvect;
		typedef HashPhysvector<2,int> Hash;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		Hash hash;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		mac c5(temp2,0,0,-1);
		keytable k(hash);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(2,-1);
		k[vkey]=c5;
		list_part lp;
		world W(k,lp);
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
		type_getcelltype m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		ExtrapolateCellFluid2<world,type_getcelltype>  Ex(W,m_GetCellType,1);
		Ex.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		int lay;
		Physvector<2,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.25,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.25,eps);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,eps);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,eps);
	}

		void test2dvar2()
	{
		typedef Physvector<2,int> keyvect;
		typedef HashPhysvector<2,int> Hash;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType<world> type_getcelltype;
		Hash hash;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		Physvector<2,double> temp2;
		temp2.Set(1,0.0);
		temp2.Set(2,0.0);
		mac c2(temp2,0,0,-1);
		mac c3(temp2,0,0,-1);
		mac c4(temp2,0,0,-1);
		mac c5(temp2,0,0,-1);
		mac c6(temp2,0,0,-1);
		mac c7(temp2,0,0,-1);
		mac c8(temp2,0,0,-1);
		mac c9(temp2,0,0,-1);
		mac c10(temp2,0,0,-1);
		mac c11(temp2,0,0,-1);
		mac c12(temp2,0,0,-1);
		mac c13(temp2,0,0,-1);
		mac c14(temp2,0,0,-1);
		mac c15(temp2,0,0,-1);
		mac c16(temp2,0,0,-1);
		mac c17(temp2,0,0,-1);
		mac c18(temp2,0,0,-1);
		mac c19(temp2,0,0,-1);
		mac c20(temp2,0,0,-1);
		mac c21(temp2,0,0,-1);
		mac c22(temp2,0,0,-1);
		mac c23(temp2,0,0,-1);
		mac c24(temp2,0,0,-1);
		mac c25(temp2,0,0,-1);

		keytable k(hash);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c4;
		vkey.Set(2,-1);
		k[vkey]=c5;

		vkey.Set(1,-1);
		vkey.Set(2,1);
		k[vkey]=c6;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c7;
		vkey.Set(1,-1);
		vkey.Set(2,-1);
		k[vkey]=c8;
		vkey.Set(1,1);
		vkey.Set(2,-1);
		k[vkey]=c9;
		vkey.Set(1,-1);
		vkey.Set(2,2);
		k[vkey]=c10;
		vkey.Set(1,0);
		vkey.Set(2,2);
		k[vkey]=c11;
		vkey.Set(1,1);
		vkey.Set(2,2);
		k[vkey]=c12;
		vkey.Set(1,2);
		vkey.Set(2,2);
		k[vkey]=c13;
		vkey.Set(1,2);
		vkey.Set(2,1);
		k[vkey]=c14;
		vkey.Set(1,2);
		vkey.Set(2,0);
		k[vkey]=c15;
		vkey.Set(1,2);
		vkey.Set(2,-1);
		k[vkey]=c16;
		vkey.Set(1,2);
		vkey.Set(2,-2);
		k[vkey]=c17;
		vkey.Set(1,1);
		vkey.Set(2,-2);
		k[vkey]=c18;
		vkey.Set(1,0);
		vkey.Set(2,-2);
		k[vkey]=c19;
		vkey.Set(1,-1);
		vkey.Set(2,-2);
		k[vkey]=c20;
		vkey.Set(1,-2);
		vkey.Set(2,-2);
		k[vkey]=c21;
		vkey.Set(1,-2);
		vkey.Set(2,-1);
		k[vkey]=c22;
		vkey.Set(1,-2);
		vkey.Set(2,0);
		k[vkey]=c23;
		vkey.Set(1,-2);
		vkey.Set(2,1);
		k[vkey]=c24;
		vkey.Set(1,-2);
		vkey.Set(2,2);
		k[vkey]=c25;

		list_part lp;
		world W(k,lp);
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
		type_getcelltype m_GetCellType(W,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		ExtrapolateCellFluid2<world,type_getcelltype>  Ex(W,m_GetCellType,1);
		Ex.Calculate();
		vkey.Set(1,0);
		vkey.Set(2,0);
		int lay;
		Physvector<2,double> tempspeed;
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,0);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.75,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.75,0.001);
		vkey.Set(1,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.25,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6666,0.001);
		vkey.Set(1,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.6666,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6666,0.001);
		
		vkey.Set(1,0);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.25,0.001);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,1);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.83333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.83333,0.001);

		vkey.Set(1,1);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.9166,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.5833,0.001);
		
		
		vkey.Set(1,-1);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.5833,0.001);

		vkey.Set(1,1);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.9166,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6666,0.001);

		vkey.Set(1,-1);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6666,0.001);

		vkey.Set(1,2);
		vkey.Set(2,-2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,4);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8611,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6666,0.001);

		vkey.Set(1,2);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.9166,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.666,0.001);
		
		vkey.Set(1,2);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.666,0.001);

		vkey.Set(1,2);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.125,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.625,0.001);

		vkey.Set(1,2);
		vkey.Set(2,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,4);
		TS_ASSERT_DELTA(tempspeed.Get(1),1.0,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.5,0.001);

		vkey.Set(1,-2);
		vkey.Set(2,-2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,4);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8402,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6597,0.001);

		vkey.Set(1,-2);
		vkey.Set(2,-1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6527,0.001);
		
		vkey.Set(1,-2);
		vkey.Set(2,0);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.6527,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6527,0.001);

		vkey.Set(1,-2);
		vkey.Set(2,1);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6388,0.001);

		vkey.Set(1,-2);
		vkey.Set(2,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,4);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.6388,0.001);

		vkey.Set(1,-1);
		vkey.Set(2,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.5833,0.001);
		
		vkey.Set(1,0);
		vkey.Set(2,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8333,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.166,0.001);

		vkey.Set(1,1);
		vkey.Set(2,2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8750,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.3750,0.001);

		vkey.Set(1,-1);
		vkey.Set(2,-2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8472,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.666,0.001);
		
		vkey.Set(1,0);
		vkey.Set(2,-2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,2);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8472,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.8472,0.001);

		vkey.Set(1,1);
		vkey.Set(2,-2);
		W.m_mac_grid[vkey].GetLayer(lay);
		W.m_mac_grid[vkey].GetSpeed(tempspeed);
		TS_ASSERT_EQUALS(lay,3);
		TS_ASSERT_DELTA(tempspeed.Get(1),0.8611,0.001);
		TS_ASSERT_DELTA(tempspeed.Get(2),1.666,0.001);
	}

}
;
