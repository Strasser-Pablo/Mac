#ifndef Data_Grid_Depth_H
#define Data_Grid_Depth_H

template <typename type_int>
class Data_Grid_Depth
{
	type_int m_depth;
	public:
	void SetDepth(type_int depth)
	{
		m_depth=depth;
	}
	type_int GetDepth() const
	{
		return m_depth;
	}
	Data_Grid_Depth()
	{
	}

	Data_Grid_Depth(int depth) : m_depth(depth)
	{
	}
	typedef Data_Grid_Depth<type_int> type_cell_depth;
	typedef type_int type_depth_value;
	typedef void type_cell_depth_exist;
};

#endif
