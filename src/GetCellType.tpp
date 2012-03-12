template <class TypeWorld>
GetCellType<TypeWorld>::GetCellType(TypeWorld& world,const type_cell &fluid,const type_cell &boundary_fluid, const type_cell &air,const type_cell &boundary_air,const type_data &rho_fluid,const type_data &rho_air,const type_data &_1_rho_fluid,const type_data &_1_rho_air,const type_data &rho_inter,const type_data& _1_rho_inter,const type_data &rho_inter_bound,const type_data& _1_rho_inter_bound )
:m_fluid(fluid),m_air(air),m_boundary_fluid(boundary_fluid),m_boundary_air(boundary_air),m_rho_air(rho_air),m_rho_fluid(rho_fluid),m_1_rho_air(_1_rho_air),m_1_rho_fluid(_1_rho_fluid),m_1_rho_inter(_1_rho_inter),m_rho_inter(rho_inter),m_world(world),m_rho_inter_bound(rho_inter_bound),m_1_rho_inter_bound(_1_rho_inter_bound)
{
	
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluid(const type_cell & cell)
{
	return GetIsFluidOnly(cell)||GetIsBoundaryFluid(cell);
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAir(const type_cell & cell)
{
	return GetIsAirOnly(cell)||GetIsBoundaryAir(cell);
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluidOnly(const type_cell & cell)
{
	return m_fluid==cell;
}
template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAirOnly(const type_cell & cell)
{
	return m_air==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryAir(const type_cell & cell)
{
	return m_boundary_air==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryFluid(const type_cell & cell)
{
	return m_boundary_fluid==cell;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundary(const type_cell & cell)
{
	return GetIsBoundaryFluid(cell)||GetIsBoundaryAir(cell);
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluid(const type_key & key)
{
	if(m_world.m_mac_grind.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsFluid(c);
	}
	return false;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAir(const type_key & key)
{
	if(m_world.m_mac_grind.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsAir(c);
	}
	return true;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsFluidOnly(const type_key & key)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsFluidOnly(c);
	}
	return false;
}
template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsAirOnly(const type_key & key)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsAirOnly(c);
	}
	return true;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryAir(const type_key & key)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsBoundaryAir(c);
	}
	return false;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundaryFluid(const type_key & key)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsBoundaryFluid(c);
	}
	return false;
}

template <class TypeWorld>
bool GetCellType<TypeWorld>::GetIsBoundary(const type_key & key)
{
	if(m_world.m_mac_grid.Exist(key))
	{
		type_cell c;
		m_world.m_mac_grid[key].GetCellType(c);
		return GetIsBoundary(c);
	}
	return false;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetFluid()
{
	return m_fluid;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetAir()
{
	return m_air;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetFluidBoundary()
{
	return m_boundary_fluid;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_cell & GetCellType<TypeWorld>::GetAirBoundary()
{
	return m_boundary_air;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetFluidRho()
{
	return m_rho_fluid;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetFluid1_Rho()
{
	return m_1_rho_fluid;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetAirRho()
{
	return m_rho_air;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetAir1_Rho()
{
	return m_1_rho_air;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetInterRho()
{
	return m_rho_inter;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetInter1_Rho()
{
	return m_1_rho_inter;
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetInterBoundRho()
{
	return m_rho_inter_bound;
}
template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetInterBound1_Rho()
{
	return m_1_rho_inter_bound;
}
template <class TypeWorld>
Type_Inter GetCellType<TypeWorld>::GetInter(const type_key & key1,const type_key &key2)
{
	if(GetIsFluidOnly(key1)&&GetIsFluidOnly(key2))
	{
		return Type_Inter::Fluid_Fluid; 
	}
	if(GetIsAirOnly(key1)&&GetIsAirOnly(key2))
	{
		return Type_Inter::Air_Air;
	}
	if((GetIsFluidOnly(key1)&&GetIsAirOnly(key2))||(GetIsFluidOnly(key2)&&GetIsAirOnly(key1)))
	{
		return Type_Inter::Fluid_Air;
	}
	if(GetIsBoundaryAir(key1)&&GetIsBoundaryAir(key2))
	{
		return Type_Inter::Air_Boundary_Air_Boundary;
	}
	if((GetIsFluidOnly(key1)&&GetIsBoundaryAir(key2))||(GetIsFluidOnly(key2)&&GetIsBoundaryAir(key1)))
	{
		return Type_Inter::Fluid_Air_Boundary;
	}
	throw logic_error("GetInter is not of a know type");
}

template <class TypeWorld>
Type_Inter GetCellType<TypeWorld>::GetInter(const type_key & key1,int i,int sign)
{
	type_key key2=key1;
	key2.Set(i,key2.Get(i)+sign);
	return GetInter(key1,key2);
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::GetRhoInter(const type_key & key1,const type_key &key2)
{
	switch(GetInter(key1,key2))
	{
		case Type_Inter::Fluid_Fluid:
			return m_rho_fluid;
		case Type_Inter::Air_Air:
			return m_rho_air;
		case Type_Inter::Fluid_Air:
			return m_rho_inter;
		case Type_Inter::Fluid_Air_Boundary:
			return m_rho_inter_bound;
		case Type_Inter::Air_Boundary_Air_Boundary:
			return m_rho_air;
	}
}

template <class TypeWorld>
const  typename GetCellType<TypeWorld>::type_data& GetCellType<TypeWorld>::GetRhoInter(const type_key &key1,int i,int sign)
{
	type_key key2=key1;
	key2.Set(i,key1.Get(i)+sign);
	return GetRhoInter(key1,key2);
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data& GetCellType<TypeWorld>::Get1_RhoInter(const type_key & key1,const type_key &key2)
{
	switch(GetInter(key1,key2))
	{
		case Type_Inter::Fluid_Fluid:
			return m_1_rho_fluid;
		case Type_Inter::Air_Air:
			return m_1_rho_air;
		case Type_Inter::Fluid_Air:
			return m_1_rho_inter;
		case Type_Inter::Fluid_Air_Boundary:
			return m_1_rho_inter_bound;
		case Type_Inter::Air_Boundary_Air_Boundary:
			return m_1_rho_air;
	}
}

template <class TypeWorld>
const typename GetCellType<TypeWorld>::type_data & GetCellType<TypeWorld>::Get1_RhoInter(const type_key &key1,int i,int sign)
{
	type_key key2=key1;
	key2.Set(i,key1.Get(i)+sign);
	return Get1_RhoInter(key1,key2);
}
