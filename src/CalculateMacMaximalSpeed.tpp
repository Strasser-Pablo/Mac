/**
 * @file CalculateMacMaximalSpeed.tpp
 * @brief
 * Implementation file for class CalculateMacMaximalSpeed.
 **/

template <class TypeMacCell>
CalculateMacMaximalSpeed<TypeMacCell>::CalculateMacMaximalSpeed(const type_cell& fluid):m_max(0),m_fluid(fluid)
{
}

template <class TypeMacCell>
void CalculateMacMaximalSpeed<TypeMacCell>::operator()(const TypeMacCell & cell){
	type_cell c;
	cell.GetCellType(c);
	if(c!=m_fluid)
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

template <class TypeMacCell>
typename TypeMacCell::type_data CalculateMacMaximalSpeed<TypeMacCell>::GetResult(){
	return sqrt(m_max);
}