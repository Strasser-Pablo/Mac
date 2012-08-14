#ifndef Policy_Layer_Max_H
#define Policy_Layer_Max_H

template< typename Data>
class Policy_Layer_Max
{
	typedef typename Data::type_data_struct::type_Data_Grid::type_data::type_layer::type_layer_value type_layer_value;
	const type_layer_value m_layer_max;
	public:
	Policy_Layer_Max(const type_layer_value& max):m_layer_max(max)
	{
	}
	type_layer_value GetLayerMax()
	{
		return m_layer_max;
	}
};

#endif
