#include <cxxtest/TestSuite.h>
#include "../src/Data_Pressure_Data.h"
#include <utility>
#define eps 1e-10
class Test_Data_Pressure_Data : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test_conversion()
	{
		typedef double type_data;
		typedef Data_Pressure_Data<double> type_pressure;
		type_data data=2.0;
		type_pressure pressure(data);
		TS_ASSERT_DELTA(double(pressure),data,eps);
		TS_ASSERT_DELTA(pressure.Get(),data,eps)
		pressure.Set(0.2);
		TS_ASSERT_DELTA(pressure.Get(),0.2,eps)
	}
	void test_Relation()
	{
		typedef double type_data;
		typedef Data_Pressure_Data<double> type_pressure;
		type_data data=2.0;
		type_data data2=4.0;
		type_pressure pressure(data);
		type_pressure pressure2(data2);
		TS_ASSERT(pressure<pressure2);
		TS_ASSERT(!(pressure2<pressure));
		TS_ASSERT((pressure2>pressure));
		TS_ASSERT(!(pressure>pressure2));
		TS_ASSERT(!(pressure==pressure2));
		TS_ASSERT((pressure==pressure));
		TS_ASSERT((pressure!=pressure2));
		TS_ASSERT(!(pressure!=pressure));
		TS_ASSERT((pressure<=pressure2));
		TS_ASSERT(!(pressure2<=pressure));
		TS_ASSERT((pressure2>=pressure));
		TS_ASSERT(!(pressure>=pressure2));
	}
};
