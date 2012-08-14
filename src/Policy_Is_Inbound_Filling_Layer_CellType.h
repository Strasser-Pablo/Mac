#ifndef Policy_Is_Inbound_Filling_Layer_CellType_H
#define Policy_Is_Inbound_Filling_Layer_CellType_H

template <typename Data>
class Policy_Is_Inbound_Filling_Layer_CellType
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	public:
	Policy_Is_Inbound_Filling_Layer_CellType()
	{
	}
	Policy_Is_Inbound_Filling_Layer_CellType(const Data& data __attribute__ ((unused)))
	{
	}
	static bool GetIsInboundNeedFilling(const type_neigh& neigh)
	{
		return neigh.CellType_GetRef().GetIsInflow()&&neigh.Layer_GetRef().GetIsLayerEmpty();
	}
};

#endif
