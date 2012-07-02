/**
 * @file CalculateTimeStep.tpp
 * @brief
 * Implementation file for class CalculateTimeStep.
 **/

template <class MacWorld,class TypeData,class TypeGetCellType>
CalculateTimeStepNonIso<MacWorld,TypeData,TypeGetCellType>::CalculateTimeStepNonIso(const MacWorld& world,const Physvector<type_dim,TypeData>& _1_h,TypeData& factor,TypeData& dt,TypeGetCellType &GetCellType):m_1_h(_1_h),m_factor(factor),m_dt(dt),m_world(world),m_GetCellType(GetCellType)
{
	
}

	template <class MacWorld,class TypeData,class TypeGetCellType>
void CalculateTimeStepNonIso<MacWorld,TypeData,TypeGetCellType>::Calculate()const
{
	CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell,TypeGetCellType> max(m_1_h,m_GetCellType);
	ApplyToEveryMacCell<CalculateMacMaximalSpeedNonIso<typename MacWorld::type_mac_cell,TypeGetCellType> ,MacWorld>(m_world,max);
	m_dt=m_factor/max.GetResult();
}