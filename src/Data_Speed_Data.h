#ifndef Data_Speed_Data_H
#define Data_Speed_Data_H
#include "Physvector.h"
#include "Data_Operation_Basic_Relation.h"
#include "Data_Operation_Vector_Arithmetic.h"

template <int Dim,typename TypeData>
class Data_Speed_Data;

/**
 * @ingroup GR_Data_Speed 
 * @brief
 * Class to Set and Get underlying Physvector.
 *
 * @tparam Dim Dimension of the vector.
 * @tparam TypeData Data in the vector.
 **/
template <int Dim,typename TypeData>
class Data_Speed_Get: private Data_Operation_Basic_Relation<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData> > , private Data_Operation_Vector_Arithmetic<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData>, TypeData >
{
	public:
	/**
	 * @brief
	 * Set the vector.
	 * @param vect Vector to set to.
	 **/
	void Set(const Physvector<Dim,TypeData>& vect)
	{
		static_cast<Data_Speed_Data<Dim,TypeData>&>(*this).SetPhys(vect);
	}
	/**
	 * @brief
	 * Get the vector.
	 * @return Get the vector.
	 **/
	Physvector<Dim,TypeData> Get() const 
	{
		return static_cast<const Data_Speed_Data<Dim,TypeData>&>(*this).GetPhys();
	}
	friend Data_Operation_Basic_Relation<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData> >;
	friend Data_Operation_Vector_Arithmetic<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData>, TypeData >;
};

/**
 * @ingroup GR_Data_Speed 
 * @brief
 * Class to store Speed in a grid.
 *
 * @tparam Dim Dimension of the vector.
 * @tparam TypeData Data in the vector.
 **/
template <int Dim,typename TypeData>
class Data_Speed_Data : public Data_Speed_Get<Dim,TypeData>
{
	protected:
	/**
	 * @brief
	 * Set the underlying Vector type.
	 * @param vect Vector to set.
	 **/
	void SetPhys(const Physvector<Dim,TypeData>& vect);
	/**
	 * @brief
	 * Get the underlying Vector type.
	 * @return Vector type.
	 **/
	 Physvector<Dim,TypeData> GetPhys() const;
	public:
	
	/**
	 * @brief
	 * Dimension of the problem.
	 **/
	static const int type_dim=Dim;
	/**
	 * @brief
	 * Type of the data.
	 **/
	typedef TypeData type_data;
	/**
	 * @brief
	 * Speed vector.
	 **/
	Physvector<Dim,TypeData> m_speed;
	/**
	 * @brief
	 * Default constructor.
	 **/
	Data_Speed_Data()
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @param vect Initial value of speed.
	 **/
	Data_Speed_Data(const Physvector<Dim,TypeData> & vect): m_speed(vect)
	{
	}

	/**
	 * @brief
	 * Set the ith component to the given value.
	 * @param i component de set between 1 and dim.
	 * @param d value to set to.
	 **/
	void Set(int i,const TypeData& d);
	/**
	 * @brief
	 * Get the ith component to the given value.
	 * @param i component de get between 1 and dim.
	 * @return Value to get.
	 **/
	TypeData Get(int i) const;
	/**
	 * @brief
	 * Get the ith component to the given value.
	 * @param i component de get between 1 and dim.
	 * @return Reference value to get.
	 **/
	TypeData& GetRef(int i);
	friend Data_Speed_Get<Dim,TypeData>;
};
#include "Data_Speed_Data.tpp"
#endif
