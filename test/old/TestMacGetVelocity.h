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
#include "../src/MacGetStagPos.h"
#define eps 1e-10
class Test_MacGetVelocity : public CxxTest::TestSuite
{
	public:
	void test1dconst(){
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0);
		mac c2(temp,0);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		list_part lp;
		world W(k,lp);
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		MacGetStagPos<world> stag(vh);
		MacGetVelocity<world,MacGetStagPos<world> > Nlin(W,stag,vh);
		Physvector<1,double> pos;
		pos.Set(1,0.5);
		Physvector<1,double> res;
		res=Nlin.Get(pos);
		
		TS_ASSERT_DELTA(res.Get(1),2.0,eps);
	}
	void test1d(){
		typedef Physvector<1,int> keyvect;
		typedef Physvector<1,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<1,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<1,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<1,double> temp;
		temp.Set(1,2.0);
		mac c1(temp,0);
		temp.Set(1,4.0);
		mac c2(temp,0);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		list_part lp;
		world W(k,lp);
		Physvector<1,double> vh;
		vh.Set(1,1.0);
		MacGetStagPos<world> stag(vh);
		MacGetVelocity<world,MacGetStagPos<world> > Nlin(W,stag,vh);
		Physvector<1,double> pos;
		pos.Set(1,0);
		Physvector<1,double> res;
		res=Nlin.Get(pos);
		TS_ASSERT_DELTA(res.Get(1),3.0,eps);
	}
	void test2dconst(){
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,2.0);
		mac c1(temp,0);
		mac c2(temp,0);
		mac c3(temp,0);
		mac c4(temp,0);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		vkey.Set(2,0);
		k[vkey]=c2;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c3;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c4;
		list_part lp;
		world W(k,lp);
		Physvector<2,double> vh;
		vh.Set(1,1.0);
		vh.Set(2,1.0);
		MacGetStagPos<world> stag(vh);
		MacGetVelocity<world,MacGetStagPos<world> > Nlin(W,stag,vh);
		Physvector<2,double> pos;
		pos.Set(1,0.5);
		pos.Set(2,0.5);
		Physvector<2,double> res;
		res=Nlin.Get(pos);
		TS_ASSERT_DELTA(res.Get(1),2.0,eps);
		TS_ASSERT_DELTA(res.Get(2),2.0,eps);
	}
	void test2d(){
		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<2,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,2.0);
		mac c1(temp,0);
		temp.Set(1,3.0);
		temp.Set(2,3.0);
		mac c2(temp,0);
		temp.Set(1,1.0);
		temp.Set(2,1.0);
		mac c3(temp,0);
		temp.Set(1,4.0);
		temp.Set(2,4.0);
		mac c4(temp,0);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		vkey.Set(2,0);
		k[vkey]=c2;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c3;
		vkey.Set(1,1);
		vkey.Set(2,1);
		k[vkey]=c4;
		list_part lp;
		world W(k,lp);
		Physvector<2,double> vh;
		vh.Set(1,1.0);
		vh.Set(2,1.0);
		MacGetStagPos<world> stag(vh);
		MacGetVelocity<world,MacGetStagPos<world> > Nlin(W,stag,vh);
		Physvector<2,double> pos;
		pos.Set(1,0);
		pos.Set(2,0);
		Physvector<2,double> res;
		res=Nlin.Get(pos);
		TS_ASSERT_DELTA(res.Get(1),2.5,eps);
		TS_ASSERT_DELTA(res.Get(2),1.5,eps);
	}
};