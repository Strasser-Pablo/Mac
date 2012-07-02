/**
 * @file CalculateMacMaximalSpeed.tpp
 * @brief
 * Implementation file for class CalculateMacMaximalSpeed.
 **/

template <class TypeMacCell,class TypeGetCellType>
CalculateMacMaximalSpeed<TypeMacCell,TypeGetCellType>::CalculateMacMaximalSpeed(TypeGetCellType & GetCellType):m_max(0),m_GetCellType(GetCellType)
{
}

template <class TypeMacCell,class TypeGetCellType>
void CalculateMacMaximalSpeed<TypeMacCell,TypeGetCellType>::operator()(const TypeMacCell & cell){
	type_cell c;
	cell.GetCellType(c);
	if(!m_GetCellType.GetIsFluid(c))
	{
		return;
	}
	typename TypeMacCell::type_vector v;
	cell.GetSpeed(v);
	
	typename TypeMacCell::type_data temp=v.Norm2();
	if(temp>m_max){
		m_max=temp;
	}
}

template <class TypeMacCell,class TypeGetCellType>
typename TypeMacCell::type_data CalculateMacMaximalSpeed<TypeMacCell,TypeGetCellType>::GetResult(){
	return sqrt(m_max);
}