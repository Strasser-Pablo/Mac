#ifndef Data_CellType_Const_Inbound_H
#define Data_CellType_Const_Inbound_H

template <typename Base>
class Data_CellType_Const_Inbound : public Base
{
	public:
	typedef Data_CellType_Const_Inbound<Base> type_cell_speed;
	typedef void type_cell_speed_exist;
	bool GetIsInbound() const
	{
		return this->Speed_Is_One_Const();
	}
	Data_CellType_Const_Inbound(const Base& base) : Base(base)
	{
	}
	Data_CellType_Const_Inbound()
	{
	}
};

#endif
