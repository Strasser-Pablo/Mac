/**
 * @file MacInitializeCell.tpp
 * @brief 
 * Implementation file for class MacInitializeCell.
 **/

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure >
MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure>::MacInitializeCell(TypeWorld &world,TypeGetCellType & GetCellType,Physvector<type_dim,type_data> & _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos,TypeCondPart &condpart,TypeFunctionPressure &func_pres):mc_fluid(world,_1_h,h,GetCellType,stag_pos,condpart),mc_init(world),mc_layer(world,GetCellType,level,func_pres),mc_delete(world)
{
	
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure >
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure>::Update()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	mc_delete.Update();
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType,class TypeCondPart,class TypeFunctionPressure >
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType,TypeCondPart,TypeFunctionPressure>::PrepareConstSpeed()
{
	mc_layer.PrepareConstSpeed();
}