#ifndef Policy_Add_Particle_Cube_H
#define Policy_Add_Particle_Cube_H

#include "RundingFunction.h"
#include "Physvector.h"
template <typename Data>
class Policy_Add_Particle_Cube
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_key type_data_key;
	typedef typename type_Data_Grid::type_data_key_value type_data_key_value;
	typedef typename Data::type_data_struct::type_Data_Topology type_Data_Topology;
	typedef typename type_Data_Topology::type_particle_list type_particle_list;
	typedef typename type_Data_Topology::type_particle type_particle;
	typedef typename type_particle::type_data_value type_data_value;
	typedef typename type_particle::type_data_vector type_data_vector;
	static const int type_dim=type_Data_Grid::type_dim;
	Round<type_data_value,type_data_key_value> m_round;
	type_particle_list &m_list;
	const type_data_vector &m_h;
	int m_n;
	double m_dh;
	public:
	Policy_Add_Particle_Cube(const Data& data,int n) : m_list(data.m_data.GetTopologyData().GetRefToParticleList()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_n(n),m_dh(1./(2*m_n+1))
	{
	}
	void AddParticle(const type_data_key& vect)
	{
		int tab[type_dim];
		for(int i=0;i<type_dim;++i)
		{
			tab[i]=-m_n;
		}
		while(true)
		{
			type_data_vector ret;
			for(int i=1;i<=type_dim;++i)
			{
				ret.GetRef(i)=(vect.Get(i)+tab[i-1]*m_dh)*m_h.Get(i);
			}
			m_list.push_back(type_particle(ret));
			int j=0;
			while(j<type_dim&&tab[j]>=m_n)
			{
				tab[j]=-m_n;
				++j;
			}
			if(j<type_dim)
			{
				++tab[j];
			}
			else
			{
				break;
			}
		}
	}
};
#endif
