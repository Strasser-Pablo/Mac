#ifndef Policy_Add_Particle_Center_H
#define Policy_Add_Particle_Center_H

#include "RundingFunction.h"
#include "Physvector.h"
template <typename Data>
class Policy_Add_Particle_Center
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_key::type_data type_key_value;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	static const int type_dim=type_spacing_vector::type_dim;

	typedef typename Data::type_data_struct::type_Data_Topology type_Data_Topology;
	typedef typename type_Data_Topology::type_particle_list type_particle_list;
	typedef typename type_Data_Topology::type_particle type_particle;
	typedef typename type_particle::type_data_value type_data_value;
	typedef typename type_particle::type_data_vector type_data_vector;
	Round<type_data_value,type_key_value> m_round;
	type_particle_list &m_list;
	const type_spacing_vector &m_h;
	public:
	Policy_Add_Particle_Center(const Data& data) : m_list(data.m_data.GetTopologyData().GetRefToParticleList()),m_h(data.m_data.GetGridData().m_h.GetRef())
	{
	}
	void AddParticle(const type_key& vect)
	{
		type_data_vector ret;
		for(int i=1;i<=type_dim;++i)
		{
			ret.GetRef(i)=vect.Get(i)*m_h.Get(i);
		}
		m_list.push_back(type_particle(ret));
	}
};
#endif
