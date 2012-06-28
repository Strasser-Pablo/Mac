#include <cxxtest/TestSuite.h>
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_CellType_Domain_Fluid.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_MacCell.h"
#include "../src/Datas.h"
#define eps 1e-10
class Test_Data_CellType_Domain_Fluid : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test_GetCellType()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase;
		DataBase base;
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air<DataBase>::Material_Type Material_Type;
		typedef Data_CellType_Fluid_Air<DataBase> type_fluid_air;
		type_fluid_air fluid_air(base);
		typedef Data_CellType_Domain_Fluid<type_fluid_air> type_domain;
		typedef typename type_domain::Material_Type Material_Type;
		type_domain D(fluid_air);
		TS_ASSERT(D.GetIsInDomain(Material_Type::Fluid));
		TS_ASSERT(!D.GetIsInDomain(Material_Type::Air));

		typedef Datas<DataBase,type_domain> type_datas;
		type_datas m_datas(base,D);
		typedef Data_Grid_MacCell<type_datas> type_mac_cell;
		type_mac_cell mac(m_datas);
		mac.SetFluid();
		TS_ASSERT(mac.GetIsInDomain());
		mac.SetAir();
		TS_ASSERT(!mac.GetIsInDomain());
	}
};
