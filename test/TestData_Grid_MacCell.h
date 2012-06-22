#include <cxxtest/TestSuite.h>
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_MacCell.h"
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_Grid_Pressure.h"
#include "../src/Datas.h"
#define eps 1e-10
class Test_Data_Grid_MacCell : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
		void test_CellType()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			DataBase base;
			typedef typename DataBase::type_data_value type_data_value;
			typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
			type_grid_speed m_grid_speed;
			type_grid_pressure m_grid_pressure;
			Data_CellType_Fluid_Air<DataBase> D;
			Inversible_Value<type_data_value> rho_air(1);
			Inversible_Value<type_data_value> rho_fluid(1000);
			D.SetRhoAir(rho_air);
			D.SetRhoFluid(rho_fluid);
			typedef Datas<DataBase,type_cell_type,type_grid_speed,type_grid_pressure> type_datas;
			type_datas m_datas(base,D,m_grid_speed,m_grid_pressure);
			typedef Data_Grid_MacCell<type_datas> type_mac_cell;
			type_mac_cell mac(m_datas);
			
			TS_ASSERT(!mac.GetIsFluid());
			TS_ASSERT(mac.GetIsAir());

			mac.SetAir();
			TS_ASSERT(!mac.GetIsFluid());
			TS_ASSERT(mac.GetIsAir());
			
			mac.SetFluid();
			TS_ASSERT(mac.GetIsFluid());
			TS_ASSERT(!mac.GetIsAir());

			TS_ASSERT_DELTA(mac.GetRho().Get(),1000,eps);

			mac.SetAir();

			TS_ASSERT_DELTA(mac.GetRho().Get(),1,eps);
		}
		void test_Speed()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			DataBase base;
			typedef typename DataBase::type_data_value type_data_value;
			typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
			type_grid_speed m_grid_speed;
			type_grid_pressure m_grid_pressure;
			Data_CellType_Fluid_Air<DataBase> D;
			Inversible_Value<type_data_value> rho_air(1);
			Inversible_Value<type_data_value> rho_fluid(1000);
			D.SetRhoAir(rho_air);
			D.SetRhoFluid(rho_fluid);
			typedef Datas<DataBase,type_cell_type,type_grid_speed,type_grid_pressure> type_datas;
			type_datas m_datas(base,D,m_grid_speed,m_grid_pressure);
			typedef Data_Grid_MacCell<type_datas> type_mac_cell;
			type_mac_cell mac(m_datas);
			mac.Speed_Set(1,10);
			mac.Speed_Set(2,4);
			mac.Speed_Set(3,3);
			TS_ASSERT_DELTA(mac.Speed_Get(1),10,eps);
			TS_ASSERT_DELTA(mac.Speed_Get(2),4,eps);
			TS_ASSERT_DELTA(mac.Speed_Get(3),3,eps);
		}
		void test_Pressure()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			DataBase base;
			typedef typename DataBase::type_data_value type_data_value;
			typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
			type_grid_speed m_grid_speed;
			type_grid_pressure m_grid_pressure;
			Data_CellType_Fluid_Air<DataBase> D;
			Inversible_Value<type_data_value> rho_air(1);
			Inversible_Value<type_data_value> rho_fluid(1000);
			D.SetRhoAir(rho_air);
			D.SetRhoFluid(rho_fluid);
			typedef Datas<DataBase,type_cell_type,type_grid_speed,type_grid_pressure> type_datas;
			type_datas m_datas(base,D,m_grid_speed,m_grid_pressure);
			typedef Data_Grid_MacCell<type_datas> type_mac_cell;
			type_mac_cell mac(m_datas);

			typedef typename type_mac_cell::type_pressure type_pressure;
			type_pressure pres;
			pres.Set(3.0);
			mac.Pressure_Set(pres);
			type_pressure pres2=mac.Pressure_Get();
			TS_ASSERT_DELTA(pres2.Get(),3.0,eps);
		}
		void test_DifferentCreation()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			DataBase base;
			typedef typename DataBase::type_data_value type_data_value;
			typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
			type_grid_speed m_grid_speed;
			type_grid_pressure m_grid_pressure;
			Data_CellType_Fluid_Air<DataBase> D;
			Inversible_Value<type_data_value> rho_air(1);
			Inversible_Value<type_data_value> rho_fluid(1000);
			D.SetRhoAir(rho_air);
			D.SetRhoFluid(rho_fluid);
			typedef Datas<DataBase,type_grid_speed,type_grid_pressure> type_datas1;
			type_datas1 m_datas1(base,m_grid_speed,m_grid_pressure);
			typedef Data_Grid_MacCell<type_datas1> type_mac_cell1;
			type_mac_cell1 mac1(m_datas1);

			typedef Datas<DataBase,type_cell_type,type_grid_pressure> type_datas2;
			type_datas2 m_datas2(base,D,m_grid_pressure);
			typedef Data_Grid_MacCell<type_datas2> type_mac_cell2;
			type_mac_cell2 mac2(m_datas2);

			typedef Datas<DataBase,type_cell_type,type_grid_speed> type_datas3;
			type_datas3 m_datas3(base,D,m_grid_speed);
			typedef Data_Grid_MacCell<type_datas3> type_mac_cell3;
			type_mac_cell3 mac3(m_datas3);
		}
};
