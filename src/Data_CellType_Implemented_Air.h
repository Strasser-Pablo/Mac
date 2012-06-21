#ifndef Data_CellType_Implemented_Air_H
#define Data_CellType_Implemented_Air_H

template<typename Parent,typename Implementation>
struct Data_CellType_Implemented_Air_Traits;

template <typename Implementation,typename Parent>
class Data_CellType_Implemented_Air
{
	typedef typename Data_CellType_Implemented_Fluid_Traits<Parent,Implementation>::Material_Type Material_Type;
	public:
	bool GetIsAir(Material_Type c);
};

#include "Data_CellType_Implemented_Air.tpp"
#endif