#ifndef Policy_Advance_Ode_RungeKutta_H
#define Policy_Advance_Ode_RungeKutta_H

template <typename Data>
class Policy_Advance_Ode_RungeKutta
{
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle type_particle;
	typedef typename type_particle::type_data_vector type_data_vector;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	public:
	template <typename Functor>
	void AdvanceSolveODE(type_data_vector& pos,Functor speed,type_Time_Type dt)
	{
		type_data_vector res=pos;
		type_data_vector k=dt*speed(pos);
		res+=(1./6.)*k;
		k=dt*speed(pos+k*0.5);
		res+=(1./3.)*k;
		k=dt*speed(pos+k*0.5);
		res+=(1./3.)*k;
		k=dt*speed(pos+k);
		res+=(1./6.)*k;
		pos=res;
	}
};
#endif
