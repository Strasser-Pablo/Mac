#ifndef OFFSET_H
#define OFFSET_H
#include "Physvector.h"
#include <cmath>
using namespace std;
template <typename type,int DIM,int N>
struct Offset
{
	type off;
	Offset(const Physvector<DIM,type>& key)
	{
		off=0;
		int B=1;
		for(int i=1;i<=DIM;++i)
		{
			off+=key.Get(i)%N*B;
			B*=N;
		}
	}
	Offset(type m_off=0):off(m_off)
	{
	}
	bool GetNeighbour(int i,int dir,Offset<type,DIM,N>& res)
	{
		res.off=off+dir*pow(N,i-1);
		if(res.off<0)
		{
			res.off+=N*pow(N,i-1);
			return true;
		}
		else if(((res.off%type(pow(N,i)))==0&&dir>0)||res.off>pow(N,DIM))
		{
			res.off-=pow(N,i);
			return true;
		}
		return false;
	}

};
#endif
