#ifndef Policy_Is_Inbound_Filling_Layer_H
#define Policy_Is_Inbound_Filling_Layer_H

template <typename Data>
class Policy_Is_Inbound_Filling_Layer
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_key type_data_key;
	typedef typename type_Data_Grid::type_data_key_value type_data_key_value;
	typedef typename type_Data_Grid::type_data_neigh type_data;
	static const int type_dim=type_Data_Grid::type_dim;
	public:
	Policy_Is_Inbound_Filling_Layer()
	{
	}
	Policy_Is_Inbound_Filling_Layer(const Data& data __attribute__ ((unused)))
	{
	}
	static bool GetIsInboundNeedFilling(const type_data& data)
	{
		return data.GetRef().GetIsInbound()&&data.GetRef().GetIsLayerEmpty();
	}
};

#endif
