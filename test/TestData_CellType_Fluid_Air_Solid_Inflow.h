#include <cxxtest/TestSuite.h>
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow.h"
#include "../src/Data_Base_Dim_Type.h"
#define eps 1e-10
class Test_Data_CellType_Fluid_Air_Solid_Inflow : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	/**
	 * \test That the following function Data...
	 **/
	void test_Base()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		Material_Type invalid=Material_Type(10);
		TS_ASSERT_EQUALS(D.MaterialToInt(Material_Type::Fluid),1);
		TS_ASSERT_EQUALS(D.MaterialToInt(Material_Type::Air),0);
		TS_ASSERT_EQUALS(D.Material_To_Type_Fluid(Material_Type::Air),Material_Type_Fluid::Air);
		TS_ASSERT_EQUALS(D.Material_To_Type_Fluid(Material_Type::Fluid),Material_Type_Fluid::Fluid);
		TS_ASSERT_THROWS_ANYTHING(D.Material_To_Type_Fluid(invalid));
		TS_ASSERT_THROWS_ANYTHING(D.MaterialToInt(invalid));
	}
	/**
	 * \test Test that dejdeojdeodje
	 **/
	void test_Air()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		TS_ASSERT(D.GetIsFluid(Material_Type::Fluid));
		TS_ASSERT(!D.GetIsFluid(Material_Type::Air));
	}
	/**
	 * \test Test that ddedekodoekdek
	 **/
	void test_Fluid()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		TS_ASSERT(!D.GetIsAir(Material_Type::Fluid));
		TS_ASSERT(D.GetIsAir(Material_Type::Air));
	}
	void test_GetFluid_Air()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		TS_ASSERT_EQUALS(D.GetFluid(),Material_Type::Fluid);
		TS_ASSERT_EQUALS(D.GetAir(),Material_Type::Air);
	}
	void test_GetRho()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		D.SetRhoAir(rho_air);
		D.SetRhoFluid(rho_fluid);
		TS_ASSERT_DELTA(D.GetRhoAir().Get(),1,eps);
		TS_ASSERT_DELTA(D.GetRhoAir().Get_Inv(),1,eps);
		TS_ASSERT_DELTA(D.GetRhoFluid().Get(),1000,eps);
		TS_ASSERT_DELTA(D.GetRhoFluid().Get_Inv(),1./1000,eps);

		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D2(rho_fluid,rho_air);
		TS_ASSERT_DELTA(D.GetRhoAir().Get(),1,eps);
		TS_ASSERT_DELTA(D.GetRhoAir().Get_Inv(),1,eps);
		TS_ASSERT_DELTA(D.GetRhoFluid().Get(),1000,eps);
		TS_ASSERT_DELTA(D.GetRhoFluid().Get_Inv(),1./1000,eps);

		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;

		TS_ASSERT_DELTA(D.GetRho(Material_Type::Air).Get(),1,eps);
		TS_ASSERT_DELTA(D.GetRho(Material_Type::Air).Get_Inv(),1,eps);
		TS_ASSERT_DELTA(D.GetRho(Material_Type::Fluid).Get(),1000,eps);
		TS_ASSERT_DELTA(D.GetRho(Material_Type::Fluid).Get_Inv(),1./1000,eps);
	}
	void test_Solid()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		TS_ASSERT(!D.GetIsSolid(Material_Type::Fluid));
		TS_ASSERT(!D.GetIsSolid(Material_Type::Air));
		TS_ASSERT(!D.GetIsSolid(Material_Type::Inflow));
		TS_ASSERT(D.GetIsSolid(Material_Type::Solid));
	}

	void test_Inflow()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air_Solid_Inflow<DataBase>::Material_Type_Fluid Material_Type_Fluid;
		Data_CellType_Fluid_Air_Solid_Inflow<DataBase> D;
		TS_ASSERT(!D.GetIsInflow(Material_Type::Fluid));
		TS_ASSERT(!D.GetIsInflow(Material_Type::Air));
		TS_ASSERT(D.GetIsInflow(Material_Type::Inflow));
		TS_ASSERT(!D.GetIsInflow(Material_Type::Solid));
	}
};
