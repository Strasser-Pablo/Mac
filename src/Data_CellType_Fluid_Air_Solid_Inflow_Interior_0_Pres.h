#ifndef Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres_H
#define Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres_H
#include "Data_CellType_Implemented_Fluid_Air.h"
#include "Data_CellType_Implemented_Inflow.h"
#include "Data_CellType_Implemented_Interior.h"
#include "Data_CellType_Implemented_Solid.h"
#include "Data_CellType_Implemented_0_Pres.h"
#include "Inversible_Value.h"
#include "Data_CellType_Solid_SFINAE.h"
template <typename DataBase>
class Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres;

/**
 * @ingroup GR_Data_CellType_Implemented_Fluid_Air
 * @brief
 * Trait class specialisation to send data to Data_CellType_Implemented_Fluid_Air.
 * This class is specialised for Data_CellType_Fluid_Air.
 * This class store the enum used by Data_CellType_Fluid_Air.
 * @sa Data_CellType_Fluid_Air
 * @sa Data_CellType_Implemented_Fluid_Air
 * @sa Data_CellType_Implemented_Fluid_Air_Traits
 **/
template<typename DataBase>
struct Data_CellType_Implemented_Inflow_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >
{
	enum class Material_Type{Fluid,Air,Solid,Inflow,Interior,_0_Pres};
};


template<typename DataBase>
struct Data_CellType_Implemented_Solid_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >
{
	typedef typename Data_CellType_Implemented_Inflow_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type Material_Type;
};

template<typename DataBase>
struct Data_CellType_Implemented_Interior_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >
{
	typedef typename Data_CellType_Implemented_Inflow_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type Material_Type;
};

template<typename DataBase>
struct Data_CellType_Implemented_Fluid_Air_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >
{
	typedef typename Data_CellType_Implemented_Inflow_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type Material_Type;
};

template<typename DataBase>
struct Data_CellType_Implemented_0_Pres_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >
{
	typedef typename Data_CellType_Implemented_Inflow_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type Material_Type;
};

template <typename DataBase>
class Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell;

/**
 * @ingroup GR_Data_CellType_Fluid_Air
 * @brief
 * Class to created an CellType consisting on Fluid and Air.
 *
 * We use two classification for the type of a CellType.
 * An Material Type: Witch is the data stored.
 * An Material Fluid Type: Witch is calculate from the Material Type above.
 *
 * For this class we have an one to one relation between Material Type and Material Fluid Type.
 *
 * This class store the value of the Density.
 *
 * This class is linked to a related class Data_CellType_Fluid_Air__InCell.
 * Witch is mean to be stored as Data and has a reference to this class to Get Data like the Density.
 *
 * @tparam DataBase A class used to access information. And derivate with.
 *
 * @pre
 * DataBase::type_value need to be defined.
 *
 * @exception std::logic_error if enum value is invalid.
 *
 * @sa Data_CellType_Fluid_Air__InCell
 **/
template <typename DataBase>
class Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres : public Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >,public Data_CellType_Implemented_Inflow<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >,public Data_CellType_Implemented_Solid<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >,public Data_CellType_Implemented_Interior<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >,public Data_CellType_Implemented_0_Pres<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >, public DataBase
{
	public:
		/**
		 * @brief
		 * Basic Type for floating point calculation.
		 * Expected to be a type like double or float.
		 **/
		typedef typename DataBase::type_data_value type_data_value;
		/**
		 * @brief
		 * Type used for density return value.
		 * This class has a method Get and GetInv to get the inverse.
		 **/
		typedef Inversible_Value<type_data_value> type_data_rho;
		/**
		 * @brief
		 * Type used for the Material Type.
		 * It consist of an enum with two value( Fluid and Air).
		 **/
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type Material_Type;
		/**
		 * @brief
		 * Type used for the Material Fluid Type.
		 * It consist of an enum with two value( Fluid and Air).
		 **/
		typedef typename Data_CellType_Implemented_Fluid_Air<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type_Fluid Material_Type_Fluid;
		typedef typename Data_CellType_Implemented_Inflow<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type_Inflow Material_Type_Inflow;
		typedef typename Data_CellType_Implemented_Solid<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type_Solid Material_Type_Solid;
		typedef typename Data_CellType_Implemented_Interior<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type_Interior Material_Type_Interior;
		typedef typename Data_CellType_Implemented_0_Pres<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> >::Material_Type_0_Pres Material_Type_0_Pres;
		/**
		 * @brief
		 * Type of the related class used to store in cell.
		 **/
		typedef Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase> type_In_Cell;
		/**
		 * @brief
		 * Value of the density of Fluid.
		 **/
		Inversible_Value<type_data_value> m_rho_fluid;
		/**
		 * @brief
		 * Value of the density of Air.
		 **/
		Inversible_Value<type_data_value> m_rho_air;
		/**
		 * @brief
		 * Transform type to a unic integer value. Begining at 0.
		 * @param m Material Type to transform on number.
		 * @return Unique integer.
		 * @post
		 * The value is between 0 and Material_Max_Int.
		 * @exception std::logic_error if enum value is invalid.
		 **/
		int MaterialToInt(Material_Type m) const;
		/**
		 * @brief
		 * Maximun of the integer value.
		 **/
		const static int Material_Max_Int=5;
		/**
		 * @brief
		 * Transform a Material Type to a Material Fluid Type.
		 * In this class, it use an one to one relation.
		 * @param m Material Type to treat.
		 * @return Material Type Fluid that conrespond to this material type.
		 * @exception std::logic_error if enum value is invalid.
		 **/
		auto Material_To_Type_Fluid(Material_Type m) const -> Material_Type_Fluid;
		auto Material_To_Type_Inflow(Material_Type m) const -> Material_Type_Inflow;
		auto Material_To_Type_Solid(Material_Type m) const -> Material_Type_Solid;
		auto Material_To_Type_Interior(Material_Type m) const -> Material_Type_Interior;
		auto Material_To_Type_0_Pres(Material_Type m) const -> Material_Type_0_Pres;
		/**
		 * @brief
		 * Return the Material Type that represent Fluid.
		 * @return Material Type used to represent Fluid.
		 **/
		auto GetFluid() const -> Material_Type;
		/**
		 * @brief
		 * Return the Material Type that represent Air.
		 * @return Material Type used to represent Air.
		 **/
		auto GetAir() const -> Material_Type;
		auto GetSolid() const -> Material_Type;
		auto GetInflow() const -> Material_Type;
		auto GetInterior() const -> Material_Type;
		auto Get0_Pres() const -> Material_Type;
		/**
		 * @brief
		 * Return the value of density for the Air.
		 * @return Density of Air.
		 **/
		auto GetRhoAir() const ->Inversible_Value<type_data_value>;
		/**
		 * @brief
		 * Return the value of density for the Fluid.
		 * @return Density of Fluid.
		 **/
		auto GetRhoFluid() const ->Inversible_Value<type_data_value>;
		/**
		 * @brief
		 * Return the value of density for the Type given.
		 * @param c Material Type.
		 * @return Density of the given Material.
		 **/
		auto GetRho(Material_Type c) const ->Inversible_Value<type_data_value>;
		/**
		 * @brief
		 * Set the value of the density of Fluid.
		 **/
		void SetRhoFluid(Inversible_Value<type_data_value>& rho_fluid);
		/**
		 * @brief
		 * Set the value of the density of Air.
		 **/
		void SetRhoAir(Inversible_Value<type_data_value>& rho_air);
		/**
		 * @brief
		 * Constructor
		 * @param rho_fluid Value of density for fluid.
		 * @param rho_air Value of density for air.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres(Inversible_Value<type_data_value>& rho_fluid,Inversible_Value<type_data_value>& rho_air):m_rho_fluid(rho_fluid),m_rho_air(rho_air)
		{
		}
		/**
		 * @brief
		 * Default Constructor
		 * @warning
		 * Value of Fluid density and Air density will not be initialised.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres()
		{
		}
		/**
		 * @brief
		 * Constructor with DataBase without default constructor.
		 * @param rho_fluid Value of density for fluid.
		 * @param rho_air Value of density for air.
		 * @param base DataBase instance that will be copied.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres(Inversible_Value<type_data_value>& rho_fluid,Inversible_Value<type_data_value>& rho_air,const DataBase& base):m_rho_fluid(rho_fluid),m_rho_air(rho_air),DataBase(base)
		{
		}
		/**
		 * @brief
		 * Constructor with DataBase without default constructor.
		 * @warning
		 * Value of Fluid density and Air density will not be initialised.
		 * @param base DataBase instance that will be copied.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres(const DataBase& base):DataBase(base)
		{
		}
		/**
		 * @brief
		 * Type of the cell to construct in Cell.
		 * This will be done by calling the constructor of this type with a reference to this class.
		 **/
		typedef Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase> type_Cell_type__InCell;
		/**
		 * @brief
		 * This type is used in SFINAE to see if we need to construct a celltype for the cell
		 * and that type type_Cell_type__InCell can be constructed.
		 **/
		typedef void type_Cell_type__InCell_exist;
		typedef void type_method_solid_exist;
		typedef void type_method_interior_exist;
};

template<typename DataBase>
struct Data_CellType_Implemented_Fluid_Air_Traits<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase> >
{
	enum class Material_Type{Fluid,Air};
};

/**
 * @ingroup GR_Data_CellType_Fluid_Air
 * @brief
 * Class to store the type of a cell and manipulated it.
 * The density is stored in another class referenced by this class.
 * This class work very closely with Data_CellType_Fluid_Air.
 *
 * @tparam DataBase A class used to access information. And derivate with.
 *
 * @pre
 * DataBase::type_value need to be defined.
 * @exception std::logic_error if enum value is invalid.
 * @sa Data_CellType_Fluid_Air
 **/
template <typename DataBase>
class Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell : public Data_CellType_Implemented_Fluid_Air__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >, public Data_CellType_Implemented_Solid__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >, public Data_CellType_Implemented_Inflow__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >, public Data_CellType_Implemented_Interior__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >, public Data_CellType_Implemented_0_Pres__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >
{
	public:
		/**
		 * @brief
		 * Basic Type for floating point calculation.
		 * Expected to be a type like double or float.
		 **/
		typedef typename DataBase::type_data_value type_data_value;
		/**
		 * @brief
		 * Material Type.
		 * It consist of an enum with two value( Fluid and Air).
		 **/
		typedef typename Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase>::Material_Type Material_Type;
		/**
		 * @brief
		 * Type used for density return value.
		 * This class has a method Get and GetInv to get the inverse.
		 **/
		typedef Inversible_Value<type_data_value> type_data_rho;
		/**
		 * @brief
		 * Material Fluid Type.
		 **/
		typedef typename Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		typedef typename Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase>::Material_Type_Inflow Material_Type_Inflow;
		typedef typename Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase>::Material_Type_Interior Material_Type_Interior;
		/**
		 * @brief
		 * Constructor from a Data_CellType_Fluid_Air class. With default cell_type Air.
		 * @param data Instance of Data_CellType_Fluid_Air that will store the density.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell(const Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> & data):Data_CellType_Implemented_Fluid_Air__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >(static_cast<const DataBase&>(data)),Data_CellType_Implemented_Solid__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >(static_cast<const DataBase&>(data)),Data_CellType_Implemented_Inflow__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >(static_cast<const DataBase&>(data)),Data_CellType_Implemented_Interior__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >(static_cast<const DataBase&>(data)),Data_CellType_Implemented_0_Pres__InCell<Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell<DataBase>,DataBase >(static_cast<const DataBase&>(data)),m_mat(Material_Type::Air),m_data_cell_type(data),m_no_delete(false)
		{
		}
		/**
		 * @brief
		 * Constructor from a Data_CellType_Fluid_Air class.
		 * @param data Instance of Data_CellType_Fluid_Air that will store the density.
		 * @param mat Value of the type of cell.
		 **/
		Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres__InCell(const Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> & data,Material_Type mat):m_mat(mat),m_data_cell_type(data),m_no_delete(false)
		{
		}
		/**
		 * @brief
		 * Set the Material Type to Air.
		 **/
		void SetAir();
		/**
		 * @brief
		 * Set the Material Type to Fluid.
		 **/
		void SetFluid();
		void SetInflow();
		void SetSolid();
		void SetInterior();
		void Set0_Pres();
		/**
		 * @brief
		 * Get the density of the current cell
		 * @return Density of the current Cell.
		 **/
		auto GetRho() const ->Inversible_Value<type_data_value>;
		/**
		 * @brief
		 * Get the density of Air.
		 * @return Density of Air.
		 **/
		auto GetRhoAir() const ->Inversible_Value<type_data_value>;
		/**
		 * @brief
		 * Get the density of Fluid.
		 * @return Density of Fluid.
		 **/
		auto GetRhoFluid() const ->Inversible_Value<type_data_value>;
		bool GetIsNoDelete()
		{
			return m_no_delete;
		}
		void SetIsNoDelete(bool nodelete=true)
		{
			m_no_delete=nodelete;
		}
		/**
		 * @brief
		 * Storage of the current CellType.
		 **/
		Material_Type m_mat;
		/**
		 * @brief
		 * Reference to the linked class.
		 **/
		const Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres<DataBase> & m_data_cell_type;
		bool m_no_delete=false;
		typedef void type_method_solid_exist;
		typedef void type_method_interior_exist;
};



#include "Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres.tpp"
#endif
