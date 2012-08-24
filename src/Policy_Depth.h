#ifndef Policy_Depth_H
#define Policy_Depth_H

template< typename Data>
class Policy_Depth
{
	typedef typename Data::type_data_struct::type_Data_Grid::type_data::type_depth::type_depth_value type_depth_value;
	const type_depth_value m_depth_max;
	const type_depth_value m_depth_interior;
	const type_depth_value m_depth_remove;
	public:
	Policy_Depth(const type_depth_value& max,const type_depth_value& interior,const type_depth_value remove):m_depth_max(max),m_depth_interior(interior),m_depth_remove(remove)
	{
	}
	type_depth_value GetDepthMax()
	{
		return m_depth_max;
	}
	type_depth_value GetDepthInterior()
	{
		return m_depth_interior;
	}
	type_depth_value GetDepthRemoveParticle()
	{
		return m_depth_remove;
	}
};

#endif
