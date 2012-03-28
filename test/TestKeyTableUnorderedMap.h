#include <cxxtest/TestSuite.h>
#include "../src/KeyTableUnorderedMap.h"
#include "../src/HashPhysvector.h"
#include "../src/PhysvectorKeyOrder.h"
#define eps 1e-10
class Test_KeyTableMap : public CxxTest::TestSuite
{
	KeyTableUnorderedMap<int,double> m_map;
public:
	void setUp(){
	m_map= KeyTableUnorderedMap<int,double> ();
	m_map[0]=1.0;
	m_map[1]=2.0;
	m_map[5]=4.0;
}
void testCreation(){
	TS_ASSERT_DELTA(m_map[0],1.0,eps);
	m_map[0]=3.0;
	TS_ASSERT_DELTA(m_map[0],3.0,eps);
	m_map.insert(8,2.0);
	TS_ASSERT_DELTA(m_map[8],2.0,eps);
	TS_ASSERT(!m_map.Exist(10));
	TS_ASSERT(m_map.Exist(0));
	TS_ASSERT_EQUALS(m_map.size(),4);
	TS_ASSERT(!m_map.empty());
	KeyTableUnorderedMap<int,double> temp;
	TS_ASSERT(temp.empty());
	m_map.erase(0);
	TS_ASSERT(!m_map.Exist(0));
}

void testPhysvector()
{
	typedef Physvector<3,int> vect;
	typedef HashPhysvector<3,int> Hash;
	Hash hash;
	KeyTableUnorderedMap<vect,double,Hash> table(hash);
	vect v;
	v.Set(1,4);
	v.Set(2,6);
	v.Set(3,9);
	table[v]=5.0;
	TS_ASSERT_DELTA(table[v],5.0,eps);
	for(int i=0;i<=0;++i)
	{
		v.Set(1,i);
		for(int j=0;j<=0;++j)
		{
			v.Set(2,j);
			for(int k=0;k<=0;++k)
			{
				v.Set(3,k);
				table[v]=i*j*k*0.1;
			}
		}
	}
	
}

};
