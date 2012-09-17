#ifndef Data_Grid_Layer_To_Delete_H
#define Data_Grid_Layer_To_Delete_H

template <typename Base>
class Data_Grid_Layer_To_Delete : public Base
{
	public:
	void SetLayerToDelete()
	{
		this->SetLayer(-2);
	}
	bool GetIsLayerToDelete() const
	{
		return this->GetLayer()==-2;
	}
	Data_Grid_Layer_To_Delete(const Base& base) :Base(base)
	{
	}
	Data_Grid_Layer_To_Delete()
	{
	}
	typedef Data_Grid_Layer_To_Delete<Base> type_cell_layer;
	typedef void type_cell_layer_exist;
};

#endif
