#ifndef Data_Pressure_Data_H
#define Data_Pressure_Data_H
#include "Data_Operation_Scalar_Relation.h"
#include "Data_Operation_Scalar_Arithmetic.h"

/**
 * @ingroup GR_Data_Pressure
 * @brief
 * This class store the pressure as a scalar data with normal arithmetic operation.
 * The use of a special type for pressure allow to ensure type safety.
 *
 * @pre
 * TypeData need to be an arithmetic type. Normaly will be a type like double or float.
 * @tparam TypeData data type to use. 
 **/
template <typename TypeData>
class Data_Pressure_Data : private Data_Operation_Scalar_Relation<Data_Pressure_Data<TypeData>, Data_Pressure_Data<TypeData> >, private Data_Operation_Scalar_Arithmetic<Data_Pressure_Data<TypeData> ,Data_Pressure_Data<TypeData> >
{
	public:
	/**
	 * @brief
	 * Data Type.
	 **/	
	typedef TypeData type_data;
	/**
	 * @brief
	 * Stored Data.
	 **/
	TypeData m_pres;
	/**
	 * @brief
	 * Default constructor.
	 **/
	Data_Pressure_Data()
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @param pres Initial pressure.
	 **/
	Data_Pressure_Data(const TypeData & pres):m_pres(pres)
	{
	}
	/**
	 * @brief
	 * Operator to convert to TypeData if asked explicitly.
	 **/
	explicit operator TypeData();
	/**
	 * @brief
	 * Method to get the value.
	 * @return Return the pressure.
	 **/
	TypeData Get() const __attribute__ ((pure));
	/**
	 * @brief
	 * Set the value.
	 * @param pres Value to set to.
	 **/
	void Set(const TypeData & pres);
};

#include "Data_Pressure_Data.tpp"
#endif
