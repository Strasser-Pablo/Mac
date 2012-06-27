#include <cxxtest/TestSuite.h>
#include "../src/Neighbour_List.h"
#include "../src/Hookable_Hash_Table.h"
#include "../src/Hook_Neighbour_List.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Datas.h"
#define eps 1e-10

class Test_Data_Neighbour_List : public CxxTest::TestSuite   //LCOV_EXCL_LINE 
{
	public:
	void testHook1()
	{
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		
		Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,int>,true,Hash> table(Neighbour_List<3,int>(3),hash);
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=0;
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=1;
		v.Set(1,0);
		v.Set(2,1);
		v.Set(3,0);
		table[v].GetRef()=2;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,1);
		table[v].GetRef()=3;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)->Get()==1);
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,-1)->Get()==0);
		table.erase(v);
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
	}
	void testHook2()
	{
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		
		Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,int>,false,Hash> table(hash);
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=0;
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=1;
		v.Set(1,0);
		v.Set(2,1);
		v.Set(3,0);
		table[v].GetRef()=2;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,1);
		table[v].GetRef()=3;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)->Get()==1);
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,-1)->Get()==0);
		table.erase(v);
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
	}
	void testHook3()
	{
		typedef Physvector<3,int> vect;
		typedef HashPhysvector<3,int> Hash;
		Hash hash;
		typedef Hookable_Hash_Table<Hook_Neighbour_List,vect,Neighbour_List<3,int>,true,Hash> type_table;
		type_table table0(Neighbour_List<3,int>(200),hash);
		Datas_Without_Base<type_table> table(table0);
		vect v;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=0;
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		table[v].GetRef()=1;
		v.Set(1,0);
		v.Set(2,1);
		v.Set(3,0);
		table[v].GetRef()=2;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,1);
		table[v].GetRef()=3;
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)!=nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)->Get()==1);
		v.Set(1,1);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,-1)!=nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,-1)->Get()==0);
		table.erase(v);
		v.Set(1,0);
		v.Set(2,0);
		v.Set(3,0);
		TS_ASSERT(table[v].GetNeighbour(1,-1)==nullptr);
		TS_ASSERT(table[v].GetNeighbour(1,1)==nullptr);
	}
};
