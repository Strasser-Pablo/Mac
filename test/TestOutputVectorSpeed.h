#include <cxxtest/TestSuite.h>
#include "../src/MacWorld.h"
#include "../src/MacCell.h"
#include "../src/Physvector.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/Particle.h"
#include "../src/OutputVectorSpeed.h"
#include "../src/MacGetStagPos.h"
#include <sstream>
#include <string>
#include <iostream>
#define eps 1e-10
class Test_OutputVectorSpeed : public CxxTest::TestSuite
{
	public:
	void testOutput1d()
	{
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
		Physvector<1,int> k0;
		Physvector<1,int> k1;
		k0.Set(1,-1);
		k1.Set(1,1);
		Physvector<1,double> h;
		h.Set(1,1);
		MacGetStagPos<world> stag(h);
		OutputVectorSpeed<world,MacGetStagPos<world> > out(W,stag,h,1);
		stringstream S;
		out.Output(S,1);
		stringstream S2;
		out.OutputPressure(S2);
		//cout<<S2.str();
	}
	
	
	void testOutput1dPart()
	{
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
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		mac c4(temp,0,0,1);
		mac c5(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<1,int> vkey;
		vkey.Set(1,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		vkey.Set(1,-2);
		k[vkey]=c4;
		vkey.Set(1,2);
		k[vkey]=c5;
		list_part lp;
		world W(k,lp);
		Physvector<1,int> k0;
		Physvector<1,int> k1;
		k0.Set(1,-1);
		k1.Set(1,1);
		Physvector<1,double> h;
		h.Set(1,1.0);
		MacGetStagPos<world> stag(h);
		OutputVectorSpeed<world,MacGetStagPos<world> > out(W,stag,h,1);
		stringstream S;
		out.Output(S,1);
		//cout<<S.str();
	}
		void testOutput2d()
	{
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
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		mac c2(temp,1,0,1);
		mac c3(temp,2,0,1);
		mac c4(temp,1,1,0);
		mac c5(temp,2,0,1);
		mac c6(temp,0,0,1);
		order o;
		keytable k(o);
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
		vkey.Set(1,1);
		k[vkey]=c5;
		vkey.Set(1,-1);
		k[vkey]=c6;
		list_part lp;
		world W(k,lp);
		Physvector<2,int> k0;
		Physvector<2,int> k1;
		k0.Set(1,-1);
		k0.Set(2,0);
		k1.Set(1,1);
		k1.Set(2,0);
		Physvector<2,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		MacGetStagPos<world> stag(h);
		OutputVectorSpeed<world,MacGetStagPos<world>  > out(W,stag,h,1);
		stringstream S;
		out.Output(S,1);
		stringstream S2;
		out.OutputPressure(S2);
		//cout<<S2.str();
		//cout<<S.str();
	}
	
	void testOutput2dvar()
	{
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
		temp.Set(2,3.0);
		mac c1(temp,0,1,0);
		mac c2(temp,0,0,1);
		mac c3(temp,0,0,1);
		mac c4(temp,0,1,0);
		mac c5(temp,0,0,1);
		mac c6(temp,0,0,1);
		mac c7(temp,0,1,0);
		mac c8(temp,0,0,1);
		mac c9(temp,0,0,1);
		order o;
		keytable k(o);
		Physvector<2,int> vkey;
		vkey.Set(1,0);
		vkey.Set(2,0);
		k[vkey]=c1;
		vkey.Set(1,1);
		k[vkey]=c2;
		vkey.Set(1,-1);
		k[vkey]=c3;
		vkey.Set(1,0);
		vkey.Set(2,-1);
		k[vkey]=c4;
		vkey.Set(1,1);
		k[vkey]=c5;
		vkey.Set(1,-1);
		k[vkey]=c6;
		vkey.Set(1,0);
		vkey.Set(2,1);
		k[vkey]=c7;
		vkey.Set(1,1);
		k[vkey]=c8;
		vkey.Set(1,-1);
		k[vkey]=c9;
		list_part lp;
		world W(k,lp);
		Physvector<2,int> k0;
		Physvector<2,int> k1;
		k0.Set(1,-1);
		k0.Set(2,-1);
		k1.Set(1,1);
		k1.Set(2,1);
		Physvector<2,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		MacGetStagPos<world> stag(h);
		OutputVectorSpeed<world,MacGetStagPos<world>  > out(W,stag,h,1);
		stringstream S;
		out.Output(S,1);
		stringstream S2;
		out.OutputPressure(S2);
		//cout<<S2.str();
	}
	
		void testOutput3dvar()
	{
		typedef Physvector<3,int> keyvect;
		typedef Physvector<3,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<3,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<3,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;
		Physvector<3,double> temp;
		temp.Set(1,2.0);
		temp.Set(2,3.0);
		temp.Set(3,5.0);
		
		order o;
		keytable k(o);
		Physvector<3,int> vkey;
		for(int i=-1;i<10;++i)
		{
			for(int j=-1;j<10;++j)
			{
				for(int l=-1;l<10;++l)
				{
			vkey.Set(1,i);
			vkey.Set(2,j);
			vkey.Set(3,l);
			mac c(temp,i+j+l,1,0);
			k[vkey]=c;
				}
			}
		}
		
		list_part lp;
		world W(k,lp);
		Physvector<3,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		h.Set(3,1.0);
		MacGetStagPos<world> stag(h);
		OutputVectorSpeed<world,MacGetStagPos<world>  > out(W,stag,h,1);
		stringstream S;
		out.Output(S,1);
		stringstream S2;
		out.OutputPressure(S2);
		//cout<<S2.str();
	}
};
