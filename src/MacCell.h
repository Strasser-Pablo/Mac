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
 * @brief
 * Represent a MAC Cell.
 * @tparam DIM Dimension of the space.
 * @tparam TypeData for numerical data (double,float).
 * @tparam TypeCell type of data for cell (enum, class etc)
 **/
template <int DIM,class TypeData, class TypeCell,int ID=0>
class MacCell{
	Physvector<DIM,TypeData> m_speed;
	Physvector<DIM,TypeData> m_speedTemp;
	TypeData m_pressure; 
	TypeCell m_cell_type;
	bool m_const_speed[DIM];
	bool m_one_const;
	int m_layer;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
	static int m_nb_const_speed;
public:
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
	 **/
	MacCell(Physvector<DIM,TypeData> &speed,const TypeData& pressure,const int layer=-1);
	
	/**
	 * @brief
	 * Constructor for a given speed and pressure and cell type.
	 * @param speed Initial speed.
	 * @param pressure Initial pressure.
	 * @param type Initial cell type.
	 **/
	MacCell(Physvector<DIM,TypeData> &speed,const TypeData& pressure,const TypeCell & type,const int layer=-1);
	/**
	 * @brief
	 * Default Destructor.
	 **/
	~MacCell();
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
	void SetInterSpeed(int i,TypeData &speed_comp);
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
	void SetInterTempSpeed(int i,TypeData &speed_comp);
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
	
	void SetLayer(const int layer);
	void GetLayer(int &layer) const ;
	void SetConstSpeed(int i,bool b);
	void GetConstSpeed(int i,bool &b);
};

#include "MacCell.tpp"
#endif
