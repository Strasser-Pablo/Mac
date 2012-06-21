#ifndef Data_CellType_Fluid_Air_H
#define Data_CellType_Fluid_Air_H
#include "Data_CellType_Implemented_Fluid_Air.h"
#include "Inversible_Value.h"
template <typename TypeData>
class Data_CellType_Fluid_Air;

template<typename TypeData>
struct Data_CellType_Implemented_Fluid_Air_Traits<Data_CellType_Fluid_Air<TypeData> >
{
	enum class Material_Type{Fluid,Air};
};

template <typename TypeData>
class Data_CellType_Fluid_Air : public Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<TypeData> > 
{
	public:
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<TypeData> >::Material_Type Material_Type;
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<TypeData> >::Material_Type_Fluid Material_Type_Fluid;
		Inversible_Value<TypeData> m_rho_fluid;
		Inversible_Value<TypeData> m_rho_air;
		int MaterialToInt(Material_Type m);
		const static int Material_Max_Int=1;	
		auto Material_To_Type_Fluid(Material_Type m) -> Material_Type_Fluid;
		auto GetFluid() -> Material_Type;
		auto GetAir() -> Material_Type;
		auto GetRhoAir()->Inversible_Value<TypeData>;
		auto GetRhoFluid()->Inversible_Value<TypeData>;
		void SetRhoFluid(Inversible_Value<TypeData>& rho_fluid);
		void SetRhoAir(Inversible_Value<TypeData>& rho_air);
		Data_CellType_Fluid_Air(Inversible_Value<TypeData>& rho_fluid,Inversible_Value<TypeData>& rho_air):m_rho_fluid(rho_fluid),m_rho_air(rho_air)
		{
		}
		Data_CellType_Fluid_Air()
		{
		}
};
#include "Data_CellType_Fluid_Air.tpp"
#endif
