#ifndef GetCellType_Air_H
#define GetCellType_Air_H
#include "Inversible_Value.h"
#include "GetCellType_Air_Base.h"

template <class TypeWorld,class Base>
struct GetCellType_Air_Argument
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename Base::type_input_struct type_sub_struct;
	type_sub_struct m_base;
	const type_cell &m_air;
	const Inversible_Value<type_data>& m_rho;
	GetCellType_Air_Argument(type_sub_struct base,const type_cell &air,const Inversible_Value<type_data>& rho):m_base(base),m_air(air),m_rho(rho)
	{
	}
};

template <class TypeWorld,class Base>
class GetCellType_Air : public GetCellType_Air_Base<TypeWorld,Base,GetCellType_Air<TypeWorld,Base> >
{
	public:
	typedef GetCellType_Air_Argument<TypeWorld,Base> type_input_struct;
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	const type_cell &m_air;
	const Inversible_Value<type_data>& m_rho; 
	public:
	GetCellType_Air(type_input_struct in);
	bool GetIsAir_Implementation(const type_cell& c);
	auto GetRhoAir()->const Inversible_Value<type_data>;
};
#include "GetCellType_Air.tpp"
#endif
