#ifndef Data_Grid_MacCell_H
#define Data_Grid_MacCell_H

template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_InCell
{
};

template <typename Enable>
struct Data_Grid_MacCell_InCell<Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	Data_Grid_MacCell_InCell(const Enable& base) :  Enable::type_Cell_type__InCell(base)
	{
	}
};


template <typename Enable,typename Base,typename Dummy=void>
struct Data_Grid_MacCell_InCell2
{
	typedef void type2;
};

template <typename Enable>
struct Data_Grid_MacCell_InCell2<Enable,Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	typedef int type;
	typedef int type2;
};

template <typename Enable,typename Base,typename Dummy=void>
class Data_Grid_MacCell_InCell3
{
};

template <typename Enable>
struct Data_Grid_MacCell_InCell3<Enable,Enable,typename Data_Grid_MacCell_InCell2<Enable,Enable>::type2 >
{
	typedef int type;
};

template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_cell_speed
{
};

template <typename Enable>
struct Data_Grid_MacCell_cell_speed<Enable,typename Enable::type_cell_speed_exist> : public Enable::type_cell_speed
{
};


template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_cell_DataBase
{
};

template <typename Enable>
struct Data_Grid_MacCell_cell_DataBase<Enable,typename Enable::type_Mac_DataBase_Exist> : public Enable::type_Mac_DataBase
{
	Data_Grid_MacCell_cell_DataBase(const Enable& base):Enable::type_Mac_DataBase(base)
	{
	}
};

template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_cell_pressure
{
};

template <typename Enable>
struct Data_Grid_MacCell_cell_pressure<Enable,typename Enable::type_cell_pressure_exist> : public Enable::type_cell_pressure
{
};

template<typename Data>
class Data_Grid_MacCell : public Data_Grid_MacCell_InCell<Data>, public Data_Grid_MacCell_cell_speed<Data> , public Data_Grid_MacCell_cell_pressure<Data>, public Data_Grid_MacCell_cell_DataBase<Data>
{
	public:
		template<typename T,typename Data_Grid_MacCell_InCell2<T,Data>::type =0>
		Data_Grid_MacCell(const T & data) : Data_Grid_MacCell_InCell<Data>(data),Data_Grid_MacCell_cell_DataBase<Data>(data)
		{
		}
		template<typename T,typename Data_Grid_MacCell_InCell3<T,Data>::type =0>
		Data_Grid_MacCell(const T & data) : Data_Grid_MacCell_cell_DataBase<Data>(data)
		{
		}
		typedef typename Data::type_data_value type_data_value;
};

#endif
