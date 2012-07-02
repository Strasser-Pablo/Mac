#ifndef Data_Particle_H
#define Data_Particle_H
#include "Physvector.h"
template <typename DataBase>
class Data_Particle
{
	public:
	typedef typename DataBase::type_data_value type_data_value;
	typedef typename DataBase::type_data_vector type_data_vector;
	static const int type_dim=DataBase::type_dim;
	Data_Particle()
	{
	}
	Data_Particle(const type_data_vector& vect) : m_pos(vect)
	{
	}
	void SetParticlePos(const type_data_vector& vect)
	{
		m_pos=vect;
	}
	const type_data_vector& GetParticlePos() const
	{
		return m_pos;
	}
	type_data_vector& GetParticlePosRef()
	{
		return m_pos;
	}
	private:
	type_data_vector m_pos;
};

#endif
