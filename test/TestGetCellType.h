#include <cxxtest/TestSuite.h>
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/GetCellType_Fluid.h"
#include "../src/GetCellType_Air.h"
#include "../src/GetCellType_Base.h"
#include "../src/GetCellType_Rho.h"
#include "../src/GetCellType_Fluid_Air_Interface.h"
#include "../src/GetCellType_Pressure_In_Domaine_Fluid_Only.h"
#include "../src/GetCellType_Pressure_Boundary_Domaine.h"
#include "../src/GetCellType_Pressure_Boundary_Non_Constant.h"
#define eps 1e-10
class Test_GetCellType : public CxxTest::TestSuite
{
	public:
	void testfluid()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		type_base::type_input_struct in_base(W,-1);
		Inversible_Value<double> rho(3.0);
		type_fluid::type_input_struct in(in_base,1,rho);
		type_fluid g_f(in);
		TS_ASSERT(g_f.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_f.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_f.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_f.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_f.GetRhoFluid().Get(),3.0,eps);
	}
	void testair()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Air<world,type_base> type_air;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		type_base::type_input_struct in_base(W,-1);
		Inversible_Value<double> rho(3.0);
		type_air::type_input_struct in(in_base,1,rho);
		type_air g_a(in);
		TS_ASSERT(g_a.GetIsAir(1));
		vkey.Set(1,0);
		TS_ASSERT(g_a.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_a.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_a.GetIsAir(vkey));
		TS_ASSERT_DELTA(g_a.GetRhoAir().Get(),3.0,eps);
	}
	void testfluid_air()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		typedef GetCellType_Air<world,type_fluid> type_comp;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		Inversible_Value<double> rho_air(3.0);
		Inversible_Value<double> rho_fluid(4.0);
		type_base::type_input_struct in_base(W,-1);
		type_fluid::type_input_struct in_fluid(in_base,1,rho_fluid);
		type_comp::type_input_struct in(in_fluid,0,rho_air);
		type_comp g_c(in);
		TS_ASSERT(g_c.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_c.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_c.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_c.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_c.GetRhoFluid().Get(),4.0,eps);
		TS_ASSERT(g_c.GetIsAir(0));
		vkey.Set(1,0);
		TS_ASSERT(!g_c.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(g_c.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_c.GetIsAir(vkey));
		TS_ASSERT_DELTA(g_c.GetRhoAir().Get(),3.0,eps);
	}

	void testfluid_air_rho()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		typedef GetCellType_Air<world,type_fluid> type_comp;
		typedef GetCellType_Rho<world,type_comp> type_rho;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		Inversible_Value<double> rho_air(3.0);
		Inversible_Value<double> rho_fluid(4.0);
		type_base::type_input_struct in_base(W,-1);
		type_fluid::type_input_struct in_fluid(in_base,1,rho_fluid);
		type_comp::type_input_struct in(in_fluid,0,rho_air);
		type_rho g_r(in);
		TS_ASSERT(g_r.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_r.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_r.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_r.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_r.GetRhoFluid().Get(),4.0,eps);
		TS_ASSERT(g_r.GetIsAir(0));
		vkey.Set(1,0);
		TS_ASSERT(!g_r.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(g_r.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_r.GetIsAir(vkey));
		TS_ASSERT_DELTA(g_r.GetRhoAir().Get(),3.0,eps);

		TS_ASSERT_DELTA(g_r.GetRho(1).Get(),4.0,eps);
		TS_ASSERT_DELTA(g_r.GetRho(0).Get(),3.0,eps);
		vkey.Set(1,0);
		TS_ASSERT_DELTA(g_r.GetRho(vkey).Get(),4.0,eps);
		vkey.Set(1,1);
		TS_ASSERT_DELTA(g_r.GetRho(vkey).Get(),3.0,eps);
		TS_ASSERT_THROWS(g_r.GetRho(3),runtime_error);
		vkey.Set(1,10);
		TS_ASSERT_THROWS(g_r.GetRho(vkey),runtime_error);
	}
	void testfluid_air_interface()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		typedef GetCellType_Air<world,type_fluid> type_comp;
		typedef GetCellType_Fluid_Air_Interface<world,type_comp> type_int;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		Inversible_Value<double> rho_air(3.0);
		Inversible_Value<double> rho_fluid(4.0);
		type_base::type_input_struct in_base(W,-1);
		type_fluid::type_input_struct in_fluid(in_base,1,rho_fluid);
		type_comp::type_input_struct in(in_fluid,0,rho_air);
		type_int g_i(in);
		TS_ASSERT(g_i.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_i.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_i.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_i.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_i.GetRhoFluid().Get(),4.0,eps);
		TS_ASSERT(g_i.GetIsAir(0));
		vkey.Set(1,0);
		TS_ASSERT(!g_i.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(g_i.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_i.GetIsAir(vkey));

		TS_ASSERT(g_i.GetIsFluidAirInterface(1,0));
		TS_ASSERT(!g_i.GetIsFluidAirInterface(1,-1));
		TS_ASSERT(!g_i.GetIsFluidAirInterface(0,-1));
		TS_ASSERT(!g_i.GetIsFluidAirInterface(0,0));
		TS_ASSERT(!g_i.GetIsFluidAirInterface(1,1));
		vkey.Set(1,0);
		Physvector<1,int> vkey2;
		vkey2.Set(1,1);
		TS_ASSERT(g_i.GetIsFluidAirInterface(vkey,vkey2));
		vkey2.Set(1,3);
		TS_ASSERT(!g_i.GetIsFluidAirInterface(vkey,vkey2));
		TS_ASSERT(g_i.GetIsFluidAirInterface(vkey,1,1));
	}

	void testfluid_air_Pressure_In_Domaine()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		typedef GetCellType_Air<world,type_fluid> type_comp;
		typedef GetCellType_Rho<world,type_comp> type_rho;
		typedef GetCellType_Pressure_In_Domaine_Fluid_Only<world,type_rho> type_pres;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		Inversible_Value<double> rho_air(3.0);
		Inversible_Value<double> rho_fluid(4.0);
		type_base::type_input_struct in_base(W,-1);
		type_fluid::type_input_struct in_fluid(in_base,1,rho_fluid);
		type_comp::type_input_struct in(in_fluid,0,rho_air);
		type_pres g_p(in);
		TS_ASSERT(g_p.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_p.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_p.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_p.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_p.GetRhoFluid().Get(),4.0,eps);
		TS_ASSERT(g_p.GetIsAir(0));
		vkey.Set(1,0);
		TS_ASSERT(!g_p.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(g_p.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_p.GetIsAir(vkey));
		TS_ASSERT_DELTA(g_p.GetRhoAir().Get(),3.0,eps);

		TS_ASSERT_DELTA(g_p.GetRho(1).Get(),4.0,eps);
		TS_ASSERT_DELTA(g_p.GetRho(0).Get(),3.0,eps);
		vkey.Set(1,0);
		TS_ASSERT_DELTA(g_p.GetRho(vkey).Get(),4.0,eps);
		vkey.Set(1,1);
		TS_ASSERT_DELTA(g_p.GetRho(vkey).Get(),3.0,eps);
		TS_ASSERT_THROWS(g_p.GetRho(3),runtime_error);
		vkey.Set(1,10);
		TS_ASSERT_THROWS(g_p.GetRho(vkey),runtime_error);

		TS_ASSERT(g_p.GetIsPressureInDomaine(1));
		TS_ASSERT(!g_p.GetIsPressureInDomaine(0));
		TS_ASSERT(!g_p.GetIsPressureInDomaine(-1));
		vkey.Set(1,0);
		TS_ASSERT(g_p.GetIsPressureInDomaine(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_p.GetIsPressureInDomaine(vkey));
		vkey.Set(1,10);
		TS_ASSERT(!g_p.GetIsPressureInDomaine(vkey));
	}

	void testfluid_air_Boundary_Non_Constant()
	{
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		typedef GetCellType_Base<world> type_base;
		typedef GetCellType_Fluid<world,type_base> type_fluid;
		typedef GetCellType_Air<world,type_fluid> type_comp;
		typedef GetCellType_Rho<world,type_comp> type_rho;
		typedef GetCellType_Pressure_In_Domaine_Fluid_Only<world,type_rho> type_pres;
		typedef GetCellType_Pressure_Boundary_Non_Constant<world,type_pres> type_non_const;
		typedef GetCellType_Pressure_Boundary_Domaine<world,type_non_const> type_bound;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		list_part lp;
 		world W(k,lp);
		Inversible_Value<double> rho_air(3.0);
		Inversible_Value<double> rho_fluid(4.0);
		type_base::type_input_struct in_base(W,-1);
		type_fluid::type_input_struct in_fluid(in_base,1,rho_fluid);
		type_comp::type_input_struct in(in_fluid,0,rho_air);
		type_bound g_b(in);
		TS_ASSERT(g_b.GetIsFluid(1));
		vkey.Set(1,0);
		TS_ASSERT(g_b.GetIsFluid(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_b.GetIsFluid(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_b.GetIsFluid(vkey));
		TS_ASSERT_DELTA(g_b.GetRhoFluid().Get(),4.0,eps);
		TS_ASSERT(g_b.GetIsAir(0));
		vkey.Set(1,0);
		TS_ASSERT(!g_b.GetIsAir(vkey));
		vkey.Set(1,1);
		TS_ASSERT(g_b.GetIsAir(vkey));
		vkey.Set(1,20);
		TS_ASSERT(!g_b.GetIsAir(vkey));
		TS_ASSERT_DELTA(g_b.GetRhoAir().Get(),3.0,eps);

		TS_ASSERT_DELTA(g_b.GetRho(1).Get(),4.0,eps);
		TS_ASSERT_DELTA(g_b.GetRho(0).Get(),3.0,eps);
		vkey.Set(1,0);
		TS_ASSERT_DELTA(g_b.GetRho(vkey).Get(),4.0,eps);
		vkey.Set(1,1);
		TS_ASSERT_DELTA(g_b.GetRho(vkey).Get(),3.0,eps);
		TS_ASSERT_THROWS(g_b.GetRho(3),runtime_error);
		vkey.Set(1,10);
		TS_ASSERT_THROWS(g_b.GetRho(vkey),runtime_error);

		TS_ASSERT(g_b.GetIsPressureInDomaine(1));
		TS_ASSERT(!g_b.GetIsPressureInDomaine(0));
		TS_ASSERT(!g_b.GetIsPressureInDomaine(-1));
		vkey.Set(1,0);
		TS_ASSERT(g_b.GetIsPressureInDomaine(vkey));
		vkey.Set(1,1);
		TS_ASSERT(!g_b.GetIsPressureInDomaine(vkey));
		vkey.Set(1,10);
		TS_ASSERT(!g_b.GetIsPressureInDomaine(vkey));

		vkey.Set(1,0);
		Physvector<1,int> vkey2;
		vkey2.Set(1,1);
		TS_ASSERT(g_b.GetIsPressure_Boundary(vkey,vkey2));

		vkey.Set(1,-1);
		vkey2.Set(1,1);
		TS_ASSERT(!g_b.GetIsPressure_Boundary(vkey,vkey2));

		vkey.Set(1,0);
		vkey2.Set(1,10);
		TS_ASSERT(g_b.GetIsPressure_Boundary(vkey,vkey2));


		TS_ASSERT(g_b.GetIsPressure_Boundary(vkey,-1,1));
		TS_ASSERT(g_b.GetIsPressure_Boundary(vkey,1,1));
	}
};
