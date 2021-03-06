/**
 * @file MacInitializeCell.tpp
 * @brief 
 * Implementation file for class MacInitializeCell.
 **/

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate>
MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate>::MacInitializeCell(TypeWorld &world,TypeGetCellType & GetCellType,Physvector<type_dim,type_data> & _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos,TypeCondPart &condpart,TypeFunctionPressure &func_pres,TypeExtrapolate &Extrap):mc_init(world),mc_fluid(world,_1_h,h,GetCellType,stag_pos,condpart),mc_layer(world,GetCellType,level,func_pres),mc_delete(world),m_Extrap(Extrap)
{
	
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate>
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate>::Update()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	mc_delete.Update();
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure,class TypeExtrapolate>
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure,TypeExtrapolate>::PrepareConstSpeed()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	m_Extrap.Calculate(false);
	mc_delete.Update();
}
