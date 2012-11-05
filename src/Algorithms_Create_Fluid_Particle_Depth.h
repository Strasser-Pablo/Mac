#ifndef Algorithms_Create_Fluid_Particle_Depth_H
#define Algorithms_Create_Fluid_Particle_Depth_H

template <typename DataType,typename Policy>
class Algorithms_Create_Fluid_Particle_Depth : public Policy
{
	using Policy::AddParticle;
	using Policy::GetIsInboundNeedFilling;
	using Policy::GetDepthRemoveParticle;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_grid::iterator iterator;
	type_grid& m_grid;
	public:
	Algorithms_Create_Fluid_Particle_Depth(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(GetIsInboundNeedFilling(it.data()))
			{
				AddParticle(it.key());
				it.data().Layer_GetRef().SetLayer(0);
				it.data().CellType_GetRef().SetFluid();
			}
			else if(it.data().CellType_GetRef().GetIsInterior()&&it.data().Layer_GetRef().GetIsLayerEmpty()&&it.data().Depth_GetRef().GetDepth()<=GetDepthRemoveParticle())
			{
				AddParticle(it.key());
				it.data().Layer_GetRef().SetLayer(0);
			}
			else if(it.data().CellType_GetRef().GetIsInterior())
			{
				it.data().Layer_GetRef().SetLayer(0);
			}
		}
		long t_end=times(&t2);
		cout<<"real Create fluid particle depth "<<(t_end-t_deb)/conv<<endl;
		cout<<"real Create fluid particle depth "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
