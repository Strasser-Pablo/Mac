#ifndef Data_Particle_To_Key_H
#define Data_Particle_To_Key_H
#include "RundingFunction.h"

template <typename Data>
class Policy_Particle_To_Key
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_key type_data_key;
	typedef typename type_data_key::type_data type_data_key_value;
	typedef typename type_Data_Grid::type_data_vector type_data_cell_spacing;
	typedef typename Data::type_data_struct::type_Data_Topology type_Data_Topology;
	typedef typename type_Data_Topology::type_particle_list type_particle_list;
	typedef typename type_Data_Topology::type_particle type_particle;
	typedef typename type_particle::type_data_value type_data_value;
	typedef typename type_particle::type_data_vector type_data_vector;
	static const int type_dim=type_data_key::type_dim;
	Round<type_data_value,type_data_key_value> m_round;
	const type_data_cell_spacing &m_1_h;
	public:
	Policy_Particle_To_Key(Data& base) : m_1_h(base.m_data.GetGridData().m_h.GetRef_Inv())
	{
	}
	template <typename Particle>
	type_data_key GetKeyFromParticle(const Particle& part)
	{
		type_data_vector vect=part.GetParticlePos();
		type_data_key ret;
		for(int i=1;i<=type_dim;++i)
		{
			vect.GetRef(i)*=m_1_h.Get(i);
			ret.GetRef(i)=m_round(vect.GetRef(i));
		}
		return ret;
	}
};

#endif
