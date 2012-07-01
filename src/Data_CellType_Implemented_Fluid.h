#ifndef Data_CellType_Implemented_Fluid_H
#define Data_CellType_Implemented_Fluid_H

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid
 * @brief
 * Trait class to send data to Data_CellType_Implemented_Fluid.
 *
 * Specialisation need to give:
 * 	- A type named Material_Type.
 * 	- A value of type Material_Type_Fluid m_fluid.
 *
 * @sa Data_CellType_Implemented_Fluid
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template<typename Parent,typename Implementation>
struct Data_CellType_Implemented_Fluid_Traits
{
};

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid
 * @brief
 * This Class implement a Method `GetIsFluid`.
 *
 * The parameter to this class are given from a trait class Data_CellType_Implemented_Fluid_Traits.
 *
 * @pre
 * Implementation and Parent couple need to define the trait class.
 * Implementation need to define a Material_To_Type_Fluid method with as argument a Material_Type, and as return value a Material_Fluid_Type.
 * The Type of this Method need to be compatible with the type in the trait class.
 *
 * @tparam Implementation class needed to Implement.
 * @tparam Parent another type used only for trait class acess.
 * @sa Data_CellType_Implemented_Fluid_Traits
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template <typename Implementation,typename Parent>
class Data_CellType_Implemented_Fluid
{
	/*
	 * @brief
	 * Material Type Type.
	 **/
	typedef typename Data_CellType_Implemented_Fluid_Traits<Parent,Implementation>::Material_Type Material_Type;
	public:
	/**
	 * @brief
	 * Return if it's Fluid or not.
	 * @param c Material_Type to test.
	 * @return return if it's Fluid.
	 **/
	bool GetIsFluid(Material_Type c) const;
};

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid
 * @brief
 * This Class implement a Method `GetIsFluid` for the current cell.
 *
 * @pre
 * The implementing class need to define the following method and class:
 * 	- Have a member named m_data_cell_type:
 * 		- That has a method named GetIsFluid:
 * 			- With as argument a member named m_mat.
 * 			- And with return type a boolean saying if it's fluid or not.
 *
 * @tparam Implementation that respect the above condition.
 * @sa Data_CellType_Implemented_Air_Traits
 * @sa Data_CellType_Implemented_Fluid_Air
 **/
template <typename Implementation>
class Data_CellType_Implemented_Fluid__InCell
{
	public:
	/**
	 * @brief
	 * Return if the current cell is Fluid or not.
	 * @return return if it's Fluid.
	 **/
	bool GetIsFluid() const;
};
#include "Data_CellType_Implemented_Fluid.tpp"
#endif
