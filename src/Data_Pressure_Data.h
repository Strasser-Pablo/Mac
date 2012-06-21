#ifndef Data_Pressure_Data_H
#define Data_Pressure_Data_H
#include "Data_Operation_Scalar_Relation.h"
template <typename TypeData>
class Data_Pressure_Data : private Data_Operation_Scalar_Relation<Data_Pressure_Data<TypeData>, Data_Pressure_Data<TypeData> >
{
	public:
	TypeData m_pres;
	Data_Pressure_Data(TypeData & pres):m_pres(pres)
	{
	}
	Data_Pressure_Data(TypeData && pres):m_pres(pres)
	{
	}
	explicit operator TypeData();
	TypeData Get() const;
	void Set(const TypeData & pres);
};

#include "Data_Pressure_Data.tpp"
#endif