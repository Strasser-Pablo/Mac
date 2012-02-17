template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
MacMoveParticle<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::MacMoveParticle(TypeWorld & world,TypeMethod &method,TypeGetSpeed & GetSpeed,type_data & dt):m_world(world),m_ode(m_pos,m_functor,0,method),m_functor(GetSpeed),m_dt(dt)
{
	
}

template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
void MacMoveParticle<TypeWorld,TypeMethod,TypeGetSpeed,TypeGetStagSpeedPos>::Calculate()
{
	for(typename TypeWorld::type_tablecontainer::iterator it= m_world.m_particle_list.begin();it!=m_world.m_particle_list.end();++it)
	{
		(*it).GetPos(m_pos);
		m_ode.Calculate(m_dt);
		(*it).SetPos(m_pos);
	}
}