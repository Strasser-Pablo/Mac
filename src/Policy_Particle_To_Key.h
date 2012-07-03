#ifndef Data_Particle_To_Key_H
#define Data_Particle_To_Key_H
#include "RundingFunction.h"

template <typename DataBase>
class Policy_Particle_To_Key
{
	typedef typename DataBase::type_data_vector type_data_vector;
	typedef typename type_data_vector::type_data type_data;
	static const int type_dim=DataBase::type_dim;
	Round<type_data,int> m_round;
	const DataBase &m_data;
	public:
	Policy_Particle_To_Key(DataBase& base) : m_data(base)
	{
	}
	template <typename Particle>
	Physvector<type_dim,int> GetKeyFromParticle(const Particle& part)
	{
		type_data_vector vect=part.GetParticlePos();
		Physvector<type_dim,int> ret;
		for(int i=1;i<=type_dim;++i)
		{
			vect.GetRef(i)*=m_data.m_h.Get_Inv().Get(i);
			ret.GetRef(i)=m_round(vect.GetRef(i));
		}
		return ret;
	}
};

#endif
