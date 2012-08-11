#ifndef Data_Grid_CellType_To_Grid_CellType_H
#define Data_Grid_CellType_To_Grid_CellType_H
template<typename CellType>
class Data_Grid_CellType_To_Grid_CellType : public CellType::type_Cell_type__InCell
{
	public:
	Data_Grid_CellType_To_Grid_CellType(const CellType& type ):CellType::type_Cell_type__InCell(type)
	{
	}
};

#endif
