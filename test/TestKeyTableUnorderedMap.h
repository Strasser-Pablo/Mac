#include <cxxtest/TestSuite.h>
#include "../src/KeyTableUnorderedMap.h"
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
void testIterator(){
	KeyTableUnorderedMap<int,double>::iterator it=m_map.begin();
	TS_ASSERT_DELTA(*it,m_map[0],eps);
	TS_ASSERT_DELTA(it.data(),m_map[0],eps);
	TS_ASSERT_EQUALS(it.key(),0);
	KeyTableUnorderedMap<int,double>::iterator it2=++it;
	TS_ASSERT_DELTA(*it,m_map[1],eps);
	TS_ASSERT_DELTA(it.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it.key(),1);
	TS_ASSERT_DELTA(*it2,m_map[1],eps);
	TS_ASSERT_DELTA(it2.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it2.key(),1);
	it=m_map.begin();
	it2=it++;
	TS_ASSERT_DELTA(*it,m_map[1],eps);
	TS_ASSERT_DELTA(it.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it.key(),1);
	TS_ASSERT_DELTA(*it2,m_map[0],eps);
	TS_ASSERT_DELTA(it2.data(),m_map[0],eps);
	TS_ASSERT_EQUALS(it2.key(),0);
	
	 it=m_map.begin();
	m_map.erase(it);
	TS_ASSERT(!m_map.Exist(0));
	
	TS_ASSERT_DIFFERS(m_map.end(),m_map.begin());
	TS_ASSERT(m_map.end()!=m_map.begin());
	
	KeyTableUnorderedMap<int,double> temp;
	TS_ASSERT_EQUALS(temp.end(),temp.begin());
}
void testConstIterator(){
	KeyTableUnorderedMap<int,double>::const_iterator it=m_map.begin();
	TS_ASSERT_DELTA(*it,m_map[0],eps);
	TS_ASSERT_DELTA(it.data(),m_map[0],eps);
	TS_ASSERT_EQUALS(it.key(),0);
	KeyTableUnorderedMap<int,double>::const_iterator it2=++it;
	TS_ASSERT_DELTA(*it,m_map[1],eps);
	TS_ASSERT_DELTA(it.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it.key(),1);
	TS_ASSERT_DELTA(*it2,m_map[1],eps);
	TS_ASSERT_DELTA(it2.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it2.key(),1);
	it=m_map.begin();
	it2=it++;
	TS_ASSERT_DELTA(*it,m_map[1],eps);
	TS_ASSERT_DELTA(it.data(),m_map[1],eps);
	TS_ASSERT_EQUALS(it.key(),1);
	TS_ASSERT_DELTA(*it2,m_map[0],eps);
	TS_ASSERT_DELTA(it2.data(),m_map[0],eps);
	TS_ASSERT_EQUALS(it2.key(),0);
	
	
	
	KeyTableUnorderedMap<int,double> temp;
	KeyTableUnorderedMap<int,double>::const_iterator it3=temp.end();
	TS_ASSERT_EQUALS(it3,temp.begin());
	
	temp.insert(2,5.0);
	TS_ASSERT_DIFFERS(temp.end(),temp.begin());
	TS_ASSERT(temp.end()!=temp.begin());
	
	unordered_map<int,double> mymap;
	unordered_map<int,double>::const_iterator sit=mymap.begin();
	KeyTableUnorderedMapConstIterator<int,double,std::hash<int>, equal_to<int> > cit(sit);
	TS_ASSERT_EQUALS(cit.GetMapIterator(),mymap.begin());
	const KeyTableUnorderedMapConstIterator<int,double ,std::hash<int>, equal_to<int> > ccit=cit;
	TS_ASSERT_EQUALS(ccit.GetMapIterator(),mymap.begin());
	TS_ASSERT(!(cit!=cit));
	
	const KeyTableUnorderedMap<int,double> & map2=m_map;
	TS_ASSERT_EQUALS(map2.begin(),m_map.begin());
	TS_ASSERT_EQUALS(map2.end(),m_map.end());
}

};
