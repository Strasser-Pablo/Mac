#ifndef Algorithms_Solve_Pressure_Update_H
#define Algorithms_Solve_Pressure_Update_H

#include <cmath>
#include <map>
#include <deque>
#include <stack>
#include <sys/times.h>
#include "lusol.h"
using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Solve_Pressure_Update: public Policy
{
	using Policy::Get_Divergence;
	using Policy::Get_Gradiant;
	using Policy::Get_Is_Von_Neumann_Boundary;
	using Policy::Get_Pressure_If_Correction;
	using Policy::GetLinearUpdateMinimalLena;
	using Policy::GetLinearUpdateLenaGrowFactor;
	using Policy::GetLinearUpdateMinMaxN;
	using Policy::GetLinearUpdateGrowMaxN;
	using Policy::GetLinearUpdateLuparm;
	using Policy::GetLinearUpdateParmlu;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data type_data_data;
	typedef typename type_data_data::type_pressure::type_pressure type_pressure;
	typedef typename type_grid::type_offset type_neigh;
	typedef typename type_data_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_value;
	typedef typename type_speed::type_speed::type_vector type_speed_vector;
	typedef typename type_grid::type_spacing_vector type_spacing_vector;
	typedef typename type_grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_speed::type_dim;
	type_grid& m_grid;
	const type_spacing_vector& m_1_h;
	const type_Time_Type& m_dt;
	type_speed_value* m_value;
	bool m_bfactorization;
	int nb_fact;
	int nb_add;
	int nb_rpc_del;
	int nb_rpc_add;
	stack<int> m_free_list;
	//lusol_Data
	int m_m;
	int m_n;
	int m_nelem;
	int m_lena;
	int m_nmax;
	int* m_luparm;
	double* m_parmlu;
	double* m_a;
	int* m_indc;
	int* m_indr;
	int* m_ip;
	int* m_iq;
	int* m_lenc;
        int* m_lenr;
	int* m_locc;
	int* m_locr;
	int* m_iploc;
	int* m_iqloc;
	protected:
	void UpdateNeighbour(const type_neigh& neigh,stack<type_neigh> & stack_to_add)
	{
		for(int i=1;i<=type_dim;++i)
		{
			for(int s=-1;s<=1;s+=2)
			{
				type_neigh neigh2=neigh.GetNeighbour(i,s);
				//Test if we have a neighbour.
				if(neigh2.IsValid())
				{
					stack_to_add.push(neigh2);
				}
			}
		}
	}
	void UpdateFactorization()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);

		++nb_fact;
		stack<type_neigh> new_point;
		stack<type_neigh> up_point;
		stack<type_neigh> up2_point;
		stack<type_neigh> del_point;
		int lay_max=m_n;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(!it.data().Id_Cell_GetRef().GetIsLayerEmpty())
			{
				if(!it.data().CellType_GetRef().GetIsInDomain())
				{
					del_point.push(it.data());
					UpdateNeighbour(it.data(),up_point);
				}
			}
			else
			{
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					new_point.push(it.data());
					UpdateNeighbour(it.data(),up_point);
				}
			}
		}
		while(!up_point.empty())
		{
			type_neigh neigh=up_point.top();
			up_point.pop();
			if(!neigh.Id_Cell_GetRef().GetIsLayerEmpty())
			{
				if(neigh.CellType_GetRef().GetIsInDomain())
				{
					up2_point.push(neigh);
				}
			}
		}
		while(!del_point.empty())
		{
			type_neigh neigh=del_point.top();
			del_point.pop();
			int i=neigh.Id_Cell_GetRef().GetLayer()+1;
			int mode1=1;
			int mode2=0;
			double diag;
			double vnorm;
			int inform;
			double* v=new double[m_m];
			double* w=new double[m_n];
			++nb_rpc_del;
			lu8rpc(mode1,mode2,m_m,m_n,i,nullptr,nullptr,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform,diag,vnorm );
			lu8rpr(mode1,mode2,m_m,m_n,i,v,w,nullptr,m_lena,m_luparm,m_parmlu,m_a, m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform );

			neigh.Id_Cell_GetRef().SetLayerEmpty();
			m_free_list.push(i-1);
			delete[] v;
			delete[] w;
		}
		while(!new_point.empty())
		{
			if(m_m+1>=m_nmax)
			{
				cout<<"complete refactorization because of m_m,m_n too small for add a row and a column "<<nb_fact<<endl;
				cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
				cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
				Complete_Factorization();
				return;
			}
			double* v=new double[m_m+1];
			double* vvv=new double[m_m+1];
			for(int i=0;i<=m_m;++i)
			{
				v[i]=0;
				vvv[i]=0;
			}
			type_neigh next_neigh=new_point.top();
			new_point.pop();
			int lay_cur;
			//Cell has no number assign one.
			if(next_neigh.Id_Cell_GetRef().GetIsLayerEmpty())
			{
				int lay;
				if(!m_free_list.empty())
				{
					lay=m_free_list.top();
					m_free_list.pop();
				}
				else
				{
					lay=lay_max;
					++lay_max;
				}
				next_neigh.Id_Cell_GetRef().SetLayer(lay);
				lay_cur=lay;
			}
			else
			{
				lay_cur=next_neigh.Id_Cell_GetRef().GetLayer();
			}
			type_speed_value temp_diag_value=0;
			//For every direction and every sign.
			for(int i=1;i<=type_dim;++i)
			{
				for(int s=-1;s<=1;s+=2)
				{
					temp_diag_value-=pow(m_1_h.Get(i),2);
					int lay_cur2;
					type_neigh neigh=next_neigh.GetNeighbour(i,s);
					//Test if we have a neighbour.
					if(neigh.IsValid())
					{
						if(Get_Is_Von_Neumann_Boundary(next_neigh,i,s))
						{
							temp_diag_value+=pow(m_1_h.Get(i),2);
						}
						//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
						else if(neigh.CellType_GetRef().GetIsInDomain())
						{
							if(neigh.Id_Cell_GetRef().GetIsLayerEmpty())
							{
								int lay;
								if(!m_free_list.empty())
								{
									lay=m_free_list.top();
									m_free_list.pop();
									neigh.Id_Cell_GetRef().SetLayer(lay);
								}
								else
								{
									continue;
								}
								lay_cur2=lay;
							}
							else
							{
								lay_cur2=neigh.Id_Cell_GetRef().GetLayer();
							}
							v[lay_cur2]=pow(m_1_h.Get(i),2);
							vvv[lay_cur2]=pow(m_1_h.Get(i),2);
						}
					}
				}
			}
			//Insert diagonal value
			v[lay_cur]=temp_diag_value;
			vvv[lay_cur]=temp_diag_value;
			if(lay_cur>=m_m)
			{
				int inform;
				double diag;
				double vnorm;
				int mode=1;
				++m_m;
				lu8adr(m_m,m_n,v,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform,diag );
				if(inform==7)
				{
					cout<<"complete refactorization because of lena too small for adr "<<nb_fact<<endl;
					cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
					cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
					delete[] v;
					delete[] vvv;
					Complete_Factorization();
					return;
				}
				++m_n;
				lu8adc(mode,m_m,m_n,v,nullptr,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform,diag,vnorm );
				if(inform==7)
				{
					cout<<"complete refactorization because of lena too small for adc "<<nb_fact<<endl;
					cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
					cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
					delete[] v;
					delete[] vvv;
					Complete_Factorization();
					return;
				}
				++nb_add;
			}
			else
			{
				int inform;
				double diag;
				double vnorm;
				int mode1=1;
				int mode2=1;
				double* w=new double[m_n];
				double *v2=new double[m_m];
				int i=lay_cur+1;
				lu8rpr(mode1,mode2,m_m,m_n,i,v2,w,v,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform);
				if(inform==7)
				{
					cout<<"complete refactorization because of lena too small for rpr add "<<nb_fact<<endl;
					cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
					cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
					delete[] w;
					delete[] v2;
					delete[] v;
					delete[] vvv;
					Complete_Factorization();
					return;
				}
				lu8rpc(mode1,mode2,m_m,m_n,i,vvv,nullptr,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform,diag,vnorm);
				if(inform==7)
				{
					cout<<"complete refactorization because of lena too small for rpc add "<<nb_fact<<endl;
					cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
					cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
					delete[] w;
					delete[] v2;
					delete[] v;
					delete[] vvv;
					Complete_Factorization();
					return;
				}
				++nb_rpc_add;
				delete[] w;
				delete[] v2;
			}
			delete[] v;
			delete[] vvv;
		}
		while(!up2_point.empty())
		{
			type_neigh next_neigh=up2_point.top();
			up2_point.pop();
			double* v=new double[m_m];
			double* w=new double[m_n];
			double* w2=new double[m_n];
			for(int i=0;i<m_m;++i)
			{
				v[i]=0;
			}
			int lay_cur=next_neigh.Id_Cell_GetRef().GetLayer();
			type_speed_value temp_diag_value=0;
			//For every direction and every sign.
			for(int i=1;i<=type_dim;++i)
			{
				for(int s=-1;s<=1;s+=2)
				{
					temp_diag_value-=pow(m_1_h.Get(i),2);
					int lay_cur2;
					type_neigh neigh=next_neigh.GetNeighbour(i,s);
					//Test if we have a neighbour.
					if(neigh.IsValid())
					{
						if(Get_Is_Von_Neumann_Boundary(next_neigh,i,s))
						{
							temp_diag_value+=pow(m_1_h.Get(i),2);
						}
						//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
						else if(neigh.CellType_GetRef().GetIsInDomain())
						{
							lay_cur2=neigh.Id_Cell_GetRef().GetLayer();
							if(lay_cur2<m_m)
							{
								v[lay_cur2]=pow(m_1_h.Get(i),2);
							}
						}
					}
				}
			}
			//Insert diagonal value
			v[lay_cur]=temp_diag_value;
			int mode1=1;
			int mode2=1;
			int inform;
			double diag;
			double vnorm;
			int i=lay_cur+1;
			lu8rpr(mode1,mode2,m_m,m_n,i,w2,w,v,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform);
			if(inform==7)
			{
				cout<<"complete refactorization because of lena too small for rpr del "<<nb_fact<<endl;
				cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
				cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
				delete[] v;
				delete[] w;
				delete[] w2;
				Complete_Factorization();
				return;
			}
			lu8rpc(mode1,mode2,m_m,m_n,i,v,nullptr,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr,inform,diag,vnorm );
			if(inform==7)
			{
				cout<<"complete refactorization because of lena too small for rpc del "<<nb_fact<<endl;
				cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
				cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
				delete[] v;
				delete[] w;
				delete[] w2;
				Complete_Factorization();
				return;
			}
			delete[] v;
			delete[] w;
			delete[] w2;
		}
		long t_end=times(&t2);
		cout<<"real Pressure_Update_Factorization "<<(t_end-t_deb)/conv<<endl;
		cout<<"real Pressure_Update_Factorization "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
	public:
	Algorithms_Solve_Pressure_Update(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_dt(data.m_data.GetTimingData().m_dt),m_bfactorization(false),m_a(nullptr),m_indc(nullptr),m_indr(nullptr),m_ip(nullptr),m_iq(nullptr),m_lenc(nullptr),m_lenr(nullptr),m_locc(nullptr),m_locr(nullptr),m_iploc(nullptr),m_iqloc(nullptr),nb_fact(0)
	{
		GetLinearUpdateLuparm(m_luparm);
		GetLinearUpdateParmlu(m_parmlu);
	}
	~Algorithms_Solve_Pressure_Update()
	{
		delete[] m_a;
		delete[] m_indc;
		delete[] m_indr;
		delete[] m_ip;
		delete[] m_iq;
      		delete[] m_lenc;
		delete[] m_lenr;
		delete[] m_iploc;
		delete[] m_iqloc;
		delete[] m_locc;
		delete[] m_locr;
	}
	void Init_Iteration()
	{
		if(!m_bfactorization)
		{
			Complete_Factorization();
		}
		UpdateFactorization();
	}
	void End_Iteration()
	{
	}
	void Divergence_Projection()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		type_speed_value* b=new type_speed_value[m_m];
		type_speed_value* res=new type_speed_value[m_n];
		// Set b to divergence.
		// Solve the linear system.
		int mode=5;
		int inform;
		bool brefact=true;
		while(brefact)
		{
			double _1_dt=1/m_dt;
			for(int i=0;i<m_m;++i)
			{
				b[i]=0;
			}
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				int lay_cur;
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					lay_cur=it.data().Id_Cell_GetRef().GetLayer();
					b[lay_cur]=Get_Divergence(it.data()).Get()*_1_dt;
				}
			}
			brefact=false;
			lu6sol(mode ,m_m ,m_n,b ,res ,m_lena,m_luparm,m_parmlu,m_a,m_indc,m_indr,m_ip,m_iq,m_lenc,m_lenr,m_locc,m_locr, inform );
			// Set the pressure of cell from the result.
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				int lay_cur;
				it.data().Acceleration_GetRef().Set(it.data().Speed_GetRef().Get(),true);
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					lay_cur=it.data().Id_Cell_GetRef().GetLayer();
					it.data().Pressure_GetRef().Pressure_Set(type_pressure(res[lay_cur]));
				}
				else
				{
					it.data().Pressure_GetRef().Pressure_Set(type_pressure(0));
				}
			}
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				for(int i=1;i<=type_dim;++i)
				{
					if(Get_Pressure_If_Correction(it.data(),i))
					{
						it.data().Speed_GetRef().Set(i,it.data().Speed_GetRef().Get(i)-Get_Gradiant(it.data(),i)*m_dt);
					}
				}
			}
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					type_speed_value div=Get_Divergence(it.data()).Get();
					if(abs(div)>0.0000000001)
					{
						cout<<"key "<<it.key()<<endl;
						cout<<"div "<<div<<endl;
						brefact=true;
						break;
					}
				}
			}
			if(brefact)
			{
				for(iterator it=m_grid.begin();it!=m_grid.end();++it)
				{
					it.data().Speed_GetRef().Set(it.data().Acceleration_GetRef().Get(),true);
				}
				cout<<"complete refactorization because of residu "<<nb_fact<<endl;
				cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
				Complete_Factorization();
			}
		}
		delete[] b;
		delete[] res;
		long t_end=times(&t2);
		cout<<"real Pressure_Projection "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Pressure_Projection "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
	void Complete_Factorization()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		nb_add=0;
		nb_rpc_del=0;
		nb_rpc_add=0;
		m_free_list=stack<int>();
		// Upper bound of memory usage.
		int n=m_grid.size_upper();

		nb_fact=1;
		m_lena=GetLinearUpdateLenaGrowFactor()*n;
		if(m_lena<GetLinearUpdateMinimalLena())
		{
			m_lena=GetLinearUpdateMinimalLena();
		}
		delete[] m_a;
		m_a=new double[m_lena];
		delete[] m_indc;
		m_indc=new int[m_lena];
		delete[] m_indr;
		m_indr=new int[m_lena];


		//Set every layer to empty.
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Id_Cell_GetRef().SetLayerEmpty();
		}
		int lay=0;
		int lay_cur;
		int off=0;
		deque<type_neigh>next;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			type_neigh  neigh;
			if(!it.data().Id_Cell_GetRef().GetIsLayerEmpty())
			{
				continue;
			}
			next.push_back(it.data());
			while(!next.empty())
			{
				type_neigh next_neigh=next.front();
				next.pop_front();
				//For every cell in domain. Where we assign a unic number.
				if(next_neigh.CellType_GetRef().GetIsInDomain())
				{
					//Cell has no number assign one.
					if(next_neigh.Id_Cell_GetRef().GetIsLayerEmpty())
					{
						next_neigh.Id_Cell_GetRef().SetLayer(lay);
						lay_cur=lay;
						++lay;
					}

					//We have a number, use it.
					else
					{
						lay_cur=next_neigh.Id_Cell_GetRef().GetLayer();
					}
					type_speed_value temp_diag_value=0;
					//For every direction and every sign.
					for(int i=1;i<=type_dim;++i)
					{
						for(int s=-1;s<=1;s+=2)
						{
							temp_diag_value-=pow(m_1_h.Get(i),2);
							int lay_cur2;
							neigh=next_neigh.GetNeighbour(i,s);
							//Test if we have a neighbour.
							if(neigh.IsValid())
							{
								if(Get_Is_Von_Neumann_Boundary(next_neigh,i,s))
								{
									temp_diag_value+=pow(m_1_h.Get(i),2);
								}
								//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
								else if(neigh.CellType_GetRef().GetIsInDomain())
								{
									if(neigh.Id_Cell_GetRef().GetIsLayerEmpty())
									{
										neigh.Id_Cell_GetRef().SetLayer(lay);
										lay_cur2=lay;
										++lay;
										next.push_back(neigh);
									}
									else
									{
										lay_cur2=neigh.Id_Cell_GetRef().GetLayer();
									}
									//Insert of diagonal value
									m_a[off]=pow(m_1_h.Get(i),2);
									m_indr[off]=lay_cur+1;
									m_indc[off]=lay_cur2+1;
									++off;
								}
							}
						}
					}
					//Insert diagonal value
					m_a[off]=temp_diag_value;
					m_indr[off]=lay_cur+1;
					m_indc[off]=lay_cur+1;
					++off;
				}
			};
		}
		m_n=lay;
		m_m=lay;
		int nelem=off;
		m_nmax=GetLinearUpdateGrowMaxN()*m_n;
		if(m_nmax<GetLinearUpdateMinMaxN())
		{
			m_nmax=GetLinearUpdateMinMaxN();
		}
		delete[] m_ip;
		m_ip=new int[m_nmax];
		delete[] m_iq;
		m_iq=new int[m_nmax];
      		delete[] m_lenc;
		m_lenc=new int[m_nmax];
		delete[] m_lenr;
		m_lenr=new int[m_nmax];
		delete[] m_iploc;
		m_iploc=new int[m_nmax];
		delete[] m_iqloc;
		m_iqloc=new int[m_nmax];
		delete[] m_locc;
		m_locc=new int[m_nmax];
		delete[] m_locr;
		m_locr=new int[m_nmax];
		int* ipinv=new int[m_m];
		int* iqinv=new int[m_n];
		double* w=new double[m_n];
		int inform;
		lu1fac(m_m,m_n,nelem, m_lena, m_luparm, m_parmlu,m_a,m_indc,m_indr, m_ip, m_iq,m_lenc, m_lenr, m_locc, m_locr,m_iploc,m_iqloc, ipinv,iqinv,w ,inform );
		delete[] ipinv;
		delete[] iqinv;
		delete[] w;
		m_bfactorization=true;
		long t_end=times(&t2);
		cout<<"real Pressure_Complete_Factorization "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Pressure_Complete_Factorization "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
		if(inform==7)
		{
			cout<<"complete refactorization because of lena to small for fac "<<nb_fact<<endl;
			cout<<"nb_rpc_del "<<nb_rpc_del<<" nb_rpc_add "<<nb_rpc_add<<" nb_add  "<<nb_add<<endl;
			cout<<"lena "<<m_lena<<" n "<<m_n<<endl;
			m_lena=this->luparm_minlen;
			cout<<"lena needed "<<m_lena<<endl;

			Complete_Factorization();
		}
	}
};
#endif
