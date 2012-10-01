#ifndef Data_Grid_Speed_H
#define Data_Grid_Speed_H
#include "Data_Speed_Data.h"
/**
 * @ingroup GR_Data_Speed
 * @brief
 * This class store the speed on the grid.
 *
 * The following data are stored:
 * 	- The speed.
 * 	- The temporary speed.
 * 	- If one of the speed is constant.
 * 	- If all speed are constant.
 *
 * @pre
 * DataBase need to have a `type_dim` const int and a type_data_value type.
 *
 * @tparam DataBase Class storing basic information.
 **/
template <typename DataBase,typename Const>
class Data_Grid_Speed
{
	public:
	typedef Const type_const;
	/**
	 * @brief
	 * Dimension of the problem.
	 **/
	const static int type_dim=DataBase::type_dim;
	/**
	 * @brief
	 * Type of the numerical value.
	 **/
	typedef typename DataBase::type_data_value type_data_value;
	/**
	 * @brief
	 * Type for speed.
	 **/
	typedef Data_Speed_Data<type_dim,type_data_value> type_speed;
	/**
	 * @brief
	 * Type of this class.
	 **/
	typedef Data_Grid_Speed<DataBase,Const> type_cell_speed;
	/**
	 * @brief
	 * Indicate that this type exist for SFINAE.
	 **/
	typedef void type_cell_speed_exist;
	/**
	 * @brief
	 * The speed.
	 **/
	type_speed m_speed;
	/**
	 * @brief
	 * The constant vector.
	 **/
	Const& m_const;
	public:
	/**
	 * @brief
	 * Default construction with vector that is not constant.
	 **/
	Data_Grid_Speed(Const& _const): m_const(_const)
	{
	}

	Data_Grid_Speed(const Data_Grid_Speed<DataBase,Const> & cop,Const& _const) :m_speed(cop.m_speed),m_const(_const)
	{
	}
	/**
	 * @brief
	 * Set the ith element to be constant.
	 * @param i Position to set (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 **/
	void Set_Const(int i);
	/**
	 * @brief
	 * Set the ith element to be non constant.
	 * @param i Position to set (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 **/
	void Set_None_Const(int i);
	/**
	 * @brief
	 * Get the ith element constantness.
	 * @param i Position to set (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 * @return if value is constant.
	 **/
	bool Get_Const(int i) const;
	/**
	 * @brief
	 * Set the ith element of speed. If this element is constant, it will not be modified.
	 * @param i Position to set (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 * @param val Value to set speed to.
	 **/
	void Set(int i,const type_data_value& val,bool force=false);
	void SetZero(bool force=false);
	/**
	 * @brief
	 * Get the ith element of speed.
	 * @param i Position to get (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 * @return Speed of the given element.
	 **/
	auto __attribute__ ((pure)) Get(int i) const -> type_data_value ;
	/**
	 * @brief
	 * Get the speed vector.
	 * @return The speed vector.
	 **/
	auto Get() const -> type_speed;
	/**
	 * @brief
	 * Set the speed vector. If an element is constant, it will not be changed.
	 * @param val Value of speed to set.
	 **/
	void Set(const type_speed &val,bool force=false);
	/**
	 * @brief
	 * Set the ith element of temporary speed. If this element is constant, it will not be modified.
	 * @param i Position to set (from 1 to type_dim).
	 * @pre i need to be between 1 to type_dim. No checking is done.
	 * @param val Value to set temporary speed to.
	 **/
	/**
	 * @brief
	 * Get if one const
	 **/
	bool Is_One_Const() const;
	const Const& GetConstRef() const;
};
#include "Data_Grid_Speed.tpp"
#endif
