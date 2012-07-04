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
#include "../src/Algorithms_Speed_Constant_Mirror.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Policy_Add_Particle_Center.h"
#include "../src/Policy_Is_Inbound_Filling_Layer.h"
#include "../src/Data_CellType_Const_Inbound.h"
#define eps 1e-10
class TestAlgorithms_Create_Fluid_Particle : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
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
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<3,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Base_Spacing<type_data_grid> DataBase_00;
		DataBase_00 base_00(table);
		Physvector<3,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		h.Set(3,1.0);
		base_00.m_h.Set(h);
		typedef Data_Grid_Data<DataBase_00,DataBase> type_grid_data;
		type_grid_data m_grid_data(base_00,base);

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
		v.Set(3,1);
		
		Physvector<3,double> speed;
		speed.Set(1,1.0);
		speed.Set(2,5.0);
		speed.Set(3,6.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<3,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set_Const(1);
		
		typedef Policies<> type_policies;
		type_policies policies;
		Algorithms_Speed_Constant_Mirror<type_data_ref,type_policies> m_alg(m_data_ref,policies);
		m_alg.Do();

		v.Set(1,2);
		Data_Speed_Data<3,double> speed_ret=m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Get();
		TS_ASSERT_DELTA(speed_ret.Get(1),1.0,eps)
		v.Set(1,1);
		v.Set(2,2);
		speed_ret=m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Get();
		TS_ASSERT_DELTA(speed_ret.Get(2),0.0,eps)
		v.Set(2,1);
		v.Set(3,2);
		speed_ret=m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Get();
		TS_ASSERT_DELTA(speed_ret.Get(3),0.0,eps)
	}
};
