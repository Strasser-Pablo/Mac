/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData>
CalculateTimeStep<MacWorld,TypeData>::CalculateTimeStep(const MacWorld &world,const TypeData &h,TypeData& factor,TypeData &dt,const type_cell &fluid):m_h(h),m_factor(factor),m_world(world),m_dt(dt),m_fluid(fluid)
{
	
}

	template <class MacWorld,class TypeData>
void CalculateTimeStep<MacWorld,TypeData>::Calculate()const
{
	CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> max(m_fluid);
	ApplyToEveryMacCell<CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> ,MacWorld>(m_world,max);
	m_dt=m_h*m_factor/max.GetResult();
}