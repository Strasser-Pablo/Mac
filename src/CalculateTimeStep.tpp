/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData>
CalculateTimeStep<MacWorld,TypeData>::CalculateTimeStep(const TypeData &h,TypeData factor):m_h(h),m_factor(factor)
{
	
}

	template <class MacWorld,class TypeData>
TypeData CalculateTimeStep<MacWorld,TypeData>::Calculate(const MacWorld &world)const
{
	CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> max;
	ApplyToEveryMacCell<CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell> ,MacWorld>(world,max);
	return m_h*m_factor/max.GetResult();
}