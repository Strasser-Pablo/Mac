/**
 * @file MacInitializeCell.tpp
 * @brief 
 * Implementation file for class MacInitializeCell.
 **/

template<class TypeWorld,class TypeStagPos,class TypeGetCellType >
MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType>::MacInitializeCell(TypeWorld &world,TypeGetCellType & GetCellType,Physvector<type_dim,type_data> & _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos):mc_fluid(world,_1_h,h,GetCellType,stag_pos),mc_init(world),mc_layer(world,GetCellType,level),mc_delete(world)
{
	
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType >
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType>::Update()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	mc_delete.Update();
}

template<class TypeWorld,class TypeStagPos,class TypeGetCellType >
void MacInitializeCell<TypeWorld,TypeStagPos,TypeGetCellType>::PrepareConstSpeed()
{
	mc_layer.PrepareConstSpeed();
}