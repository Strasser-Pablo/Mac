#ifndef GetCellType_Fluid_H
#define GetCellType_Fluid_H
#include "Inversible_Value.h"
#include "GetCellType_Fluid_Base.h"

template <class TypeWorld,class Base>
struct GetCellType_Fluid_Argument
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename Base::type_input_struct type_sub_struct;
	type_sub_struct m_base;
	const type_cell &m_fluid;
	const Inversible_Value<type_data>& m_rho;
	GetCellType_Fluid_Argument(type_sub_struct base,const type_cell &fluid,const Inversible_Value<type_data>& rho):m_base(base),m_fluid(fluid),m_rho(rho)
	{
	}
};

template <class TypeWorld,class Base>
class GetCellType_Fluid : public GetCellType_Fluid_Base<TypeWorld,Base,GetCellType_Fluid<TypeWorld,Base> >
{
	public:
	typedef GetCellType_Fluid_Argument<TypeWorld,Base> type_input_struct;
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	const type_cell &m_fluid;
	const Inversible_Value<type_data>& m_rho; 
	public:
	GetCellType_Fluid(type_input_struct in);
	bool GetIsFluid_Implementation(const type_cell& c);
	auto GetRhoFluid()->const Inversible_Value<type_data>;
};
#include "GetCellType_Fluid.tpp"
#endif
