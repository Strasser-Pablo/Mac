#ifndef Data_Grid_MacCell_H
#define Data_Grid_MacCell_H
template<typename Data>
class Data_Grid_MacCell : public  Data::type_Cell_type__InCell
{
	public:
		Data_Grid_MacCell(const Data& data) : Data::type_Cell_type__InCell(data.GetInCell())
		{
		}
};

#endif
