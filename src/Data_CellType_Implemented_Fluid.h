#ifndef Data_CellType_Implemented_Fluid_H
#define Data_CellType_Implemented_Fluid_H

template<typename Parent,typename Implementation>
struct Data_CellType_Implemented_Fluid_Traits;

template <typename Implementation,typename Parent>
class Data_CellType_Implemented_Fluid
{
	typedef typename Data_CellType_Implemented_Fluid_Traits<Parent,Implementation>::Material_Type Material_Type;
	public:
	bool GetIsFluid(Material_Type c);
};

#include "Data_CellType_Implemented_Fluid.tpp"
#endif
