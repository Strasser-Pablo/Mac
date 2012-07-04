#ifndef Data_Grid_Table_h
#define Data_Grid_Table_H

/**
 * @ingroup GR_Data_Grid
 * @brief
 * This uttility class define some type from base class.
 * It's mean to be used above an hookable table.
 * That contain as type an Neighbour_List with as Data an MacCell.
 * @pre
 * The following type need to be accessible from Table:
 * 	- type_data with an Neighbour_Type.
 * 	- type_data_key with the key to acess the table,
 * 	- type_dim int type_data_key the dimension of the problem.
 * 	- type_data in type_data_key where it's a MacCell.
 * 	- type_data_value in type_data in type_data_key.
 *
 * @tparam Table table to construct Data_Grid_Table on.
 **/
template<class Table>
class Data_Grid_Table : public Table
{
	public:
	/**
	 * @brief
	 * Type of neighbour type
	 **/
	typedef typename Table::type_data type_data_neigh;
	/**
	 * @brief
	 * Type of neighbour type
	 **/
	typedef typename Table::type_key type_data_key;
	typedef typename type_data_key::type_data type_data_key_value;
	/**
	 * @brief
	 * Dimension of the problem
	 **/
	static const int type_dim= type_data_key::type_dim;
	/**
	 * @brief
	 * Type of MacCell.
	 **/
	typedef typename type_data_neigh::type_data type_data_mac_cell;
	/**
	 * @brief
	 * Type of numerical type.
	 **/
	typedef typename type_data_mac_cell::type_data_value type_data_value;
	typedef typename type_data_mac_cell::type_data_vector type_data_vector;
	/**
	 * @brief
	 * Constructor.
	 * @param table Table to copy and inherith with.
	 **/
	Data_Grid_Table(const Table& table) : Table(table)
	{
	}
}
;
#endif
