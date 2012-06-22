#ifndef Data_CellType_Implemented_Fluid_Air_H
#define Data_CellType_Implemented_Fluid_Air_H
#include "Data_CellType_Implemented_Fluid.h"
#include "Data_CellType_Implemented_Air.h"

enum class Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid{Fluid,Air};

template <typename Implementation>
struct Data_CellType_Implemented_Fluid_Air_Traits;

template <typename Implementation>
class Data_CellType_Implemented_Fluid_Air; 

template<typename Implementation>
struct Data_CellType_Implemented_Fluid_Traits<Data_CellType_Implemented_Fluid_Air<Implementation>,Implementation> 
{
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	static const Material_Type_Fluid m_fluid=Material_Type_Fluid::Fluid;
};

template<typename Implementation>
struct Data_CellType_Implemented_Air_Traits<Data_CellType_Implemented_Fluid_Air<Implementation>,Implementation> 
{
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	static const Material_Type_Fluid m_air=Material_Type_Fluid::Air;
};

template <typename Implementation>
class Data_CellType_Implemented_Fluid_Air : public Data_CellType_Implemented_Fluid<Implementation,Data_CellType_Implemented_Fluid_Air<Implementation> > , public Data_CellType_Implemented_Air<Implementation,Data_CellType_Implemented_Fluid_Air<Implementation> > ,public Data_CellType_Implemented_Fluid_Air_Traits<Implementation>
{
	public:
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
};


template <typename Implementation>
class Data_CellType_Implemented_Fluid_Air__InCell : public Data_CellType_Implemented_Fluid__InCell<Implementation,typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type> , public Data_CellType_Implemented_Air__InCell<Implementation,typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type>
{
};

#endif
