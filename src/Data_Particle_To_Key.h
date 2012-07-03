#ifndef Data_Particle_To_Key_H
#define Data_Particle_To_Key_H
#include "RundingFunction.h"

template <typename DataBase>
class Data_Particle_To_Key: public DataBase
{
	typedef typename DataBase::type_data_vector type_data_vector;
	typedef typename type_data_vector::type_data type_data;
	static const int type_dim=DataBase::type_dim;
	Round<type_data,int> m_round;
	public:
	Data_Particle_To_Key(DataBase& base) : DataBase(base)
	{
	}
	template <typename Particle>
	Physvector<type_dim,int> GetKeyFromParticle(const Particle& part)
	{
		type_data_vector vect=part.GetParticlePos();
		Physvector<type_dim,int> ret;
		for(int i=1;i<=type_dim;++i)
		{
			vect.GetRef(i)*=this->m_h.Get_Inv().Get(i);
			ret.GetRef(i)=m_round(vect.GetRef(i));
		}
		return ret;
	}
};

#endif
