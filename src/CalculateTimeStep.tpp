/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData>
CalculateTimeStep<MacWorld,TypeData>::CalculateTimeStep(const MacWorld &world,const TypeData &h,TypeData& factor,TypeData &dt):m_h(h),m_factor(factor),m_world(world),m_dt(dt)
{
	
}

	template <class MacWorld,class TypeData>
void CalculateTimeStep<MacWorld,TypeData>::Calculate()const
{
	CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> max;
	ApplyToEveryMacCell<CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> ,MacWorld>(m_world,max);
	m_dt=m_h*m_factor/max.GetResult();
}