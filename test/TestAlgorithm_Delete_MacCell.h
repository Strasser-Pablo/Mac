#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List.h"
#include "../src/Hookable_Hash_Table.h"
#include "../src/Hook_Neighbour_List.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_MacCell.h"
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_Grid_Pressure.h"
#include "../src/Datas.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Grid_Layer.h"
#include "../src/DataRef.h"
#include "../src/Policy_Layer_Initial.h"
#include "../src/Policies.h"
#include "../src/Data_Grid_Data.h"
#include "../src/Algorithms.h"
#include "../src/Algorithms_Delete_MacCell.h"
#include "../src/Data_Grid_Table.h"
#include "../src/Empty.h"
#define eps 1e-10
class TestAlgorithmes_Delete_MacCell : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test_Layer_Initial1()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_speed m_grid_speed;
		type_grid_pressure m_grid_pressure;
		Data_CellType_Fluid_Air<DataBase> D(base);
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		D.SetRhoAir(rho_air);
		D.SetRhoFluid(rho_fluid);
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Datas<DataBase,type_cell_type,type_grid_speed,type_grid_pressure,type_layer> type_datas;
		type_datas m_datas(base,D,m_grid_speed,m_grid_pressure,layer);
		typedef Data_Grid_MacCell<type_datas> type_mac_cell;
		type_mac_cell mac(m_datas);
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<3,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Data<type_data_grid,Empty> type_grid_data;
		type_grid_data m_grid_data(table,Empty());
		typedef DataRef<type_grid_data> type_data_ref;
		type_data_ref m_data_ref(m_grid_data);
		Physvector<3,int> v;
		v.Set(1,1);
		v.Set(2,2);
		v.Set(3,3);
		m_data_ref.m_data.GetGridData()[v].GetRef().SetLayer(-1);
		typedef Policy_Layer_Initial<int,-1> pol_layer;
		pol_layer m_pol_layer;
		Algorithms_Delete_MacCell<type_data_ref,pol_layer> m_alg(m_data_ref,m_pol_layer);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),1);
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),0);
		v.Set(1,1);
		v.Set(2,2);
		v.Set(3,3);
		m_data_ref.m_data.GetGridData()[v].GetRef().SetLayer(1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),1);
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),1);
	}
};
