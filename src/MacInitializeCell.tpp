/**
 * @file MacInitializeCell.tpp
 * @brief 
 * Implementation file for class MacInitializeCell.
 **/

template<class TypeWorld,class TypeStagPos >
MacInitializeCell<TypeWorld,TypeStagPos>::MacInitializeCell(TypeWorld &world,type_cell &Fluid,type_cell& Air,Physvector<type_dim,type_data> & _1_h,Physvector<type_dim,type_data> &h,int level,TypeStagPos & stag_pos):mc_fluid(world,_1_h,h,Fluid,stag_pos),mc_init(world),mc_layer(world,Fluid,Air,level),mc_delete(world)
{
	
}

template<class TypeWorld,class TypeStagPos >
void MacInitializeCell<TypeWorld,TypeStagPos>::Update()
{
	mc_init.Update();
	mc_fluid.Update();
	mc_layer.Update();
	mc_delete.Update();
}

template<class TypeWorld,class TypeStagPos >
void MacInitializeCell<TypeWorld,TypeStagPos>::PrepareConstSpeed()
{
	mc_layer.PrepareConstSpeed();
}