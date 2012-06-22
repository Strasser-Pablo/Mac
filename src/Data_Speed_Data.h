#ifndef Data_Speed_Data_H
#define Data_Speed_Data_H
#include "Physvector.h"
#include "Data_Operation_Basic_Relation.h"
#include "Data_Operation_Vector_Arithmetic.h"

template <int Dim,typename TypeData>
class Data_Speed_Data;

template <int Dim,typename TypeData>
class Data_Speed_Get: private Data_Operation_Basic_Relation<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData> > , private Data_Operation_Vector_Arithmetic<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData>, TypeData >
{
	public:
	void Set(const Physvector<Dim,TypeData>& vect)
	{
		static_cast<Data_Speed_Data<Dim,TypeData>&>(*this).SetPhys(vect);
	}
	Physvector<Dim,TypeData> Get() const 
	{
		return static_cast<const Data_Speed_Data<Dim,TypeData>&>(*this).GetPhys();
	}
	friend Data_Operation_Basic_Relation<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData> >;
	friend Data_Operation_Vector_Arithmetic<Data_Speed_Data<Dim,TypeData>,Data_Speed_Get<Dim,TypeData>, TypeData >;
};

template <int Dim,typename TypeData>
class Data_Speed_Data : public Data_Speed_Get<Dim,TypeData>
{
	protected:
	void SetPhys(const Physvector<Dim,TypeData>& vect);
	 Physvector<Dim,TypeData> GetPhys() const;
	public:
	
	static const int type_dim=Dim;
	typedef TypeData type_data;
	Physvector<Dim,TypeData> m_speed;
	Data_Speed_Data()
	{
	}
	Data_Speed_Data(const Physvector<Dim,TypeData> & vect): m_speed(vect)
	{
	}

	void Set(int i,const TypeData& d);
	TypeData Get(int i) const;
	TypeData& GetRef(int i);
	friend Data_Speed_Get<Dim,TypeData>;
};
#include "Data_Speed_Data.tpp"
#endif
