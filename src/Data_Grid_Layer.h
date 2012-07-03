#ifndef Data_Grid_Layer_H
#define Data_Grid_Layer_H

template <typename type_int>
class Data_Grid_Layer
{
	type_int m_layer;
	public:
	void SetLayer(type_int lay)
	{
		m_layer=lay;
	}
	type_int GetLayer() const
	{
		return m_layer;
	}
	Data_Grid_Layer()
	{
	}

	Data_Grid_Layer(int lay) : m_layer(lay)
	{
	}
	typedef Data_Grid_Layer<type_int> type_cell_layer;
	typedef void type_cell_layer_exist;
};

#endif
