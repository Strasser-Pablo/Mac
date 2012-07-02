#ifndef Data_CellType_SFINAE_H
#define Data_CellType_SFINAE_H
/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will derivate with `Enable::type_Cell_type__InCell` if `Enable::type_Cell_type__InCell_exist` exist.
 * This class is the case when the condition is not respected.
 * @tparam Enable Base class to test.
 * @tparam Dummy This is a Dummy type, if this is not void only this class will be selected.
 **/
template<typename Enable,typename Dummy=void>
class Data_CellType_Derivate_SFINAE
{
};

/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will derivate with `Enable::type_Cell_type__InCell` if `Enable::type_Cell_type__InCell_exist` exist.
 * This class is the case when the condition is respected.
 * @tparam Enable Base class to test.
 * @tparam Dummy This is a Dummy type, if this is not void this class will not be selected.
 **/
template<typename Enable>
class Data_CellType_Derivate_SFINAE<Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	public:
	Data_CellType_Derivate_SFINAE(const Enable &enable): Enable::type_Cell_type__InCell(enable)
	{
	}
};

/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will define type `type` and `type2` to `int` only if `Enable::type_Cell_type__InCell_exist` exist and if Base and Enable are the same.
 * Otherwise only `type2` will be define to void.
 * This class is the case when the condition is not respected.
 * @tparam Enable value of the template to be determine.
 * @tparam Base Base class.
 * @tparam Dummy This is a Dummy type, if this is not void only this class will be selected.
 **/
template <typename Enable,typename Base,typename Dummy=void>
struct Data_CellType_Constructor_Derivate_SFINAE
{
	/**
	 * @brief
	 * This type defined to void is used to detect the else case.
	 **/
	typedef void type2;
};

/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will define type `type` and `type2` to `int` only if `Enable::type_Cell_type__InCell_exist` exist and if Base and Enable are the same.
 * Otherwise only `type2` will be define to void.
 * This class is the case when the condition is respected.
 * @tparam Enable value of the template to be determine.
 * @tparam Base Base class.
 * @tparam Dummy This is a Dummy type, if this is not void only this class will be selected.
 **/
template <typename Enable>
struct Data_CellType_Constructor_Derivate_SFINAE<Enable,Enable,typename Enable::type_Cell_type__InCell_exist>
{
	/**
	 * @brief
	 * This type is only defined in this case.
	 **/
	typedef int type;
	/**
	 * @brief
	 * This type has value int only in this case. 
	 **/
	typedef int type2;
};

/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will define type `type` to `int` only if `Enable::type_Cell_type__InCell_exist` don't exist and if Base and Enable are the same.
 * Otherwise no type will be defined.
 * This class is the case when the condition is respected.
 * @tparam Enable value of the template to be determine.
 * @tparam Base Base class.
 * @tparam Dummy This is a Dummy type, if this is not void only this class will be selected.
 **/
template <typename Enable,typename Base,typename Dummy=void>
class Data_CellType_Constructor_Not_Derivate_SFINAE
{
};

/**
 * @ingroup GR_SFINAE
 * @ingroup GR_Data_CellType
 * @brief
 * This SFINAE class will define type `type` and `type2` to `int` only if `Enable::type_Cell_type__InCell_exist` exist.
 * Otherwise no type will be defined.
 * This class is the case when the condition is not respected.
 * @tparam Enable value of the template to be determine.
 * @tparam Base Base class.
 * @tparam Dummy This is a Dummy type, if this is not void only this class will be selected.
 **/
template <typename Enable>
struct Data_CellType_Constructor_Not_Derivate_SFINAE<Enable,Enable,typename Data_CellType_Constructor_Derivate_SFINAE<Enable,Enable>::type2 >
{
	/**
	 * @brief
	 * This Type has value int only in this case.
	 **/
	typedef int type;
};
#endif
