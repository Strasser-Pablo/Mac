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
#include "../src/Data_Grid_Table.h"
#include "../src/Data_Interface_Fluid_Air.h"
#define eps 1e-10

class Test_Data_Inteface_Fluid_Air : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void testInterface()
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
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<3,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		Data_Interface_Fluid_Air<type_data_grid> m_interface_fluid_air(table);
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		m_interface_fluid_air[v].GetRef().SetFluid();
		vect v2;
		v2.Set(1,1);
		v2.Set(2,0);
		v2.Set(3,0);
		m_interface_fluid_air[v2].GetRef().SetFluid();
		TS_ASSERT(m_interface_fluid_air[v].GetNeighbour(1,1)==&m_interface_fluid_air[v2]);
		TS_ASSERT(!m_interface_fluid_air.GetIsFluidAirInterface(v,v2));
		TS_ASSERT(!m_interface_fluid_air.GetIsFluidAirInterface(v,1,1));
		m_interface_fluid_air[v2].GetRef().SetAir();
		TS_ASSERT(m_interface_fluid_air.GetIsFluidAirInterface(v,v2));
		TS_ASSERT(m_interface_fluid_air.GetIsFluidAirInterface(v,1,1));
	}
};
