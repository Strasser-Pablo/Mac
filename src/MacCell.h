#include "Physvector.h"
#ifndef MacCell_H
#define MacCell_H

#include <iostream>
#include <boost/serialization/nvp.hpp>
using namespace std;
/**
 * @file MacCell.h
 * @brief 
 * Declaration file for class MacCell.
 **/
/**
 * @ingroup GR_Cell
 * @brief
 * Represent a MAC Cell.
 * @tparam DIM Dimension of the space.
 * @tparam TypeData for numerical data (double,float).
 * @tparam TypeCell type of data for cell (enum, class etc)
 * @tparam ID an ID differencing different group of Cell.
 * Used so that static member can be different.
 **/
template <int DIM,class TypeData, class TypeCell,int ID=0>
class MacCell{
	Physvector<DIM,TypeData> m_speed;
	Physvector<DIM,TypeData> m_speedTemp;
	TypeData m_pressure;
        TypeData m_div;	
	TypeData m_circulation;
	TypeCell m_cell_type;
	bool m_const_speed[DIM];
	bool m_one_const;
	int m_layer;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
	static int m_nb_const_speed;
public:
/**
 * @brief 
 * Get the number of constspeed for all cell with the same id.
 * The value that we get is a upper bound.
 **/
	static int GetNBConstSpeed();
/**
 * @brief
 * Type of the data (float, double).
 **/
typedef TypeData type_data;
/**
 * @brief
 * Type of the cell (int, enum etc).
 **/
typedef TypeCell type_cell;
/**
 * @brief
 * Type used for vector.
 **/
typedef Physvector<DIM,TypeData> type_vector;
/**
 * @brief
 * Dimension of the vector.
 **/
static const int type_dim=DIM;
	/**
	 * @brief
	 * Default Constructor.
	 **/
	MacCell();
	/**
	 * @brief
	 * Constructor for a given speed and pressure.
	 * @param speed Initial speed.
	 * @param pressure Initial pressure.
	 * @param layer Layer used in different algorithm.
	 **/
	MacCell(Physvector<DIM,TypeData> &speed,const TypeData& pressure,const int layer=-1);
	
	/**
	 * @brief
	 * Constructor for a given speed and pressure and cell type.
	 * @param speed Initial speed.
	 * @param pressure Initial pressure.
	 * @param type Initial cell type.
	 * @param layer Layer used in different algorithm.
	 **/
	MacCell(Physvector<DIM,TypeData> &speed,const TypeData& pressure,const TypeCell & type,const int layer=-1);
	/**
	 * @brief
	 * Default Destructor.
	 **/
	~MacCell();
	void SetCirculation(const TypeData &circulation);
	void GetCirculation(TypeData & Circulation);
	/**
	 * @brief
	 * Set the speed.
	 * @param speed Speed value to set to.
	 **/
	void SetSpeed(Physvector<DIM,TypeData> &speed);
	/**
	 * @brief
	 * Get the speed.
	 * @param speed Speed value returned.
	 **/
	void GetSpeed(Physvector<DIM,TypeData> &speed) const;
	/**
	 * @brief
	 * Set the speed of a given component.
	 * @param i Component to set.
	 * @param speed_comp Value to set to.
	 **/
	void SetInterSpeed(int i,TypeData &speed_comp);
	/**
	 * @brief
	 * Get the speed of a given component.
	 * @param i Component to set.
	 * @param speed_comp Reference to set to the value of the speed component.
	 **/
	void GetInterSpeed(int i,TypeData &speed_comp);
	/**
	 * @brief
	 * Set the temporary speed.
	 * @param speed Temporary Speed value to set to.
	 **/
	void SetTempSpeed(Physvector<DIM,TypeData> &speed);
	/**
	 * @brief
	 * Get the Temporary Speed.
	 * @param speed Temporary Speed value returned.
	 **/
	void GetTempSpeed(Physvector<DIM,TypeData> &speed);
	/**
	 * @brief
	 * Set the temporary speed of a given component.
	 * @param i Component to set.
	 * @param speed_comp Value to set to.
	 **/
	void SetInterTempSpeed(int i,TypeData &speed_comp);
	/**
	 * @brief
	 * Get the temporary speed of a given component.
	 * @param i Component to set.
	 * @param speed_comp Reference to set to the value of the temporary speed component.
	 **/
	void GetInterTempSpeed(int i,TypeData &speed_comp);
	/**
	 * @brief Assign Temporary value to Speed.
	 **/
	void TempToSpeed();
	/**
	 * @brief Assign Speed value to Temporary.
	 **/
	void SpeedToTemp();
	/**
	 * @brief
	 * Set Pressure Value.
	 * @param pressure Value to set to.
	 **/
	void SetPressure(const TypeData &  pressure);
	/**
	 * @brief
	 * Get Pressure Value.
	 * @param pressure Value returned.
	 **/
	void GetPressure(TypeData & pressure);
	/**
	 * @brief
	 * Set Div Value.
	 * @param Div Value to set to.
	 **/
	void SetDivergence(const TypeData &  Div);
	/**
	 * @brief
	 * Get Div Value.
	 * @param Div Value returned.
	 **/
	void GetDivergence(TypeData & Div);
	/**
	 * @brief 
	 * Set the cell type.
	 * @param type Cell type to set to.
	 **/
	void SetCellType(const TypeCell&  type);
	/**
	 * @brief 
	 * Get the cell type.
	 * @param type Cell type returned.
	 **/
	void GetCellType(TypeCell & type) const ;
	
	/**
	 * @brief
	 * Set the value of the layer.
	 * @param layer Value to set.
	 **/
	void SetLayer(const int layer);
	/**
	 * @brief
	 * Get the value of the layer.
	 * @param layer Reference to set to the given layer.
	 **/
	void GetLayer(int &layer) const ;
	/**
	 * @brief
	 * Set the given component to constant speed.
	 * @param i Component to set.
	 * @param b Boolean if we set to constant speed or not.
	 **/
	void SetConstSpeed(int i,bool b);
	/**
	 * @brief
	 * Get the given component constant speed value.
	 * @param i Component to get.
	 * @param b Reference to the value where to put the value.
	 **/
	void GetConstSpeed(int i,bool &b);
};

#include "MacCell.tpp"
#endif
