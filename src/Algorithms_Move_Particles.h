#ifndef Algorithms_Move_Particles_H
#define Algorithms_Move_Particles_H

template <typename DataType,typename Policy>
class Algorithms_Move_Particles : public Policy
{
	using Policy::AdvanceSolveODE;
	using Policy::Get_Speed_Functor;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_particle_list::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	type_particle_list& m_list;
	type_Time_Type& m_dt;
	public:
	Algorithms_Move_Particles(DataType data,const Policy& pol): Policy(pol),m_list(data.m_data.GetTopologyData().GetRefToParticleList()),m_dt(data.m_data.GetTimingData().m_dt)
	{
	}
	void Do()
	{
		for(iterator it=m_list.begin();it!=m_list.end();++it)
		{
			this->AdvanceSolveODE((*it).GetParticlePosRef(),this->Get_Speed_Functor(),m_dt);
		}
	}
};
#endif
