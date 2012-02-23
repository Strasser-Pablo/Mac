/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData,class TypeGetCellType>
CalculateTimeStep<MacWorld,TypeData,TypeGetCellType>::CalculateTimeStep(const MacWorld &world,const TypeData &h,TypeData& factor,TypeData &dt,TypeGetCellType &GetCellType):m_h(h),m_factor(factor),m_world(world),m_dt(dt),m_GetCellType(GetCellType)
{
	
}

	template <class MacWorld,class TypeData,class TypeGetCellType>
void CalculateTimeStep<MacWorld,TypeData,TypeGetCellType>::Calculate()const
{
	CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell,TypeGetCellType> max(m_GetCellType);
	ApplyToEveryMacCell<CalculateMacMaximalSpeed<typename MacWorld::type_mac_cell,TypeGetCellType> ,MacWorld>(m_world,max);
	m_dt=m_h*m_factor/max.GetResult();
}