/**
 * @file MacInitializeCell4.tpp
 * @brief 
 * Implementation file for class MacInitializeCell3.
 **/

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate,class TypeOutput>
MacInitializeCell4<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate,TypeOutput>::MacInitializeCell4(TypeWorld &world,TypeGetCellType & GetCellType,Physvector<type_dim,type_data> & _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos,TypeCondPart &condpart,TypeFunctionPressure &func_pres,TypeExtrapolate &Extrap,TypeOutput &out):mc_fluid(world,_1_h,h,GetCellType,stag_pos,condpart),mc_init(world),mc_layer(world,GetCellType,level,func_pres,h,_1_h),mc_delete(world),m_Extrap(Extrap),m_out(out)
{
	
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate,class TypeOutput>
void MacInitializeCell4<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate,TypeOutput>::Update()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	mc_delete.Update();
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate,class TypeOutput>
void MacInitializeCell4<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate,TypeOutput>::PrepareConstSpeed(bool b)
{	
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	m_Extrap.Calculate(b);
	mc_delete.Update();
}
