#ifndef Algorithms_Layer_Initial_With_Particle_H
#define Algorithms_Layer_Initial_With_Particle_H

template <typename DataType,typename Policy>
class Algorithms_Layer_Initial_With_Particle : public Policy
{
	using Policy::GetLayerParticleInitial;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_particle_list::const_iterator iterator;
	type_data& m_data;
	type_grid& m_grid;
	const type_particle_list& m_list;
	public:
	Algorithms_Layer_Initial_With_Particle(DataType data,const Policy& pol) :m_data(data.m_data), m_grid(m_data.GetGridData()), m_list(m_data.GetTopologyData().GetRefToParticleList()),Policy(pol)
	{
	}
	void Do()
	{
		for(iterator it=m_list.begin();it!=m_list.end();++it)
		{
			m_grid[this->GetKeyFromParticle(*it)].GetRef().SetLayer(GetLayerParticleInitial());
		}
	}
};

#endif
