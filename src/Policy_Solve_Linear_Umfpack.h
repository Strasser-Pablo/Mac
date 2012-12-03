#ifndef Policy_Solve_Linear_Umfpack_H
#define Policy_Solve_Linear_Umfpack_H
#include <umfpack.h>
#include <sys/times.h>

template <typename Data>
class Policy_Solve_Linear_Umfpack
{
	double controle[UMFPACK_CONTROL];
	void *m_Symbolic;
	void *m_Numeric ;
    bool b=false;
	public:
    void CheckError(int status,const char * message)
    {
        if(status!=UMFPACK_OK)
        {
            cout<<"umfpack error or warning :"<<status<<" in "<<message<<endl;
        }
    }

	Policy_Solve_Linear_Umfpack()
	{
		umfpack_di_defaults(controle);
		controle[UMFPACK_STRATEGY]=UMFPACK_STRATEGY_SYMMETRIC;
	}
	void Solve_Linear_FactorizeMatrice(int n,int* offset,int* indice,Data* value)
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		if(n!=0)
		{
			cout<<"n system size "<<n<<endl;
            int status=umfpack_di_symbolic (n, n,offset,indice,value,&m_Symbolic, controle, nullptr) ;
            CheckError(status," symbolic");
            status=umfpack_di_numeric (offset,indice,value,m_Symbolic,&m_Numeric,controle, nullptr) ;
            CheckError(status," numeric");
            b=true;
		}
		long t_end=times(&t2);
		cout<<"real Matrice Factorize "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Matrice Factorize "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
	void Solve_Linear_Clean()
	{
        if(b)
        {
            umfpack_di_free_symbolic (&m_Symbolic);
            umfpack_di_free_numeric (&m_Numeric);
            b=false;
        }
	}
	void Solve_Linear(int n,int* offset,int* indice,Data* value,Data* b,Data* res)
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
        long t_deb=times(&t1);
		if(n!=0)
		{
            int status=umfpack_di_solve (UMFPACK_A,offset,indice,value,res,b,m_Numeric, controle, nullptr);
            CheckError(status," solve");
		}
		long t_end=times(&t2);
		cout<<"real Matrice Solve "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Matrice Solve "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
