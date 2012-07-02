#include <cxxtest/TestSuite.h>
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Datas.h"
#include "../src/Data_Grid_MacCell.h"
#define eps 1e-10
class Test_Data_Grid : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void testBaseSpacing()
	{
		typedef Data_Base_Dim_Type<double,3> Data_Base;
		typedef Data_Grid_Base_Spacing<Data_Base> Data_Grid_Base;
		typedef typename Data_Grid_Base::type_data_vector type_data_vector;
		type_data_vector h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		h.Set(3,1.0);
		Data_Grid_Base D;
		D.m_h=Inversible_Value<type_data_vector>(h);
		type_data_vector veps;
		veps.SetAll(eps);
		TS_ASSERT(true);
	}
	void testBaseMacCell()
	{
		typedef Data_Base_Dim_Type<double,3> Data_Base;
		typedef Data_Grid_Base_Spacing<Data_Base> Data_Grid_Base;
		typedef typename Data_Grid_Base::type_data_vector type_data_vector;
		type_data_vector h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		h.Set(3,1.0);
		Data_Grid_Base D;
		D.m_h=Inversible_Value<type_data_vector>(h);
		typedef Datas<Data_Grid_Base> type_datas;
		type_datas m_datas(D);
		Data_Grid_MacCell<type_datas> mac(m_datas);
		TS_ASSERT(true);
	}
};
