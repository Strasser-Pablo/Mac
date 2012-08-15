#ifndef Data_Staggered_Left_H
#define Data_Staggered_Left_H

/**
 * @ingroup GR_DataBase_Topology
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class, type doesnt exist if we are not staggered left and int otherwise.
 * To be exact, type doesn't exist if type_staggered_pos_left is not defined in a type name type_data_mac_cell in Base.
 *
 * @tparam Enable A template type to be determine.
 * @tparam Base Class to check if staggered.
 * @tparam Type If found, Enable will be determine to value Type.
 * @tparam dummy if void the class work correctly, in the contrary only this version is instantiated.
 **/
template<typename Enable,typename Base,typename Type,typename dummy=void>
class Is_Staggered_Left_SFINAE
{
	public:
};

/**
 * @ingroup GR_DataBase_Topology
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class, type doesnt exist if we are not staggered left and int otherwise.
 * To be exact, type doesn't exist if type_staggered_pos_left is not defined in a type name type_data_mac_cell in Base.
 *
 * @tparam Enable A template type to be determine.
 * @tparam Base Class to check if staggered.
 * @tparam Type If found, Enable will be determine to value Type.
 * @tparam dummy if void the class work correctly, in the contrary only this version is instantiated.
 **/
template<typename Base,typename Type>
class Is_Staggered_Left_SFINAE<Type,Base,Type,typename Base::type_staggered_pos_left>
{
	public:
	/**
	 * @brief
	 * type That is defined only if Staggered Left.
	 **/
	typedef int type;
};

/**
 * @ingroup GR_DataBase_Topology
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class, type doesn't exist if we are not staggered and int otherwise.
 * To be exact, type doesn't exist if type_staggered_pos is not defined in a type name type_data_mac_cell in Base.
 *
 * @tparam Enable A template type to be determine.
 * @tparam Base Class to check if staggered.
 * @tparam Type If found, Enable will be determine to value Type.
 * @tparam dummy if void the class work correctly, in the contrary only this version is instantiated.
 **/
template<typename Enable,typename Base,typename Type,typename dummy=void>
class Is_Staggered_SFINAE
{
};

/**
 * @ingroup GR_DataBase_Topology
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class, type doesn't exist if we are not staggered and int otherwise.
 * To be exact, type doesn't exist if type_staggered_pos is not defined in a type name type_data_mac_cell in Base.
 *
 * @tparam Enable A template type to be determine.
 * @tparam Base Class to check if staggered.
 * @tparam Type If found, Enable will be determine to value Type.
 * @tparam dummy if void the class work correctly, in the contrary only this version is instantiated.
 **/
template<typename Base,typename Type>
class Is_Staggered_SFINAE<Type,Base,Type,typename Base::type_staggered_pos>
{
	public:
	/**
	 * @brief
	 * type That is defined only if Staggered Left.
	 **/
	typedef int type;
};

/**
 * @ingroup GR_DataBase_Topology
 * @brief
 * Indicate that the topology is a stagered left grid.
 * This is a grid where the pressure is at center and the speed on the boundary.
 *
 * @tparam Base Base class to use.
 **/
template <typename Base>
class Data_Staggered_Left : public Base
{
	public:
	/**
	 * @brief
	 * Indicate that this a staggered grid type.
	 * The value is not used only the existance of void type is important.
	 * It's used in SFINAE method.
	 **/
	typedef void type_staggered_pos;
	/**
	 * @brief
	 * Indicate that this a staggered grid with speed at left or below.
	 * The value is not used only the existance of void type is important.
	 * It's used in SFINAE method.
	 **/
	typedef void type_staggered_pos_left;
	/**
	 * @brief
	 * Constructor that derivate with the argument.
	 * @param base element with witch we derivate.
	 **/
	Data_Staggered_Left(const Base & base):Base(base)
	{
	}
	/**
	 * @brief
	 * Default constructor.
	 **/
	Data_Staggered_Left()
	{
	}
};

#endif 
