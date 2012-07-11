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
#include "../src/Policies.h"
#include "../src/Data_Grid_Data.h"
#include "../src/Algorithms.h"
#include "../src/Algorithms_Delete_MacCell.h"
#include "../src/Data_Grid_Table.h"
#include "../src/Empty.h"
#include "../src/Data_Topology.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Algorithms_Update_CellType_Layer.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Policy_Layer_Max.h"
#include "../src/Data_CellType_Const_Inbound.h"
#define eps 1e-10
class TestAlgorithms_Update_CellType_Layer : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
	{
		typedef Data_Base_Dim_Type<double,2> DataBase0;
		DataBase0 base0;
		typedef Data_Grid_Base_Spacing<DataBase0> DataBase00;
		DataBase00 base00(base0);
		Physvector<2,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		base00.m_h.Set(h);
		typedef Data_Staggered_Left<DataBase00> DataBase;
		DataBase base(base00);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_speed m_grid_speed;
		typedef Data_CellType_Const_Inbound<type_grid_speed> type_grid_speed2;
		type_grid_speed2 m_grid_speed2(m_grid_speed);
		type_grid_pressure m_grid_pressure;
		Data_CellType_Fluid_Air<DataBase> D(base);
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		D.SetRhoAir(rho_air);
		D.SetRhoFluid(rho_fluid);
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_layer2;
		type_layer2 layer2;
		typedef Datas<DataBase,type_cell_type,type_grid_speed2,type_grid_pressure,type_layer2> type_datas;
		type_datas m_datas(base,D,m_grid_speed2,m_grid_pressure,layer2);
		typedef Data_Grid_MacCell<type_datas> type_mac_cell;
		type_mac_cell mac(m_datas);
		typedef Physvector<2,int> vect;
		typedef HashPhysvector<2,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<2,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<2,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Data<type_data_grid,DataBase> type_grid_data;
		type_grid_data m_grid_data(table,base);

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,1);
		v.Set(2,1);

		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set_Const(1);
		m_data_ref.m_data.GetGridData()[v].GetRef().SetLayer(0);
		
		typedef Policy_Layer_Max<type_data_ref> type_layer_max;
		type_layer_max m_layer_max(2);
		typedef Policies<type_layer_max> type_policies;
		type_policies policies(m_layer_max);
		Algorithms_Update_CellType_Layer<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),1)
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),21)
	}

	void test2()
	{
		typedef Data_Base_Dim_Type<double,2> DataBase0;
		DataBase0 base0;
		typedef Data_Grid_Base_Spacing<DataBase0> DataBase00;
		DataBase00 base00(base0);
		Physvector<2,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		base00.m_h.Set(h);
		typedef Data_Staggered_Left<DataBase00> DataBase;
		DataBase base(base00);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		type_grid_speed m_grid_speed;
		typedef Data_CellType_Const_Inbound<type_grid_speed> type_grid_speed2;
		type_grid_speed2 m_grid_speed2(m_grid_speed);
		type_grid_pressure m_grid_pressure;
		Data_CellType_Fluid_Air<DataBase> D(base);
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		D.SetRhoAir(rho_air);
		D.SetRhoFluid(rho_fluid);
		typedef Data_Grid_Layer<int> type_layer;
		type_layer layer;
		typedef Data_Grid_Layer_Empty<type_layer> type_layer2;
		type_layer2 layer2;
		typedef Datas<DataBase,type_cell_type,type_grid_speed2,type_grid_pressure,type_layer2> type_datas;
		type_datas m_datas(base,D,m_grid_speed2,m_grid_pressure,layer2);
		typedef Data_Grid_MacCell<type_datas> type_mac_cell;
		type_mac_cell mac(m_datas);
		typedef Physvector<2,int> vect;
		typedef HashPhysvector<2,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<2,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<2,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Data<type_data_grid,DataBase> type_grid_data;
		type_grid_data m_grid_data(table,base);

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef DataRef<type_topology> type_data_ref;
		type_data_ref m_data_ref(topo);
		
		vect v;
		v.Set(1,0);
		v.Set(2,0);

		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set_Const(1);
		m_data_ref.m_data.GetGridData()[v].GetRef().SetLayer(0);
		
		typedef Policy_Layer_Max<type_data_ref> type_layer_max;
		type_layer_max m_layer_max(1);
		typedef Policies<type_layer_max> type_policies;
		type_policies policies(m_layer_max);
		Algorithms_Update_CellType_Layer<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),1);
		m_alg.Do();
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData().size(),10);
		v.Set(1,0);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),0);
		v.Set(1,1);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),1);
		v.Set(1,0);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),1);
		v.Set(1,-1);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),1);
		v.Set(1,0);
		v.Set(2,-1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),1);
		v.Set(1,2);
		v.Set(2,0);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),2);
		v.Set(1,1);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),2);
		v.Set(1,1);
		v.Set(2,-1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),2);
		v.Set(1,0);
		v.Set(2,2);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),2);
		v.Set(1,-1);
		v.Set(2,1);
		TS_ASSERT_EQUALS(m_data_ref.m_data.GetGridData()[v].GetRef().GetLayer(),2);
	}
};
