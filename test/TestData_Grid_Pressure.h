#include <cxxtest/TestSuite.h>
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_Pressure.h"
#define eps 1e-10
class Test_Data_Grid_MacCell : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
		void test_Set_Get()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
			typedef typename type_grid_pressure::type_pressure type_pressure;
			type_grid_pressure m_grid_pressure;
			type_pressure pres;
			pres.Set(3.0);
			m_grid_pressure.Pressure_Set(pres);
			type_pressure pres2=m_grid_pressure.Pressure_Get();
			TS_ASSERT_DELTA(pres2.Get(),3.0,eps);
		}
};
