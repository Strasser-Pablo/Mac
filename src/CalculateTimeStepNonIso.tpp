/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData>
CalculateTimeStepNonIso<MacWorld,TypeData>::CalculateTimeStepNonIso(const Physvector<type_dim,TypeData>& _1_h,TypeData factor):m_1_h(_1_h),m_factor(factor)
{
	
}

	template <class MacWorld,class TypeData>
TypeData CalculateTimeStepNonIso<MacWorld,TypeData>::Calculate(const MacWorld &world)const
{
	CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell> max(m_1_h);
	ApplyToEveryMacCell<CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell> ,MacWorld>(world,max);
	return m_factor/max.GetResult();
}