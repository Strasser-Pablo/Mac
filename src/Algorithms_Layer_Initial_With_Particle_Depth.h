#ifndef Algorithms_Layer_Initial_With_Particle_Depth_H
#define Algorithms_Layer_Initial_With_Particle_Depth_H

template <typename DataType,typename Policy>
class Algorithms_Layer_Initial_With_Particle_Depth : public Policy
{
	using Policy::GetKeyFromParticle;
	using Policy::GetDepthRemoveParticle;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_particle_list::iterator iterator;
	type_grid& m_grid;
	type_particle_list& m_list;
	public:
	Algorithms_Layer_Initial_With_Particle_Depth(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData()), m_list(data.m_data.GetTopologyData().GetRefToParticleList())
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		iterator it=m_list.begin();
		while(it!=m_list.end())
		{
			if(m_grid[GetKeyFromParticle(*it)].CellType_GetRef().GetIsInterior())
			{
				m_grid[GetKeyFromParticle(*it)].Layer_GetRef().SetLayer(0);
				if(m_grid[GetKeyFromParticle(*it)].Depth_GetRef().GetDepth()>GetDepthRemoveParticle())
				{
					it=m_list.erase(it);
				}
				else
				{
					++it;
				}
			}
			else
			{
				m_grid[GetKeyFromParticle(*it)].Layer_GetRef().SetLayer(0);
				m_grid[GetKeyFromParticle(*it)].CellType_GetRef().SetFluid();
				++it;
			}
		}
		long t_end=times(&t2);
		cout<<"real Layer initial With Particle Depth "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Layer initial With Particle Depth "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
