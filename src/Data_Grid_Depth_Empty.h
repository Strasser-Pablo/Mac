#ifndef Data_Grid_Depth_Empty_H
#define Data_Grid_Depth_Empty_H

template <typename Base>
class Data_Grid_Depth_Empty : public Base
{
	public:
	void SetDepthEmpty()
	{
		this->SetDepth(-1);
	}
	bool GetIsDepthEmpty() const
	{
		return this->GetDepth()==-1;
	}
	Data_Grid_Depth_Empty(const Base& base) :Base(base)
	{
	}
	Data_Grid_Depth_Empty()
	{
	}
	typedef Data_Grid_Depth_Empty<Base> type_cell_depth;
	typedef void type_cell_depth_exist;
};

#endif
