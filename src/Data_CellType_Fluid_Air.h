#ifndef Data_CellType_Fluid_Air_H
#define Data_CellType_Fluid_Air_H
#include "Data_CellType_Implemented_Fluid_Air.h"
#include "Inversible_Value.h"
template <typename DataBase>
class Data_CellType_Fluid_Air;

template<typename DataBase>
struct Data_CellType_Implemented_Fluid_Air_Traits<Data_CellType_Fluid_Air<DataBase> >
{
	enum class Material_Type{Fluid,Air};
};

template <typename DataBase>
class Data_CellType_Fluid_Air : public Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> > 
{
	public:
		typedef typename DataBase::type_data_value type_data_value;
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> >::Material_Type Material_Type;
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> >::Material_Type_Fluid Material_Type_Fluid;
		Inversible_Value<type_data_value> m_rho_fluid;
		Inversible_Value<type_data_value> m_rho_air;
		int MaterialToInt(Material_Type m);
		const static int Material_Max_Int=1;	
		auto Material_To_Type_Fluid(Material_Type m) -> Material_Type_Fluid;
		auto GetFluid() -> Material_Type;
		auto GetAir() -> Material_Type;
		auto GetRhoAir()->Inversible_Value<type_data_value>;
		auto GetRhoFluid()->Inversible_Value<type_data_value>;
		auto GetRho(Material_Type c)->Inversible_Value<type_data_value>;
		void SetRhoFluid(Inversible_Value<type_data_value>& rho_fluid);
		void SetRhoAir(Inversible_Value<type_data_value>& rho_air);
		Data_CellType_Fluid_Air(Inversible_Value<type_data_value>& rho_fluid,Inversible_Value<type_data_value>& rho_air):m_rho_fluid(rho_fluid),m_rho_air(rho_air)
		{
		}
		Data_CellType_Fluid_Air()
		{
		}
};
#include "Data_CellType_Fluid_Air.tpp"
#endif
