#ifndef Inversible_Value_Base_H
#define Inversible_Value_Base_H

/**
 * @ingroup GR_Inversible_Value
 * @brief
 * This base class is mean to be derived. And contain the common interface
 * to all derivation. The goal of this class is to provide a value that can be inversed, and allow to store the two value consistantly.
 *
 * The inverse value will always be correct.
 *
 * @pre
 * Parent need to define a method with name Inverse.
 * That calculate the inverse of the data given as argument.
 *
 * @tparam Data data type that is stored.
 * @tparam Parent parent class that implement the calculation of the inverse.
 **/
template <class Data,class Parent>
class Inversible_Value_Base
{
	/**
	 * @brief
	 * Data
	 **/
	Data m_data;
	/**
	 * @brief
	 * Inverse of the Data.
	 **/
	Data m_1_data;
	protected:
	/**
	 * @brief
	 * Calculate the inverse of the data, using the parent Inverse method.
	 * @param data Data to inverse.
	 * @return Inverse value.
	 **/
	Data Inverse_Abstract(const Data& data)
	{
		return static_cast<Parent&>(*this).Inverse(data);
	}
	public:
	/**
	 * @brief
	 * Default constructor.
	 **/
	Inversible_Value_Base()
	{

	}
	/**
	 * @brief
	 * Constructor.
	 * @param data Initial value to be constructed.
	 **/
	Inversible_Value_Base(const Data & data)
	{
		m_data=data;
		m_1_data=Inverse_Abstract(data);
	}
	/**
	 * @brief
	 * Return the Value.
	 * @return Return the value.
	 **/
	Data Get() const
	{
		return m_data;
	}
	/**
	 * @brief
	 * Return the inverse of Value.
	 * @return Return the inverse of value.
	 **/
	Data Get_Inv() const
	{
		return m_1_data;
	}
	/**
	 * @brief
	 * Set the value to data.
	 * @param data Value to set.
	 **/
	void Set(Data data)
	{
		m_data=data;
		m_1_data=Inverse_Abstract(m_data);
	}
	/**
	 * @brief
	 * Set the value to the inverse of data.
	 * @param data Inverse Value to set.
	 **/
	void Set_Inv(Data data)
	{
		m_data=Inverse_Abstract(m_data);
		m_1_data=data;
	}
	/**
	 * @brief Type of Data.
	 **/
	typedef Data type_data;
};
#endif
