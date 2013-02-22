#ifndef OFFSET_GETNEIGHBOUR_H
#define OFFSET_GETNEIGHBOUR_H
#include "Singleton.h"
#include "Pow_Int.h"
#include <cmath>
template<int N,int Dim,class Type>
class Offset_GetNeighbour : public Singleton<Offset_GetNeighbour<N,Dim,Type> >
{
    friend class Singleton<Offset_GetNeighbour<N,Dim,Type> >;
    Type neigh[Dim][2][Pow_Int<N,Dim,Type>::GetStatic(Dim)];
    bool neighb[Dim][2][Pow_Int<N,Dim,Type>::GetStatic(Dim)];
    Offset_GetNeighbour()
    {
        Pow_Int<N,Dim,Type>& m_pow=Singleton<Pow_Int<N,Dim,Type> >::GetInstance();
        for(int i=1;i<=Dim;++i)
        {
            for(int dir=-1;dir<=1;dir+=2)
            {
                for(Type off=0;off<m_pow.Get(Dim);++off)
                {
                    neighb[i-1][(dir+1)/2][off]=true;
                    int res=off+dir*m_pow.Get(i-1);
                    if(res<0)
                    {
                        res+=m_pow.Get(i);
                    }
                    else if(dir==1&&((res/m_pow.Get(i-1)%N)==0))
                    {
                        res-=m_pow.Get(i);
                    }
                    else if(dir==-1&&((res/m_pow.Get(i-1)%N)==N-1))
                    {
                        res+=m_pow.Get(i);
                    }
                    else
                    {
                        neighb[i-1][(dir+1)/2][off]=false;
                    }
                    neigh[i-1][(dir+1)/2][off]=res;
                }
            }
        }
    }

    Offset_GetNeighbour(const Offset_GetNeighbour<N,Dim,Type>&)=delete;
    ~Offset_GetNeighbour() __attribute__ ((const))
    {

    }

    public:
    bool Get(int i,int dir,Type off,Type & res)
    {
        res=neigh[i-1][(dir+1)/2][off];
        bool b=neighb[i-1][(dir+1)/2][off];
        return neighb[i-1][(dir+1)/2][off];
    }
};

#include "Singleton_Impl.h"
#endif // OFFSET_GETNEIGHBOUR_H
