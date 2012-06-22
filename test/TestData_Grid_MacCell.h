#include <cxxtest/TestSuite.h>
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_MacCell.h"
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
			Data_CellType_Fluid_Air<DataBase> D;
			Inversible_Value<type_data_value> rho_air(1);
			Inversible_Value<type_data_value> rho_fluid(1000);
			D.SetRhoAir(rho_air);
			D.SetRhoFluid(rho_fluid);
			typedef Datas<DataBase,type_cell_type> type_datas;
			type_datas m_datas(base,D);
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
};
