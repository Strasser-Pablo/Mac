#ifndef Algorithms_Create_Fluid_Particle_H
#define Algorithms_Create_Fluid_Particle_H

template <typename DataType,typename Policy>
class Algorithms_Create_Fluid_Particle : public Policy
{
	using Policy::AddParticle;
	using Policy::GetIsInboundNeedFilling;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_grid::iterator iterator;
	type_data& m_data;
	type_grid& m_grid;
	public:
	Algorithms_Create_Fluid_Particle(DataType data,const Policy& pol) :Policy(pol),m_data(data.m_data), m_grid(m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(GetIsInboundNeedFilling(it.data()))
			{
				AddParticle(it.key());
				it.data().GetRef().SetLayer(0);
				it.data().GetRef().SetFluid();
			}
		}
	}
};

#endif
