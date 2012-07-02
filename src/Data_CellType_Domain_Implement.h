#ifndef Data_CellType_Domain_Implement_H
#define Data_CellType_Domain_Implement_H
#include "Data_CellType_SFINAE.h"

/**
 * @ingroup GR_Data_CellType_Domain_Implement
 * @ingroup GR_Traits
 * @brief
 * Trait class to send data for Data_CellType_Domain_Implement.
 * @pre
 * Specialisation need to define a Material_Type variable.
 * @tparam Implementation implementation that will be called for some key method.
 * @tparam Base base class.
 **/
template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement_Trait
{
};

/**
 * @ingroup GR_Data_CellType_Domain_Implement
 * @brief
 * Implementation class for the method GetIsInDomain.
 * The type Material_Type are send by traits class.
 *
 * @pre
 * Traits class that define the type Material_Type.
 * Implementation that define a method GetIsInDomain_Impl.
 * @tparam Implementation implementation to use.
 * @tparam Base base class to derivate with.
 **/
template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement : public Base
{
	/**
	 * @brief
	 * Type of Material.
	 **/
	typedef typename Data_CellType_Domain_Implement_Trait<Implementation,Base>::Material_Type Material_Type;
	public:
	/**
	 * @brief
	 * Return is it's in Domain.
	 * The actual calculation depend of the implementation class.
	 * @param mat Material to test.
	 **/
	bool GetIsInDomain(const Material_Type mat) const
	{
		return static_cast<const Implementation&> (*this).GetIsInDomain_Impl(mat);
	}
	/**
	 * @brief
	 * Constructor.
	 * @param base Base class to copy.
	 **/
	Data_CellType_Domain_Implement(const Base & base): Base(base)
	{
	}
};

/**
 * @ingroup GR_Data_CellType_Domain_Implement
 * @brief
 * Implementation class for the method GetIsInDomain.
 * The type Material_Type are send by traits class.
 * This is the InCell version of the class.
 * It will correctly inherite the base class to be InCell to.
 * @pre
 * Traits class that define the type Material_Type.
 * Implementation that define a method GetIsInDomain_Impl.
 * @tparam Implementation implementation to use.
 * @tparam Base base class to derivate with.
 **/
template <typename Implementation,typename Base>
class Data_CellType_Domain_Implement__InCell : public Data_CellType_Derivate_SFINAE<Base>
{
	/**
	 * @brief
	 * Type of Material.
	 **/
	typedef typename Data_CellType_Domain_Implement_Trait<Implementation,Base>::Material_Type Material_Type;
	public:
	/**
	 * @brief
	 * Return if it's in domain. Will uttilize the implementation to do the calculation.
	 * @return Return if it's in domain.
	 **/
	bool GetIsInDomain() const
	{
		return static_cast<const Implementation&> (*this).GetIsInDomain_Impl();
	}
	/**
	 * @brief
	 * Constructor. This constructor will be choosen by SFINAE if we have an InCell parent class.
	 * It will then correctly create the incell Parent.
	 * @param base Base class instance copy.
	 * @tparam T template type that will be equal to Base if we have a match.
	 **/
	template<typename T,typename Data_CellType_Constructor_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Domain_Implement__InCell(const T & base): Data_CellType_Derivate_SFINAE<Base>(base)
	{
	}
	/**
	 * @brief
	 * Constructor. This constructor will be choosen by SFINAE if we have not an InCell parent class.
	 * @param base Base class instance copy.
	 * @tparam T template type that will be equal to Base if we have a match.
	 **/
	template<typename T,typename Data_CellType_Constructor_Not_Derivate_SFINAE<T,Base>::type =0>
	Data_CellType_Domain_Implement__InCell(const T & base)
	{
	}
};
#endif
