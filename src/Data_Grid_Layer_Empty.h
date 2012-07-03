#ifndef Data_Grid_Layer_Empty_H
#define Data_Grid_Layer_Empty_H

template <typename Base>
class Data_Grid_Layer_Empty : public Base
{
	public:
	void SetLayerEmpty()
	{
		this->SetLayer(-1);
	}
	bool GetIsLayerEmpty() const
	{
		return this->GetLayer()==-1;
	}
	Data_Grid_Layer_Empty(const Base& base) :Base(base)
	{
	}
	Data_Grid_Layer_Empty()
	{
	}
	typedef Data_Grid_Layer_Empty<Base> type_cell_layer;
	typedef void type_cell_layer_exist;
};

#endif
