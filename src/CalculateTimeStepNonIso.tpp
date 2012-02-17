/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData>
CalculateTimeStepNonIso<MacWorld,TypeData>::CalculateTimeStepNonIso(const MacWorld& world,const Physvector<type_dim,TypeData>& _1_h,TypeData& factor,TypeData& dt):m_1_h(_1_h),m_factor(factor),m_dt(dt),m_world(world)
{
	
}

	template <class MacWorld,class TypeData>
void CalculateTimeStepNonIso<MacWorld,TypeData>::Calculate()const
{
	CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell> max(m_1_h);
	ApplyToEveryMacCell<CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell> ,MacWorld>(m_world,max);
	m_dt=m_factor/max.GetResult();
}