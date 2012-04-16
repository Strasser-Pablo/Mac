
#include <cxxtest/TestSuite.h>
#define eps 1e-10
const int dim=2;
#include "Utility_Test_Jet_D_Eau.h"
#define INTERPOLATION_NO_PROTECTION
using namespace std;

class Test_JetDEau_1 :public JetDEau_Test
{

	void Calculate()
	{
		JetDEau_Test::Calculate();
	}

	void SetUp()
	{
		m_t=0; 
		m_viscosity_const=0;
		Physvector<dim,double> speed;
		speed.SetAll(0);
		double prop=1;
		m_v_1_h.SetAll(1);
		m_v_h.SetAll(1);
		int Nx=2;
		Physvector<dim,int> key;
		
		for(int i=-Nx;i<=Nx;++i)
		{
			speed.Set(2,prop*i);
		key.Set(1,i);
		key.Set(2,0);
		mac m(speed,0,0,0);
		m.SetConstSpeed(2,true);
		m_w.m_mac_grid[key]=m;
		}
		m_init.PrepareConstSpeed();
		m_g.Set(1,0);
		m_g.Set(2,-9.81);
		m_dt=0;
		m_t=0;
	}
	friend class Test_Symmetry;  
};

class Test_JetDEau_2 :public JetDEau_Test
{

	void Calculate()
	{
		JetDEau_Test::Calculate();
	}

	void SetUp()
	{
		m_t=0; 
		m_viscosity_const=0;
		Physvector<dim,double> speed;
		speed.SetAll(0);
		double prop=-1;
		m_v_1_h.SetAll(1);
		m_v_h.SetAll(1);
		int Nx=2;
		Physvector<dim,int> key;
		
		for(int i=-Nx;i<=Nx;++i)
		{
			speed.Set(2,prop*i);
		key.Set(1,i);
		key.Set(2,0);
		mac m(speed,0,0,0);
		m.SetConstSpeed(2,true);
		m_w.m_mac_grid[key]=m;
		}
		m_init.PrepareConstSpeed();
		m_g.Set(1,0);
		m_g.Set(2,-9.81);
		m_dt=0;
		m_t=0;
	}
	friend class Test_Symmetry;  
};

class Test_Symmetry : public CxxTest::TestSuite
{
	public:
	void xtesta()
	{
 		Test_JetDEau_1 j1;
		Test_JetDEau_2 j2;
		j1.SetUp();
		j2.SetUp();
		for (auto it1=j1.m_w.m_mac_grid.begin();it1!=j1.m_w.m_mac_grid.end();++it1)
		{
			Physvector<2,double> speed1;
			double p1;
			it1.data().GetSpeed(speed1);
			it1.data().GetPressure(p1);
			Physvector<2,double> speed2;
			double p2;
			Physvector<2,int> key=it1.key();
			key.GetRef(1)=(-1)*key.Get(1);
			j2.m_w.m_mac_grid[key].GetSpeed(speed2);
			j2.m_w.m_mac_grid[key].GetPressure(p2);
			TS_ASSERT_DELTA(speed1.Get(1),speed2.Get(1),eps);
			TS_ASSERT_DELTA(speed1.Get(2),speed2.Get(2),eps);
			TS_ASSERT_DELTA(p1,p2,eps);
		}
		for(int i=0;i<=10;++i)
		{
		cout<<"1 "<<endl;
		j1.Calculate();
		cout<<"2 "<<endl;
		j2.Calculate();
		for (auto it1=j1.m_w.m_mac_grid.begin();it1!=j1.m_w.m_mac_grid.end();++it1)
		{
			Physvector<2,double> speed1;
			double p1;
			it1.data().GetSpeed(speed1);
			it1.data().GetPressure(p1);
			Physvector<2,double> speed2;
			double p2;
			Physvector<2,int> key=it1.key();
			key.GetRef(1)=(-1)*key.Get(1);
			j2.m_w.m_mac_grid[key].GetSpeed(speed2);
			j2.m_w.m_mac_grid[key].GetPressure(p2);
			TS_ASSERT_DELTA(speed1.Get(1),speed2.Get(1),eps);
			TS_ASSERT_DELTA(speed1.Get(2),speed2.Get(2),eps);
			TS_ASSERT_DELTA(p1,p2,eps);
		}
		}
	}	
};
