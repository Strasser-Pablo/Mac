#include <cxxtest/TestSuite.h>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
//#include <boost/archive/nvp.hpp>
#include <fstream>
#include "../src/Physvector.h"
#include "../src/Particle.h"
#include "../src/TableContainerList.h"
#include "../src/MacCell.h"
#include "../src/KeyTableMap.h"
#include "../src/MacWorld.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/JetDEau.h"
#define eps 1e-10
using namespace std;
class Test_Serialization : public CxxTest::TestSuite
{
	
	
public:
	void testBasic()
	{
		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			int a=3;
			oa<<boost::serialization::make_nvp("test_1",a);
		}
		{
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			int i;
			ia>>boost::serialization::make_nvp("test_1",i);
			TS_ASSERT_EQUALS(i,3);
		}
	}

	void testPhysvector()
	{
		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			Physvector<2,double> vect;
			vect.Set(1,2.3);
			vect.Set(2,4.6);
			oa<<boost::serialization::make_nvp("vect",vect);
			
			Physvector<2,int> vect2;
			vect2.Set(1,5);
			vect2.Set(2,8);
			oa<<boost::serialization::make_nvp("vect2",vect2);
		}
		{
			Physvector<2,double> v;
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			ia>>boost::serialization::make_nvp("vect",v);
			TS_ASSERT_DELTA(v.Get(1),2.3,eps);
			TS_ASSERT_DELTA(v.Get(2),4.6,eps);
			Physvector<2,double> v2;
			ia>>boost::serialization::make_nvp("vect2",v2);
			TS_ASSERT_DELTA(v2.Get(1),5,eps);
			TS_ASSERT_DELTA(v2.Get(2),8,eps);
		}
	}
	void testParticle()
	{

		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			Physvector<2,double> vect;
			vect.Set(1,2.3);
			vect.Set(2,4.6);
			Particle<Physvector<2,double> > Part(vect);
			oa<<boost::serialization::make_nvp("Particle",Part);
		}
		{
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			Particle<Physvector<2,double> > P;
			ia>>boost::serialization::make_nvp("Particle",P);
			Physvector<2,double> v;
			P.GetPos(v);
			TS_ASSERT_DELTA(v.Get(1),2.3,eps);
			TS_ASSERT_DELTA(v.Get(2),4.6,eps);
		}
	}

	void testTableContainerList()
	{
		typedef Physvector<2,double> type_vector;
		typedef Particle<type_vector> type_particle;
		typedef TableContainerList<type_particle> type_list;

		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			type_list l;
			Physvector<2,double> vect;
			vect.Set(1,2.3);
			vect.Set(2,4.6);
			Particle<Physvector<2,double> > Part(vect);
			l.push_back(Part);
			vect.Set(1,5.3);
			vect.Set(2,9.6);
			Particle<Physvector<2,double> > Part2(vect);
			l.push_back(Part2);
			oa<<boost::serialization::make_nvp("List",l);
		}
		{
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			type_list l;
			ia>>boost::serialization::make_nvp("List",l);
			type_particle P1=l.back();
			l.pop_back();
			type_particle P2=l.back();
			type_vector v1;
			P1.GetPos(v1);
			type_vector v2;
			P2.GetPos(v2);
			TS_ASSERT_DELTA(v2.Get(1),2.3,eps);
			TS_ASSERT_DELTA(v2.Get(2),4.6,eps);
			TS_ASSERT_DELTA(v1.Get(1),5.3,eps);
			TS_ASSERT_DELTA(v1.Get(2),9.6,eps);
		}
	}

	void testMacCell()
	{
		typedef MacCell<2,double,int> type_mac;
		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			type_mac Mac;
			Physvector<2,double> vect;
			vect.Set(1,2.3);
			vect.Set(2,4.6);
			Mac.SetSpeed(vect);
			Mac.SetCellType(4);
			Mac.SetLayer(3);
			oa<<boost::serialization::make_nvp("MacCell",Mac);
		}
		{
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			type_mac M;
			ia>>boost::serialization::make_nvp("MacCell",M);
			int c;
			int l;
			Physvector<2,double> v;
			M.GetCellType(c);
			M.GetSpeed(v);
			M.GetLayer(l);
			TS_ASSERT_DELTA(v.Get(1),2.3,eps);
			TS_ASSERT_DELTA(v.Get(2),4.6,eps);
			TS_ASSERT_EQUALS(c,4);
			TS_ASSERT_EQUALS(l,3);
		}
	}

	void testmap()
	{
		typedef KeyTableMap<int,int> type_map;
		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			type_map Map;
			Map[2]=6;
			Map[1]=9;
			Map[19]=2;
			oa<<boost::serialization::make_nvp("KeyTable",Map);
		}
		{
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			type_map M;
			ia>>boost::serialization::make_nvp("MacCell",M);
			TS_ASSERT_EQUALS(M[1],9);
			TS_ASSERT_EQUALS(M[2],6);
			TS_ASSERT_EQUALS(M[19],2);
		}	
	}
	void testMacWorld()
	{

		typedef Physvector<2,int> keyvect;
		typedef Physvector<2,double> vect;
		typedef Particle<vect> part;
		typedef MacCell<2,double,int> mac;
		typedef TableContainerList<part> list_part;
		typedef PhysvectorKeyOrder<2,int> order;
		typedef KeyTableMap<keyvect,mac,order> keytable;
		typedef MacWorld<keytable,list_part> world;

		{
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			order o;
			keytable k(o);
			vect speed;
			speed.Set(1,1);
			speed.Set(2,3);
			mac m(speed,2.3,1,3);
			speed.Set(1,4);
			speed.Set(2,7);
			mac m2(speed,5,2,5);
			keyvect key;
			key.Set(1,4);
			key.Set(2,8);
			k[key]=m;
			key.Set(1,8);
			key.Set(2,2);
			k[key]=m2;
			list_part lp;
			vect pos;
			pos.Set(1,5);
			pos.Set(2,8);
			lp.push_back(part(pos));
			world w(k,lp);
			oa <<boost::serialization::make_nvp("World",w);
		}
		{

			order o;
			keytable k(o);
			list_part lp;
			world W(k,lp);
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			ia>>boost::serialization::make_nvp("World",W);
			keyvect key;
			key.Set(1,4);
			key.Set(2,8);
			double p;
			W.m_mac_grid[key].GetPressure(p);
			TS_ASSERT_DELTA(p,2.3,eps);
			vect speed;
			W.m_mac_grid[key].GetSpeed(speed);
			TS_ASSERT_DELTA(speed.Get(1),1,eps);
			TS_ASSERT_DELTA(speed.Get(2),3,eps);
			int layer;
			W.m_mac_grid[key].GetLayer(layer);
			TS_ASSERT_EQUALS(layer,3);
			int type;
			W.m_mac_grid[key].GetCellType(type);
			TS_ASSERT_EQUALS(type,1);
			key.Set(1,8);
			key.Set(2,2);
			W.m_mac_grid[key].GetPressure(p);
			TS_ASSERT_DELTA(p,5,eps);
			W.m_mac_grid[key].GetSpeed(speed);
			TS_ASSERT_DELTA(speed.Get(1),4,eps);
			TS_ASSERT_DELTA(speed.Get(2),7,eps);
			W.m_mac_grid[key].GetLayer(layer);
			TS_ASSERT_EQUALS(layer,5);
			W.m_mac_grid[key].GetCellType(type);
			TS_ASSERT_EQUALS(type,2);
			list_part::iterator it=W.m_particle_list.begin();
			vect pos;
			(*it).GetPos(pos);
			TS_ASSERT_DELTA(pos.Get(1),5,eps);
			TS_ASSERT_DELTA(pos.Get(2),8,eps);
		}
	}
	void testJetDEau()
	{
		{		
			JetDEau j;
			j.SetUp();
			std::ofstream ofs("test.txt");
			boost::archive::xml_oarchive oa(ofs);
			oa<<boost::serialization::make_nvp("JetDEau",j);
		}
		{
			JetDEau J;
			std::ifstream ifs("test.txt");
			boost::archive::xml_iarchive ia(ifs);
			ia>>boost::serialization::make_nvp("JetDEau",J);
		}
	}

};
