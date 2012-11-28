#include <cxxtest/TestSuite.h>
#include "../src/Data_CellType_Fluid_Air.h"
#include "../src/Data_CellType_Fluid_Air_Solid_Inflow.h"
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Grid_Speed.h"
#include "../src/Data_Grid_Pressure.h"
#include "../src/Datas.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Grid_Layer.h"

#include "../src/Data_Grid_CellType_To_Grid_CellType.h"
#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Neighbour_List_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Hookable_Hash_Table.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/ChunkHashTable.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#define eps 1e-10
class Test_MacCell2 : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	~Test_MacCell2()
	{
		SingletonManager::Kill();
	}
	void testcelltype()
	{
		const int N=1;
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;
		typedef Data_CellType_Fluid_Air<DataBase> type_cell_type;
		Data_CellType_Fluid_Air<DataBase> D(base);
		Inversible_Value<type_data_value> rho_air(1);
		Inversible_Value<type_data_value> rho_fluid(1000);
		D.SetRhoAir(rho_air);
		D.SetRhoFluid(rho_fluid);
		typedef Data_Grid_CellType_To_Grid_CellType<type_cell_type> type_grid_cell_type;
		type_grid_cell_type m_grid_cell_type(D);

		typedef Data_Chunk_CellType<type_grid_cell_type,N> type_celltype;
		type_celltype m_celltype(m_grid_cell_type);

		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;
		typedef Data_Chunk<type_celltype,type_bool_array> type_chunk;
		type_chunk m_chunk(m_celltype,m_bool_array);

		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_CellType<type_grid_cell_type,type_off_base> type_off_base_celltype;
		typedef Offset_Base_Neighbour<type_off_base_celltype> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		type_vect v;
		v.Set(1,1.0);
		m_table[v].CellType_GetRef().SetFluid();
		TS_ASSERT(m_table[v].CellType_GetRef().GetIsFluid());
		TS_ASSERT(!m_table[v].CellType_GetRef().GetIsAir());
		TS_ASSERT_DELTA(m_table[v].CellType_GetRef().GetRho().Get(),1000,eps);
		m_table[v].CellType_GetRef().SetAir();
		TS_ASSERT(m_table[v].CellType_GetRef().GetIsAir());
		TS_ASSERT(!m_table[v].CellType_GetRef().GetIsFluid());
		TS_ASSERT_DELTA(m_table[v].CellType_GetRef().GetRho().Get(),1,eps);
	}
	void test_Speed()
	{
		const int N=1;
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;

		typedef Data_Grid_Speed<DataBase> type_grid_speed;
		typedef Data_Chunk_Speed<type_grid_speed,N> type_chunk_speed;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;
		type_grid_speed m_grid_speed;
		type_chunk_speed m_chunk_speed(m_grid_speed);
		typedef Data_Chunk<type_chunk_speed,type_bool_array> type_chunk;
		type_chunk m_chunk(m_chunk_speed,m_bool_array);

		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Speed<type_grid_speed,type_off_base> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		type_vect v;
		v.Set(1,0);
		m_table[v].Speed_GetRef().Speed_Set(1,10);
		m_table[v].Speed_GetRef().Speed_Set(2,4);
		m_table[v].Speed_GetRef().Speed_Set(3,50);
		TS_ASSERT_DELTA(m_table[v].Speed_GetRef().Speed_Get(1),10,eps);
		TS_ASSERT_DELTA(m_table[v].Speed_GetRef().Speed_Get(2),4,eps);
		TS_ASSERT_DELTA(m_table[v].Speed_GetRef().Speed_Get(3),50,eps);
	}
	void test_Pressure()
	{
		const int N=1;
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef typename DataBase::type_data_value type_data_value;

		typedef Data_Grid_Pressure<DataBase> type_grid_pressure;
		typedef Data_Chunk_Pressure<type_grid_pressure,N> type_chunk_pressure;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;
		type_grid_pressure m_grid_pressure;
		type_chunk_pressure m_chunk_pressure(m_grid_pressure);
		typedef Data_Chunk<type_chunk_pressure,type_bool_array> type_chunk;
		type_chunk m_chunk(m_chunk_pressure,m_bool_array);

		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Pressure<type_grid_pressure,type_off_base> type_off_base_pressure;
		typedef Offset_Base_Neighbour<type_off_base_pressure> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		type_vect v;
		v.Set(1,0);
		typedef type_chunk::type_pressure::type_pressure type_pressure;
		type_pressure pres;
		pres.Set(20);
		m_table[v].Pressure_GetRef().Pressure_Set(pres);
		type_pressure pres2=m_table[v].Pressure_GetRef().Pressure_Get();
		TS_ASSERT_DELTA(pres2.Get(),20,eps);
	}
	void test_Layer()
	{
		const int N=1;
		typedef Data_Grid_Layer<int> type_grid_layer;
		typedef Data_Chunk_Layer<type_grid_layer,N> type_chunk_layer;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		type_bool_array m_bool_array;
		type_grid_layer m_grid_layer;
		type_chunk_layer m_chunk_layer(m_grid_layer);
		typedef Data_Chunk<type_chunk_layer,type_bool_array> type_chunk;
		type_chunk m_chunk(m_chunk_layer,m_bool_array);

		typedef Neighbour_List_Empty<1,type_chunk> type_neigh;
		type_neigh m_neigh(m_chunk);
		typedef Offset<int,1,N> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Layer<type_grid_layer,type_off_base> type_off_base_layer;
		typedef Offset_Base_Neighbour<type_off_base_layer> type_off_base_neighbour;
		typedef Physvector<1,int> type_vect;
		typedef HashPhysvector<1,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(m_neigh,hash);
		type_vect v;
		v.Set(1,0);
		m_table[v].Layer_GetRef().SetLayer(10);
		TS_ASSERT_DELTA(m_table[v].Layer_GetRef().GetLayer(),10,eps);
	}
};
