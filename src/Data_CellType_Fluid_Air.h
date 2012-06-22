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
class Data_CellType_Fluid_Air__InCell;

template <typename DataBase>
class Data_CellType_Fluid_Air : public Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> > 
{
	public:
		typedef typename DataBase::type_data_value type_data_value;
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> >::Material_Type Material_Type;
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air<DataBase> >::Material_Type_Fluid Material_Type_Fluid;
		typedef Data_CellType_Fluid_Air__InCell<DataBase> type_In_Cell;
		Inversible_Value<type_data_value> m_rho_fluid;
		Inversible_Value<type_data_value> m_rho_air;
		int MaterialToInt(Material_Type m) const;
		const static int Material_Max_Int=1;	
		auto Material_To_Type_Fluid(Material_Type m) const -> Material_Type_Fluid;
		auto GetFluid() const -> Material_Type;
		auto GetAir() const -> Material_Type;
		auto GetRhoAir() const ->Inversible_Value<type_data_value>;
		auto GetRhoFluid() const ->Inversible_Value<type_data_value>;
		auto GetRho(Material_Type c) const ->Inversible_Value<type_data_value>;
		void SetRhoFluid(Inversible_Value<type_data_value>& rho_fluid);
		void SetRhoAir(Inversible_Value<type_data_value>& rho_air);
		Data_CellType_Fluid_Air(Inversible_Value<type_data_value>& rho_fluid,Inversible_Value<type_data_value>& rho_air):m_rho_fluid(rho_fluid),m_rho_air(rho_air)
		{
		}
		Data_CellType_Fluid_Air()
		{
		}
		typedef Data_CellType_Fluid_Air__InCell<DataBase> type_Cell_type__InCell;
		typedef void type_Cell_type__InCell_exist;
		auto GetInCell() const -> type_Cell_type__InCell;
};

template<typename DataBase>
struct Data_CellType_Implemented_Fluid_Air_Traits<Data_CellType_Fluid_Air__InCell<DataBase> >
{
	enum class Material_Type{Fluid,Air};
};

template <typename DataBase>
class Data_CellType_Fluid_Air__InCell : public Data_CellType_Implemented_Fluid_Air__InCell<Data_CellType_Fluid_Air__InCell<DataBase> >
{
	public:
		typedef typename DataBase::type_data_value type_data_value;
		typedef typename Data_CellType_Fluid_Air<DataBase>::Material_Type Material_Type;
		typedef typename Data_CellType_Fluid_Air<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air__InCell(const Data_CellType_Fluid_Air<DataBase> & data):m_mat(Material_Type::Air),m_data_cell_type(data)
		{
		}
		Data_CellType_Fluid_Air__InCell(const Data_CellType_Fluid_Air<DataBase> & data,Material_Type mat):m_mat(mat),m_data_cell_type(data)
		{
		}
		void SetAir();
		void SetFluid();
		auto GetRho() const ->Inversible_Value<type_data_value>;
		Material_Type m_mat;
		const Data_CellType_Fluid_Air<DataBase> & m_data_cell_type;
};

#include "Data_CellType_Fluid_Air.tpp"
#endif
