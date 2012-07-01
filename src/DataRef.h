#ifndef DataRef_H
#define DataRef_H

/**
 * @ingroup GR_Data
 * @brief
 * Class that Store a reference to it's template argument.
 * 
 * Usefull to have a handler to a shard data.
 *
 * @tparam Data Data to store a reference to.
 **/
template <typename Data>
struct DataRef
{
	/**
	 * @brief
	 * Reference to Data.
	 **/
	Data & m_data;
	/**
	 * @brief
	 * Type of stored data.
	 **/
	typedef Data type_data_struct;
	/**
	 * @brief
	 * Constructor
	 * @param data Data to store a reference to.
	 **/
	DataRef(Data& data):m_data(data)
	{
	}
};

#endif
