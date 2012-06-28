#ifndef Data_CellType_SFINAE_H
#define Data_CellType_SFINAE_H
template<typename Enable,typename Dummy=void>
class Data_CellType_Derivate_SFINAE
{
};


template<typename Enable>
class Data_CellType_Derivate_SFINAE<Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	public:
	Data_CellType_Derivate_SFINAE(const Enable &enable): Enable::type_Cell_type__InCell(enable)
	{
	}
};

template <typename Enable,typename Base,typename Dummy=void>
struct Data_CellType_Constructor_Derivate_SFINAE
{
	typedef void type2;
};

template <typename Enable>
struct Data_CellType_Constructor_Derivate_SFINAE<Enable,Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	typedef int type;
	typedef int type2;
};

template <typename Enable,typename Base,typename Dummy=void>
class Data_CellType_Constructor_Not_Derivate_SFINAE
{
};

template <typename Enable>
struct Data_CellType_Constructor_Not_Derivate_SFINAE<Enable,Enable,typename Data_CellType_Constructor_Derivate_SFINAE<Enable,Enable>::type2 >
{
	typedef int type;
};
#endif
