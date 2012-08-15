#ifndef Policy_Von_Neumann_Boundary_H
#define Policy_Von_Neumann_Boundary_H

template<typename Data>
class Policy_Von_Neumann_Boundary
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	type_Data_Grid& m_grid;
	public:
	Policy_Von_Neumann_Boundary(Data& data) :m_grid(data.m_data.GetGridData())
	{
	}
	bool Get_Is_Von_Neumann_Boundary(type_neigh neigh,int i,int sign)
	{
		return m_grid.GetIsConstantInterface(neigh,i,sign);
	}
};

#endif
