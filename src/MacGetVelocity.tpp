
/**
 * @file MacGetVelocity.tpp
 * @brief
 * Implementation file for class MacGetVelocity.
 **/

template <class TypeWorld,class TypeStagPos>
MacGetVelocity<TypeWorld,TypeStagPos>::MacGetVelocity(TypeWorld &world,TypeStagPos& stag_pos,const Physvector<type_dim,type_data> &_1_h ):m_Interp(world,_1_h),m_stag_pos(stag_pos)
{
}

template <class TypeWorld,class TypeStagPos>
 Physvector< MacGetVelocity<TypeWorld,TypeStagPos>::type_dim,typename MacGetVelocity<TypeWorld,TypeStagPos>::type_data> MacGetVelocity<TypeWorld,TypeStagPos>::Get(const Physvector<type_dim,type_data> &pos)
{
	Physvector<type_dim,type_data> v2;
	for(int i=1;i<=type_dim;i++){
	v2.Set(i,m_Interp.Calculate(m_stag_pos.GetCorrectLow(pos,i) ,i));
	}
	return v2;
}