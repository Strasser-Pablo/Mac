#include <cxxtest/TestSuite.h>
#define eps 1e-10
const int dim=2;
#include "Utility_Test_Jet_D_Eau.h"
#define INTERPOLATION_NO_PROTECTION
using namespace std;

class JetDEau_Lin :public JetDEau_Test
{

	public:
	double maxer;
	double meaner;
	int Nx;
	int Ny;
	JetDEau_Lin():maxer(0)
	{
	}
	void Calculate()
	{
		JetDEau_Test::Calculate();
	}
	void Test()
	{
		meaner=0;
		int N=0;
		Physvector<dim,int> key;
		for(int i=-Nx;i<Nx;++i)
		{
			for(int j=0;j<=Ny;++j)
			{
				++N;
				key.Set(1,i);
				key.Set(2,j);
				Physvector<2,double> speed;
				m_w.m_mac_grid[key].GetSpeed(speed);
				double temp=0;
				temp+=abs(speed.Get(1)-(Nx*Nx*i-pow(i,3)/3.)*pow(m_v_h.Get(1),3));
				temp+=abs(speed.Get(2)-(pow(Nx,2)-pow(i+0.5,2))*(Ny-j)*pow(m_v_h.Get(1),2)*m_v_h.Get(2));
				meaner+=temp;
				if(temp>maxer)
				{
					maxer=temp;
				}
			}
		}
		meaner/=N;
	}
	void SetUp()
	{
		m_i=0;
		m_out.SetUp();
		m_rho_fluid=1;
		m_rho_air=1;
		m_1_rho_fluid=1;
		m_1_rho_air=1;
		m_rho_inter=1;
		m_1_rho_inter=1;
		m_rho_inter_bound=1;
		m_1_rho_inter_bound=1;
		m_t=0; 
		m_viscosity_const=0;
		Physvector<dim,double> speed;
		speed.SetAll(0);
		double prop=1;
		 Nx=50;
		 Ny=50;
		m_v_1_h.Set(1,Nx);
		m_v_1_h.Set(2,Ny);
		m_v_h.Set(1,1./Nx);
		m_v_h.Set(2,1./Ny);
		ParticleToKey< part,world::type_key_vect::type_data ,double,dim> m_to_key(m_v_1_h,m_v_h);
		Physvector<dim,int> key;
		
		for(int i=-Nx;i<Nx;++i)
		{
			speed.Set(2,(pow(Nx,2)-pow(i+0.5,2))*Ny*pow(m_v_h.Get(1),2)*m_v_h.Get(2));
			speed.Set(1,(Nx*Nx*i-pow(i,3)/3.)*pow(m_v_h.Get(1),3));
			key.Set(1,i);
			key.Set(2,0);
			mac m(speed,0,0,0);
			if(i!=Nx-1)
			{
				m.SetConstSpeed(2,true);
			}
			m_w.m_mac_grid[key]=m;
		}
		for(int i=-Nx;i<Nx;++i)
		{
			for(int j=1;j<=Ny;++j)
			{
				speed.Set(2,(pow(Nx,2)-pow(i+0.5,2))*(Ny-j)*pow(m_v_h.Get(1),2)*m_v_h.Get(2));
				speed.Set(1,(Nx*Nx*i-pow(i,3)/3.)*pow(m_v_h.Get(1),3));
				key.Set(1,i);
				key.Set(2,j);
			if(i!=Nx-1&&j!=Ny)
			{
				Physvector<dim,double> keytemp=m_to_key.FromKey(key);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(1)+=0.25*m_v_h.Get(1);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(1)-=0.5*m_v_h.Get(1);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(2)+=0.25*m_v_h.Get(2);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(2)-=0.5*m_v_h.Get(2);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(1)+=0.5*m_v_h.Get(1);
				m_w.m_particle_list.push_back(part(keytemp));
				keytemp.GetRef(2)+=0.5*m_v_h.Get(2);
				m_w.m_particle_list.push_back(part(keytemp));

			}
				mac m(speed,0,0,0);
				m_w.m_mac_grid[key]=m;
			}
		}
		m_init.PrepareConstSpeed();
		m_g.Set(1,0);
		m_g.Set(2,-1);
		m_dt=0;
		m_t=0;
	}
};


class JetDEau_Lin_Non_Stat :public JetDEau_Test
{

	public:
	double maxer;
	double meaner;
	int Nx;
	int Ny;
	JetDEau_Lin_Non_Stat():maxer(0)
	{
	}
	void Calculate()
	{
		JetDEau_Test::Calculate();
	}
	void Test()
	{
		meaner=0;
		int N=0;
		Physvector<dim,int> key;
		for(int i=-Nx;i<Nx;++i)
		{
			for(int j=0;j<=Ny;++j)
			{
				++N;
				key.Set(1,i);
				key.Set(2,j);
				Physvector<2,double> speed;
				m_w.m_mac_grid[key].GetSpeed(speed);
				double temp=0;
				temp+=abs(speed.Get(1)-(Nx*Nx*i-pow(i,3)/3.)*pow(m_v_h.Get(1),3));
				temp+=abs(speed.Get(2)-(pow(Nx,2)-pow(i+0.5,2))*(Ny-j)*pow(m_v_h.Get(1),2)*m_v_h.Get(2));
				meaner+=temp;
				if(temp>maxer)
				{
					maxer=temp;
				}
			}
		}
		meaner/=N;
	}
	void SetUp()
	{
		m_no_output=false;
		m_i=0;
		m_out.SetUp();
		m_rho_fluid=1;
		m_rho_air=1;
		m_1_rho_fluid=1;
		m_1_rho_air=1;
		m_rho_inter=1;
		m_1_rho_inter=1;
		m_rho_inter_bound=1;
		m_1_rho_inter_bound=1;
		m_t=0; 
		m_viscosity_const=0;
		Physvector<dim,double> speed;
		speed.SetAll(0);
		double prop=1;
		 Nx=50;
		 Ny=50;
		m_v_1_h.Set(1,Nx);
		m_v_1_h.Set(2,Ny);
		m_v_h.Set(1,1./Nx);
		m_v_h.Set(2,1./Ny);
		ParticleToKey< part,world::type_key_vect::type_data ,double,dim> m_to_key(m_v_1_h,m_v_h);
		Physvector<dim,int> key;
		
		for(int i=-Nx;i<Nx;++i)
		{
			speed.Set(2,(pow(Nx,2)-pow(i+0.5,2))*Ny*pow(m_v_h.Get(1),2)*m_v_h.Get(2));
			speed.Set(1,(Nx*Nx*i-pow(i,3)/3.)*pow(m_v_h.Get(1),3));
			key.Set(1,i);
			key.Set(2,0);
			mac m(speed,0,0,0);
			m.SetConstSpeed(2,true);
			m_w.m_mac_grid[key]=m;
		}
		for(int j=0;j<=Ny;++j)
		{
			speed.Set(2,0);
			speed.Set(1,0);
			key.Set(1,-Nx);
			key.Set(2,j);
			mac m(speed,0,0,0);
			m.SetConstSpeed(1,true);
			m_w.m_mac_grid[key]=m;
			speed.Set(2,0);
			speed.Set(1,0);
			key.Set(1,Nx-1);
			key.Set(2,j);
			mac m2(speed,0,0,0);
			m2.SetConstSpeed(1,true);
			m_w.m_mac_grid[key]=m2;
		}
		m_init.PrepareConstSpeed();
		m_g.Set(1,0);
		m_g.Set(2,-1);
		m_dt=0;
		m_t=0;
		m_out.Calculate();
	}
};
class Test_Stationar : public CxxTest::TestSuite
{
	public:
	void test_Lin()
	{
		JetDEau_Lin J;
		J.SetUp();
		for(int i=0;i<=10;++i)
		{
			J.Test();
			if(J.maxer>0.1)
			{
				TS_FAIL("To Much error with analytical solution");
				cout<<"Error is "<<J.maxer<<" "<<J.meaner<<endl;
			}
			J.maxer=0;
			J.Calculate();
		}
	}

	void xtest_Lin_No_Stat()
	{

		JetDEau_Lin_Non_Stat J;
		J.SetUp();
		for(int i=0;true;++i)
		{
			J.Calculate();
		}

	}
};
