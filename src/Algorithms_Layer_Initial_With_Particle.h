#ifndef Algorithms_Layer_Initial_With_Particle_H
#define Algorithms_Layer_Initial_With_Particle_H

template <typename DataType,typename Policy>
class Algorithms_Layer_Initial_With_Particle : public Policy
{
	using Policy::GetKeyFromParticle;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_particle_list::const_iterator iterator;
	type_grid& m_grid;
	const type_particle_list& m_list;
	public:
	Algorithms_Layer_Initial_With_Particle(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData()), m_list(data.m_data.GetTopologyData().GetRefToParticleList())
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		long t_deb=times(&t1);
		for(iterator it=m_list.begin();it!=m_list.end();++it)
		{
			m_grid[GetKeyFromParticle(*it)].Layer_GetRef().SetLayer(0);
			m_grid[GetKeyFromParticle(*it)].CellType_GetRef().SetFluid();
		}
		long t_end=times(&t2);
		cout<<"real Layer Initial With Particle "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Layer Initial With Particle "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
