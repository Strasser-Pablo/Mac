#ifndef Data_Grid_MacCell_H
#define Data_Grid_MacCell_H

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_Cell_type__InCell` only if `Enable::type_Cell_type__InCell_exist` exist. 
 * This is the base class where we do not derivate.
 **/
template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_InCell
{
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_Cell_type__InCell` only if `Enable::type_Cell_type__InCell_exist` exist. 
 * This is the base class where we derivate.
 **/
template <typename Enable>
struct Data_Grid_MacCell_InCell<Enable,typename Enable::type_Cell_type__InCell_exist> : public Enable::type_Cell_type__InCell
{
	/**
	 * @brief
	 * Constructor
	 * @param base Base to copy from.
	 **/
	Data_Grid_MacCell_InCell(const Enable& base) :  Enable::type_Cell_type__InCell(base)
	{
	}
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class where type `type` and `type2` have value int only if Enable and Base are the same and `Enable::type_Cell_type__InCell_exist`.
 * Otherwise only type `type2` is defined to void.
 * This is the second case.
 **/
template <typename Enable,typename Base,typename Dummy=void>
struct Data_Grid_MacCell_InCell2
{
	typedef void type2;
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class where type `type` and `type2` have value int only if Enable and Base are the same and `Enable::type_Cell_type__InCell_exist`.
 * Otherwise only type `type2` is defined to void.
 * This is the first case.
 **/
template <typename Enable>
struct Data_Grid_MacCell_InCell2<Enable,Enable,typename Enable::type_Cell_type__InCell_exist>
{
	typedef int type;
	typedef int type2;
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class where type `type` have value int only if Enable and Base are the same and `Enable::type_Cell_type__InCell_exist does not exist`.
 * Otherwise no type is defined.
 * This is the first case.
 **/
template <typename Enable,typename Base,typename Dummy=void>
class Data_Grid_MacCell_InCell3
{
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class where type `type` have value int only if Enable and Base are the same and `Enable::type_Cell_type__InCell_exist does not exist`.
 * Otherwise no type is defined.
 * This is the first case.
 **/
template <typename Enable>
struct Data_Grid_MacCell_InCell3<Enable,Enable,typename Data_Grid_MacCell_InCell2<Enable,Enable>::type2 >
{
	typedef int type;
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_cell_speed` only if `Enable::type_cell_speed_exist` exist. 
 * This is the base class where we do not derivate.
 **/
template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_cell_speed
{
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_cell_speed` only if `Enable::type_cell_speed_exist` exist. 
 * This is the base class where we derivate.
 **/
template <typename Enable>
struct Data_Grid_MacCell_cell_speed<Enable,typename Enable::type_cell_speed_exist> : public Enable::type_cell_speed
{
};


/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_Mac_DataBase` only if `Enable::type_Mac_DataBase_Exist` exist. 
 * This is the base class where we do not derivate.
 **/
template <typename Enable,typename Dummy=void>
struct Data_Grid_MacCell_cell_DataBase
{
	Data_Grid_MacCell_cell_DataBase(const Enable& base)
	{
	}
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_Mac_DataBase` only if `Enable::type_Mac_DataBase_Exist` exist. 
 * This is the base class where we derivate.
 **/
template <typename Enable>
struct Data_Grid_MacCell_cell_DataBase<Enable,typename Enable::type_Mac_DataBase_Exist> : public Enable::type_Mac_DataBase
{
	/**
	 * @brief
	 * Constructor
	 * @param base Instance to copy.
	 **/
	Data_Grid_MacCell_cell_DataBase(const Enable& base):Enable::type_Mac_DataBase(base)
	{
	}
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_cell_pressure` only if `type_cell_pressure_exist` exist. 
 * This is the base class where we do not derivate.
 **/
template <typename Enable,typename Dummy=void>
class Data_Grid_MacCell_cell_pressure
{
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @ingroup GR_SFINAE
 * @brief
 * SFINAE class that derivate from `Enable::type_cell_pressure` only if `type_cell_pressure_exist` exist. 
 * This is the base class where we derivate.
 **/
template <typename Enable>
struct Data_Grid_MacCell_cell_pressure<Enable,typename Enable::type_cell_pressure_exist> : public Enable::type_cell_pressure
{
};

/**
 * @ingroup GR_Data_Grid_MacCell
 * @brief
 * Class aggregating other class to define a Cell.
 *
 * This class will derive from the class given by the following type if they exist in the Data Argument:
 * 	- `type_Cell_type__InCell`
 * 	- `type_cell_speed`
 * 	- `type_cell_pressure`
 *
 * 	The following type is needed `type_Mac_DataBase`.
 * 	@tparam Data Class formed by combination of class (by mean of Datas for example).
 **/
template<typename Data>
class Data_Grid_MacCell : public Data_Grid_MacCell_InCell<Data>, public Data_Grid_MacCell_cell_speed<Data> , public Data_Grid_MacCell_cell_pressure<Data>, public Data_Grid_MacCell_cell_DataBase<Data>
{
	public:
		/**
		 * @brief
		 * Constructor in the case that we derivate from Data_Grid_MacCell_InCell.
		 * @tparam T this type is used for SFINAE if the function is activated it's value is Data.
		 * @param data a Data instance.
		 **/
		template<typename T,typename Data_Grid_MacCell_InCell2<T,Data>::type =0>
		Data_Grid_MacCell(const T & data) : Data_Grid_MacCell_InCell<Data>(data),Data_Grid_MacCell_cell_DataBase<Data>(data)
		{
		}
		/**
		 * @brief
		 * Constructor in the case that we do not derivate from Data_Grid_MacCell_InCell.
		 * @tparam T this type is used for SFINAE if the function is activated it's value is Data.
		 * @param data a Data instance.
		 **/
		template<typename T,typename Data_Grid_MacCell_InCell3<T,Data>::type =0>
		Data_Grid_MacCell(const T & data) : Data_Grid_MacCell_cell_DataBase<Data>(data)
		{
		}
};

#endif
