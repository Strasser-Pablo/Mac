/**
 * @file CalculateMacMaximalSpeed.tpp
 * @brief
 * Implementation file for class CalculateMacMaximalSpeed.
 **/

template <class TypeMacCell>
CalculateMacMaximalSpeedNonIso<TypeMacCell>::CalculateMacMaximalSpeedNonIso(const Physvector<type_dim,type_data> & _1_h,const type_cell & fluid):m_max(0),m_1_h(_1_h),m_fluid(fluid)
{
}

template <class TypeMacCell>
void CalculateMacMaximalSpeedNonIso<TypeMacCell>::operator()(const TypeMacCell & cell){
	type_cell c;
	cell.GetCellType(c);
	if(c!=m_fluid)
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

template <class TypeMacCell>
typename TypeMacCell::type_data CalculateMacMaximalSpeedNonIso<TypeMacCell>::GetResult(){
	return sqrt(m_max);
}