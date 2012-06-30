template <class TypeWorld>
GetCellType_Base<TypeWorld>::GetCellType_Base(type_input_struct in):m_default(in.m_default),m_world(in.m_world)
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

template <class TypeWorld>
bool GetCellType_Base<TypeWorld>::KeyToMacCell(const type_key & key,type_mac_cell & mac)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		mac=m_world.m_mac_grid[key];
		return true;
	}
	return false;
}

template <class TypeWorld>
bool GetCellType_Base<TypeWorld>::KeyToMacCellAndType(const type_key & key,type_mac_cell & mac,type_cell& c)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		mac=m_world.m_mac_grid[key];
		mac.GetCellType(c);
		return true;
	}
	c=m_default;
	return false;
}

template <class TypeWorld>
bool GetCellType_Base<TypeWorld>::KeyToSignDiff(const type_key & key1,const type_key &key2,int& sign,int& dim)
{
	type_key dif=key2-key1;
	bool b=false;
	for(int i=1;i<=type_dim;++i)
	{
		sign=dif.Get(i);
		if(sign!=0)
		{
			dim=i;
			if(b)
			{
				return false;
			}
			else
			{
				b=true;
			}
		}
	}
	return true;
}

template <class TypeWorld>
void GetCellType_Base<TypeWorld>::SignDiffToKey(const type_key & key1,type_key &key2,const int sign,const int dim)
{
	key2=key1;
	key2.GetRef(dim)+=sign;
}
