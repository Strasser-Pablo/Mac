#ifndef Policy_Solve_Linear_Umfpack_H
#define Policy_Solve_Linear_Umfpack_H
#include <umfpack.h>
	
#include <sys/times.h>
template <typename Data>
class Policy_Solve_Linear_Umfpack
{
	public:
	Policy_Solve_Linear_Umfpack()
	{
	}
	void Solve_Linear(int n,int* offset,int* indice,Data* value,Data* b,Data* res)
	{
/*		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);*/
		if(n!=0)
		{
			/*
			for(int i=0;i<n;++i)
			{
				cout<<"line "<<i<<endl;
				for(int off=offset[i];off<offset[i+1];++off)
				{
					cout<<"indice "<<indice[off]<<endl;
					cout<<"value "<<value[off]<<endl;
				}
			}
			for(int i=0;i<n;++i)
			{
				cout<<"b "<<b[i]<<endl;
			}
			*/
			void *Symbolic, *Numeric ;
			(void) umfpack_di_symbolic (n, n,offset,indice,value,&Symbolic, nullptr, nullptr) ;
			(void) umfpack_di_numeric (offset,indice,value,Symbolic,&Numeric,nullptr, nullptr) ;
			umfpack_di_free_symbolic (&Symbolic) ;
			(void) umfpack_di_solve (UMFPACK_A,offset,indice,value,res,b, Numeric, nullptr, nullptr) ;
			umfpack_di_free_numeric (&Numeric) ;
		}
/*		long t_end=times(&t2);
		cout<<"real solve_lin "<<(t_end-t_deb)/conv<<endl;
		cout<<"user solve_lin "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
*/
	}
};

#endif
