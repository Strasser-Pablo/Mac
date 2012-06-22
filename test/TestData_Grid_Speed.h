#include <cxxtest/TestSuite.h>
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_Base_Dim_Type.h"
#define eps 1e-10
class Test_Data_Grid_Speed : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
		void test_Grid_Speed_Set_Get()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			type_grid_speed m_grid_speed;
			m_grid_speed.Speed_Set(1,3.4);
			m_grid_speed.Speed_Set(2,4.4);
			m_grid_speed.Speed_Set(3,9);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),3.4,eps);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(2),4.4,eps);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(3),9,eps);
			
			typedef typename type_grid_speed::type_speed type_speed;
			type_speed s=m_grid_speed.Speed_Get();
			
			TS_ASSERT_DELTA(s.Get(1),3.4,eps);
			TS_ASSERT_DELTA(s.Get(2),4.4,eps);
			TS_ASSERT_DELTA(s.Get(3),9,eps);

			type_grid_speed m_grid_speed2;
			m_grid_speed2.Speed_Set(s);

			TS_ASSERT_DELTA(m_grid_speed2.Speed_Get(1),3.4,eps);
			TS_ASSERT_DELTA(m_grid_speed2.Speed_Get(2),4.4,eps);
			TS_ASSERT_DELTA(m_grid_speed2.Speed_Get(3),9,eps);
		}
		void test_Grid_Speed_Const()
		{
			typedef Data_Base_Dim_Type<double,3> DataBase;
			typedef Data_Grid_Speed<DataBase> type_grid_speed;
			type_grid_speed m_grid_speed;
			m_grid_speed.Speed_Set(1,3.4);
			m_grid_speed.Speed_Set(2,4.4);
			m_grid_speed.Speed_Set(3,9);

			typedef typename type_grid_speed::type_speed type_speed;
			type_speed m_speed=m_grid_speed.Speed_Get();
			m_grid_speed.Speed_Set_Const(1);
			m_grid_speed.Speed_Set(1,5);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),3.4,eps);
			m_grid_speed.Speed_Set_None_Const(1);
			m_grid_speed.Speed_Set(1,5);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),5,eps);
			m_grid_speed.Speed_Set(m_speed);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),3.4,eps);

			m_grid_speed.Speed_Set(1,33.4);
			m_grid_speed.Speed_Set(2,44.4);
			m_grid_speed.Speed_Set(3,33);

			m_grid_speed.Speed_Set_Const(1);
			m_grid_speed.Speed_Set_Const(2);
			TS_ASSERT(m_grid_speed.Speed_Get_Const(1));
			TS_ASSERT(!m_grid_speed.Speed_Get_Const(3));
			m_grid_speed.Speed_Set(m_speed);

			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),33.4,eps);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(2),44.4,eps);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(3),9,eps);

			m_grid_speed.Speed_Set_None_Const(1);
			m_grid_speed.Speed_Set(1,33.4);
			TS_ASSERT_DELTA(m_grid_speed.Speed_Get(1),33.4,eps);
		}

};
