/**
 * @file CalculateMacMaximalSpeed.tpp
 * @brief
 * Implementation file for class CalculateMacMaximalSpeed.
 **/

template <class TypeMacCell,class TypeGetCellType>
CalculateMacMaximalSpeedNonIso<TypeMacCell,TypeGetCellType>::CalculateMacMaximalSpeedNonIso(const Physvector<type_dim,type_data> & _1_h,TypeGetCellType & GetCellType):m_max(0),m_1_h(_1_h),m_GetCellType(GetCellType)
{
}

template <class TypeMacCell,class TypeGetCellType>
void CalculateMacMaximalSpeedNonIso<TypeMacCell,TypeGetCellType>::operator()(const TypeMacCell & cell){
	type_cell c;
	cell.GetCellType(c);
	if(!m_GetCellType.GetIsFluid(c))
	{
		return;
	}
	typename TypeMacCell::type_vector v;
	cell.GetSpeed(v);
	for(int i=1;i<=type_dim;++i)
	{
		v.GetRef(i)*=m_1_h.Get(i);
	}
	typename TypeMacCell::type_data temp=v.Norm2();
	if(temp>m_max){
		m_max=temp;
	}
}

template <class TypeMacCell,class TypeGetCellType>
typename TypeMacCell::type_data CalculateMacMaximalSpeedNonIso<TypeMacCell,TypeGetCellType>::GetResult(){
	return sqrt(m_max);
}