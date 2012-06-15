template <class TypeWorld>
GetCellType_Base<TypeWorld>::GetCellType_Base(type_input_struct in):m_world(in.m_world),m_default(in.m_default)
{
}

template <class TypeWorld>
auto GetCellType_Base<TypeWorld>::KeyToType(const type_key & key)-> type_cell
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return c;
	}
	return m_default;
}
