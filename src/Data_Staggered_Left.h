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
class Is_Staggered_Left_SFINAE<Type,Base,Type,typename Base::type_data_mac_cell::type_staggered_pos_left>
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
class Is_Staggered_SFINAE<Type,Base,Type,typename Base::type_data_mac_cell::type_staggered_pos>
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
	/**
	 * @brief
	 * Type where the base class of this class has as new base InheritedWith
	 * @tparam InheritedWith Class to inherit with.
	 **/
	template <typename InheritedWith>
	using type_DataBase_SubInherite=Data_Staggered_Left<typename Base::template type_DataBase_SubInherite<InheritedWith> >;
	/**
	 * @brief
	 * Type pointing to the base type without additional inheritance.
	 * Because after addition of additional base class we are of this class but with another template value, we need this type to know the type.
	 **/
	typedef Data_Staggered_Left<typename Base::type_SubInherite_Base> type_SubInherite_Base;
	/**
	 * @brief
	 * Constructor used to created a inherited base class.
	 * @tparam InheritedWith Class to inherit with.
	 * @param base element of type before transformation.
	 * @param in elememnt of type witch will be the new base class.
	 **/
	template<typename InheritedWith> 
	Data_Staggered_Left(const  type_SubInherite_Base& base, const InheritedWith& in): Base(base,in)
	{
	}
};

#endif 
