#include "lusol.h"
#include <iostream>
using namespace std;
int main()
{
	testtest();
	int m=4;
	int n=4;
	int mmax=2000000;
	int nmax=2000000;
	int nelem=12;
	int lena=100000000;
	double* a=new double[lena];
	int* indc=new int[lena];
	int* indr=new int[lena];

	a[0]=-4;
	indc[0]=1;
	indr[0]=1;

	a[1]=1;
	indc[1]=1;
	indr[1]=2;

	a[2]=1;
	indc[2]=1;
	indr[2]=3;

	a[3]=1;
	indc[3]=2;
	indr[3]=1;

	a[4]=-4;
	indc[4]=2;
	indr[4]=2;

	a[5]=1;
	indc[5]=2;
	indr[5]=4;

	a[6]=1;
	indc[6]=3;
	indr[6]=1;

	a[7]=-4;
	indc[7]=3;
	indr[7]=3;

	a[8]=1;
	indc[8]=3;
	indr[8]=4;

	a[9]=1;
	indc[9]=4;
	indr[9]=2;

	a[10]=1;
	indc[10]=4;
	indr[10]=3;

	a[11]=-4;
	indc[11]=4;
	indr[11]=4;

	double factol=2;
	int luparm[30];
	luparm[0]=6;
	luparm[1]=0;
	luparm[2]=5;
	luparm[5]=0;
	luparm[7]=1;
	double parmlu[30];
	parmlu[0]=factol;
	parmlu[1]=factol;
	parmlu[2]=3e-13;
	parmlu[3]=3.7e-11;
	parmlu[4]=3.7e-11;
	parmlu[5]=3.0;
	parmlu[6]=0.3;
	parmlu[7]=0.5;
	int* ip=new int[mmax];
	int* iq=new int[nmax];
	int* lenc=new int[nmax];
	int* lenr=new int[mmax];
	int* iploc=new int[nmax];
	int* iqloc=new int[mmax];
	int* ipinv=new int[mmax];
	int* iqinv=new int[nmax];
	double* w=new double[nmax];
	int inform;
	int* locc=new int[mmax];
	int* locr=new int[nmax];
	lu1fac(m ,n ,nelem ,lena ,luparm ,parmlu ,a ,indc ,indr ,ip ,iq , lenc ,lenr ,locc ,locr ,iploc ,iqloc ,ipinv ,iqinv ,w ,inform);

	int mode=1;
	double diag;
	double vnorm;
      	int lenl=luparm[22];
	for(int l = lenl-1;l>=0;--l)
	{
		cout<<"l "<<l<<" "<<indc[l]<<endl;
	}
	int nrank=luparm[15];
	cout<<"nrank "<<nrank<<endl;

	/*for(int i=2;i<=7;++i)
	{
		cout<<"i "<<i<<endl;
		n=i;
		double *v=new double[m];
		for(int i2=0;i2<m-1;++i2)
		{
			v[i2]=0;
		}
		v[m-1]=1;
		lu8adc(mode,m,n,v,w,lena,luparm,parmlu,a,indc,indr,ip,iq,
			lenc,lenr,locc,locr,inform,diag,vnorm );
		cout<<"inform "<<inform<<endl;
		m=i;
		double* w=new double[n];
		for(int i2=0;i2<n-2;++i2)
		{
			w[i2]=0;
		}
		w[n-2]=1;
		w[n-1]=-4;
		lu8adr(m,n,w,lena,luparm,parmlu,a,indc,indr,ip,iq,lenc,lenr,locc,locr,inform,diag );
		cout<<"inform "<<inform<<endl;
		delete[] v;
		cout<<"len L "<<luparm[22]<<endl;
		cout<<"len U "<<luparm[23]<<endl;
		delete[] w;

		if(i%200==0)
		{
			double* b=new double[m];
			double* x=new double[n];
			for(int i=0;i<m;++i)
			{
				b[i]=1;
			}

			mode=5;
			lu6sol(mode,m,n,b,x,lena,luparm,parmlu,a,indc,indr,ip,iq,lenc,lenr,locc,locr,inform );

			cout<<"x"<<endl;
			for(int i=0;i<n;++i)
			{
				cout<<i<<" "<<x[i]<<endl;
			}
			delete[] x;
			delete[] b;
		}
	}
	*/

	cout<<"m "<<m<<endl;
	cout<<"n "<<n<<endl;
	/*
	int jdel=3;

	cout<<"len L "<<luparm[22]<<endl;
	lu8dlc(m,n,jdel,lena,luparm,parmlu,a,indc,indr,ip,iq,
                         lenc,lenr,locc,locr,inform );
	cout<<"inform "<<inform<<endl;
	--n;
	*/
	cout<<"len L "<<luparm[22]<<endl;
	mode=1;
	int idel=3;
	delete[] w;
	w=new double[n];
	double* v=new double[m];
	for(int i=0;i<m;++i)
	{
		v[i]=1;
	}
	int jrep=1;
	int mode1=1;
	int mode2=1;
	//lu8rpc(mode1,mode2,m,n,jrep,v,w,lena,luparm,parmlu,a,indc,indr,ip,iq,lenc,lenr,locc,locr,inform,diag,vnorm );
	cout<<"inform "<<inform<<endl;
	delete[] w;

	mode1=2;
	mode2=1;
	double*	wnew=new double[n];
	for(int i=0;i<n;++i)
	{
		wnew[i]=1;
	}
	int irep=1;
	w=new double[n];
	w[0]=-4;
	w[1]=1;
	w[2]=1;
	w[3]=0;
	nrank=luparm[15];
	cout<<"nrank "<<nrank<<endl;

	lu8rpr(mode1,mode2,m,n,irep,v,w,wnew,lena,luparm,parmlu,a,indc,indr,ip,iq,lenc,lenr,locc,locr,inform );
	delete[] w;

	double* b=new double[m];
	double* x=new double[n];
	for(int i=0;i<m;++i)
	{
		b[i]=1;
	}

	mode=5;
	lu6sol(mode,m,n,b,x,lena,luparm,parmlu,a,indc,indr,ip,iq,lenc,lenr,locc,locr,inform );

	cout<<"x"<<endl;
	for(int i=0;i<n;++i)
	{
		cout<<i<<" "<<x[i]<<endl;
	}
	delete[] x;
	delete[] b;

	delete[] v;
	delete[] a;
	delete[] indr;
	delete[] indc;
	delete[] ip;
	delete[] iq;
	delete[] lenc;
	delete[] lenr;
	delete[] iploc;
	delete[] iqloc;
	delete[] ipinv;
	delete[] iqinv;
	delete[] locc;
	delete[] locr;
	return 0;
}
