#include <cxxtest/TestSuite.h>
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/GetCellType_Fluid.h"
#include "../src/GetCellType_Base.h"
#define eps 1e-10
class Test_GetCellType_Fluid : public CxxTest::TestSuite
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
	}
};
