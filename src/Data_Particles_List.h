#ifndef Data_Particles_List_H
#define Data_Particles_List_H
#include "TableContainerList.h"
template <typename Particle, typename DataBase>
class Data_Particles_List : public DataBase
{
	TableContainerList<Particle> m_table;
	public:
	Data_Particles_List()
	{
	}
	Data_Particles_List(const DataBase& base) : DataBase(base)
	{
	}
	TableContainerList<Particle>& GetRefToParticleList()
	{
		return m_table;
	}
	const TableContainerList<Particle>& GetRefToParticleList() const
	{
		return m_table;
	}
	typedef Particle type_particle;
	typedef TableContainerList<Particle> type_particle_list;
};

#endif
