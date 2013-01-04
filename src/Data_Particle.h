#ifndef Data_Particle_H
#define Data_Particle_H
#include "Physvector.h"
template <typename DataBase,int N=1>
class Data_Particle
{
	public:
	typedef typename DataBase::type_data_value type_data_value;
	typedef typename DataBase::type_data_vector type_data_vector;
	static const int type_dim=DataBase::type_dim;
    static int imove_particle;
	Data_Particle()
	{
	}
    Data_Particle(const type_data_vector& vect,int i=-1)
	{
        if(i==-1)
        {
            i=imove_particle;
        }
        m_pos[i]=vect;
	}
    void SetParticlePos(const type_data_vector& vect,int i=-1)
	{
        if(i==-1)
        {
            i=imove_particle;
        }
        m_pos[i]=vect;
	}
    const type_data_vector& GetParticlePos(int i=-1) const
	{
        if(i==-1)
        {
            i=imove_particle;
        }
        return m_pos[i];
	}
    type_data_vector& GetParticlePosRef(int i=-1)
	{
        if(i==-1)
        {
            i=imove_particle;
        }
        return m_pos[i];
	}
    static void SetIPos(int i)
    {
        imove_particle=i;
    }
    static int GetIPos()
    {
        return imove_particle;
    }

	private:
    type_data_vector m_pos[N];
};
template <typename DataBase,int N>
int Data_Particle<DataBase,N>::imove_particle=0;
#endif
