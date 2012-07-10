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
#include "../src/Data_Grid_Table.h"
#include "../src/Empty.h"
#include "../src/Data_Topology.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"
#include "../src/Policy_Particle_To_Key.h"
#include "../src/Data_Grid_Base_Spacing.h"
#include "../src/Data_Grid_Layer_Empty.h"
#include "../src/Data_CellType_Const_Inbound.h"
#include "../src/Data_Timing.h"
#include "../src/Data_Timing_Time.h"
#include "../src/Policy_Output_Particle.h"
#include "../src/Policy_Output_Grid_Speed.h"
#include "../src/Policy_Output_Grid_Pressure.h"
#include "../src/Algorithms_Output.h"
#include "../src/Policy_Output_Animation.h"
#define eps 1e-10
class TestAlgorithms_Output : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
	{
		typedef Data_Base_Dim_Type<double,1> DataBase0;
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
		typedef Physvector<1,int> vect;
		typedef HashPhysvector<1,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<1,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<1,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Base_Spacing<type_data_grid> DataBase_00;
		DataBase_00 base_00(table);
		Physvector<1,double> h;
		h.Set(1,1.0);
		base_00.m_h.Set(h);
		typedef Data_Grid_Data<DataBase_00,DataBase> type_grid_data;
		type_grid_data m_grid_data(base_00,base);

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);
		
		vect v;
		v.Set(1,0);
		Physvector<1,double> speed;
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(0);
		
		v.Set(1,1);
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(0);

		v.Set(1,-1);
		speed.Set(1,1.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<1,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(0);
		
		type_particle part;
		part.GetParticlePosRef().Set(1,2.2);
		m_data_ref.m_data.GetTopologyData().GetRefToParticleList().push_back(part);
		
		m_data_ref.m_data.GetTimingData().m_t=1;
		
		typedef Policy_Output_Grid_Speed<type_data_ref> type_pol_speed;
		type_pol_speed m_pol_speed(m_data_ref,"Out_Speed_");
		typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_pressure;
		type_pol_pressure m_pol_pressure(m_data_ref,"Out_Pressure_");
		typedef Policy_Output_Particle<type_data_ref> type_pol_particle;
		type_pol_particle m_pol_particle(m_data_ref,"Out_Particle_");
		typedef Policy_Output_Animation<type_data_ref> type_pol_animation;
		type_pol_animation m_pol_animation(m_data_ref,"Out_Animation.pvd");

		typedef Policies<type_pol_speed,type_pol_pressure,type_pol_particle,type_pol_animation> type_pol;
		type_pol pol(m_pol_speed,m_pol_pressure,m_pol_particle,m_pol_animation);
		typedef Algorithms_Output<type_data_ref,type_pol> type_alg;
		type_alg alg(m_data_ref,pol);
		alg.Do();
		TS_ASSERT(true);
	}
	void test2()
	{
		typedef Data_Base_Dim_Type<double,2> DataBase0;
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
		typedef Physvector<2,int> vect;
		typedef HashPhysvector<2,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<2,type_mac_cell>,true,Hash> hook_table;
		Neighbour_List<2,type_mac_cell> m_neigh(mac);
		hook_table m_hook_table(m_neigh,hash);
		typedef Data_Grid_Table<hook_table> type_data_grid;
		type_data_grid table(m_hook_table);
		typedef Data_Grid_Base_Spacing<type_data_grid> DataBase_00;
		DataBase_00 base_00(table);
		Physvector<2,double> h;
		h.Set(1,1.0);
		h.Set(2,1.0);
		base_00.m_h.Set(h);
		typedef Data_Grid_Data<DataBase_00,DataBase> type_grid_data;
		type_grid_data m_grid_data(base_00,base);

		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_particles;
		type_particles particles(base);
		typedef Data_Topology<type_particles,type_grid_data> type_topology;
		type_topology topo(particles,m_grid_data);
		typedef Data_Timing_Time<double> type_time;
		type_time m_time;
		typedef Data_Timing<type_time,type_topology> type_timing;
		type_timing m_timing(m_time,topo);
		typedef DataRef<type_timing> type_data_ref;
		type_data_ref m_data_ref(m_timing);
		
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		Physvector<2,double> speed;
		speed.Set(1,1.0);
		speed.Set(2,1.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(1);
		
		v.Set(1,1);
		v.Set(2,0);
		speed.Set(1,1.0);
		speed.Set(2,2.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(3);

		v.Set(1,0);
		v.Set(2,1);
		speed.Set(1,3.0);
		speed.Set(2,3.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(4);
		
		v.Set(1,1);
		v.Set(2,1);
		speed.Set(1,1.0);
		speed.Set(2,3.0);
		m_data_ref.m_data.GetGridData()[v].GetRef().Speed_Set(Data_Speed_Data<2,double>(speed));
		m_data_ref.m_data.GetGridData()[v].GetRef().Pressure_Set(5);

		type_particle part;
		part.GetParticlePosRef().Set(1,0.5);
		part.GetParticlePosRef().Set(2,0.5);
		m_data_ref.m_data.GetTopologyData().GetRefToParticleList().push_back(part);
		m_data_ref.m_data.GetTimingData().m_t=1;
		
		typedef Policy_Output_Grid_Speed<type_data_ref> type_pol_speed;
		type_pol_speed m_pol_speed(m_data_ref,"Out_Speed_");
		typedef Policy_Output_Grid_Pressure<type_data_ref> type_pol_pressure;
		type_pol_pressure m_pol_pressure(m_data_ref,"Out_Pressure_");
		typedef Policy_Output_Particle<type_data_ref> type_pol_particle;
		type_pol_particle m_pol_particle(m_data_ref,"Out_Particle_");
		typedef Policy_Output_Animation<type_data_ref> type_pol_animation;
		type_pol_animation m_pol_animation(m_data_ref,"Out_Animation.pvd");

		typedef Policies<type_pol_speed,type_pol_pressure,type_pol_particle,type_pol_animation> type_pol;
		type_pol pol(m_pol_speed,m_pol_pressure,m_pol_particle,m_pol_animation);
		typedef Algorithms_Output<type_data_ref,type_pol> type_alg;
		type_alg alg(m_data_ref,pol);
		alg.Do();
		TS_ASSERT(true);
	}
};
