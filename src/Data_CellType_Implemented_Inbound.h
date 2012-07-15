#ifndef Data_CellType_Implemented_Inbound_H
#define Data_CellType_Implemented_Inbound_H
#include "Data_CellType_Implemented_Fluid.h"
#include "Data_CellType_Implemented_Air.h"
#include "Data_CellType_SFINAE.h"

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid_Air
 * @brief
 * Enum Describing the Material_Fluid Type.
 **/
enum class Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid{Fluid,Air};

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid_Air
 * @brief
 * Trait class to send data to Data_CellType_Implemented_Fluid_Air.
 * Expect a type named Material_Type.
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template <typename Implementation>
struct Data_CellType_Implemented_Fluid_Air_Traits
{
};

template <typename Implementation>
class Data_CellType_Implemented_Fluid_Air; 

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid
 * @brief
 * Trait class to send data to Data_CellType_Implemented_Fluid.
 * Specialized for Data_CellType_Implemented_Fluid_Air.
 *
 * @pre
 * Implementation need to define the type `Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type`
 * 
 * @tparam Implementation an implementation that respect above condition.
 *
 * @sa Data_CellType_Implemented_Fluid
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template<typename Implementation>
struct Data_CellType_Implemented_Fluid_Traits<Data_CellType_Implemented_Fluid_Air<Implementation>,Implementation> 
{
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	static const Material_Type_Fluid m_fluid=Material_Type_Fluid::Fluid;
};

/**
 * @ingroup GR_Data_CellType_Implemented_Air
 * @brief
 * Trait class to send data to Data_CellType_Implemented_Air.
 * Specialized for Data_CellType_Implemented_Fluid_Air.
 *
 * @pre
 * Implementation need to define the type `Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type`
 * 
 * @tparam Implementation an implementation that respect above condition.
 *
 * @sa Data_CellType_Implemented_Air
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template<typename Implementation>
struct Data_CellType_Implemented_Air_Traits<Data_CellType_Implemented_Fluid_Air<Implementation>,Implementation> 
{
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	static const Material_Type_Fluid m_air=Material_Type_Fluid::Air;
};

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid_Air
 * @brief
 * Implementation class adding The abbility to check if it's air or fluid for a given Material Type.
 * This class is mean to serve as base class for an implementing class.
 *
 * The implementing class need to define the following method and class:
 * 	- Specialize the trait class Data_CellType_Implemented_Fluid_Air_Traits<Implementation> witch has a type named Material_Type.
 * 	- Have a method with signature compatible with `Material_Fluid_Type Material_To_Type_Fluid(Material_Type)` where Material_Fluid_Type is the type defined in this class.
 *
 * @tparam Implementation Class that is parent to this class and respect the condition given above.
 *
 **/
template <typename Implementation>
class Data_CellType_Implemented_Fluid_Air : public Data_CellType_Implemented_Fluid<Implementation,Data_CellType_Implemented_Fluid_Air<Implementation> > , public Data_CellType_Implemented_Air<Implementation,Data_CellType_Implemented_Fluid_Air<Implementation> > ,public Data_CellType_Implemented_Fluid_Air_Traits<Implementation>
{
	public:
	/**
	 * @brief
	 * Material Fluid Type used. 
	 **/
	typedef Data_CellType_Implemented_Fluid_Air_Material_Type_Fluid Material_Type_Fluid;
	/**
	 * @brief
	 * Material Type found from the Trait class.
	 **/
	typedef typename Data_CellType_Implemented_Fluid_Air_Traits<Implementation>::Material_Type Material_Type;
};

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid_Air
 * @brief
 * Implementation class adding The abbility to check if it's air or fluid for the current cell.
 * This class is mean to serve as base class for an implementing class.
 *
 * The implementing class need to define the following method and class:
 * 	- Have a member named m_data_cell_type:
 * 		- That has a method named GetIsAir and GetIsFluid:
 * 			- With as argument a member named m_mat.
 * 			- And with return type a boolean saying if it's fluid or not.
 *
 * @tparam Implementation Class that is parent to this class and respect the condition given above.
 *
 **/
template <typename Implementation,typename Base>
class Data_CellType_Implemented_Fluid_Air__InCell : public Data_CellType_Implemented_Fluid__InCell<Implementation> , public Data_CellType_Implemented_Air__InCell<Implementation> , public Data_CellType_Derivate_SFINAE<Base>
{
	public:
	template<typename T,typename Data_CellType_Constructor_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Implemented_Fluid_Air__InCell(const T& base):Data_CellType_Derivate_SFINAE<Base>(base)
	{
	}
	template<typename T,typename Data_CellType_Constructor_Not_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Implemented_Fluid_Air__InCell(const T& base __attribute__ ((unused)))
	{
	}
};

#endif
