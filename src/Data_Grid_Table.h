#ifndef Data_Grid_Table_h
#define Data_Grid_Table_H

template<class Table>
class Data_Grid_Table : public Table
{
	public:
	typedef typename Table::type_data type_data_neigh;
	typedef typename Table::type_key type_data_key;
	static const int type_dim= type_data_key::type_dim;
	typedef typename type_data_neigh::type_data type_data_mac_cell;
	typedef typename type_data_mac_cell::type_data_value type_data_value;
	Data_Grid_Table(const Table& table) : Table(table)
	{
	}
}
;
#endif
