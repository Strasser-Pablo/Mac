#include <cxxtest/TestSuite.h>
#include "../src/TableContainerList.h"
#define eps 1e-10
class Test_ContainerList : public CxxTest::TestSuite
{
	TableContainerList<double> m_list;
public:
	void testCreation(){
		m_list.push_back(2.0);
		TS_ASSERT_DELTA(m_list.front(),2.0,eps);
		TS_ASSERT_DELTA(m_list.back(),2.0,eps);
		m_list.push_front(4.0);
		TS_ASSERT_DELTA(m_list.front(),4.0,eps);
		TS_ASSERT_DELTA(m_list.back(),2.0,eps);
		m_list.push_back(1.0);
		TS_ASSERT_DELTA(m_list.front(),4.0,eps);
		TS_ASSERT_DELTA(m_list.back(),1.0,eps);
		TS_ASSERT(!m_list.empty());
		TableContainerList<double>  temp;
		TS_ASSERT(temp.empty());
		TS_ASSERT_EQUALS(m_list.size(),3);
		TS_ASSERT_EQUALS(temp.size(),0);
		
		m_list.pop_back();
		TS_ASSERT_DELTA(m_list.back(),2.0,eps);
		m_list.pop_front();
		TS_ASSERT_DELTA(m_list.front(),2.0,eps);
		
		const TableContainerList<double> & c_mlist=m_list;
		TS_ASSERT_DELTA(c_mlist.back(),2.0,eps);
		TS_ASSERT_DELTA(c_mlist.front(),2.0,eps);
	}
	void testIterator()
	{
		m_list.push_front(4.0);
		TableContainerList<double>::iterator it=m_list.begin();
		TS_ASSERT_DELTA(*it,m_list.front(),eps);
		
		const TableContainerList<double>& cm_list=m_list;
		TableContainerList<double>::const_iterator it2=cm_list.begin();
		TS_ASSERT_DELTA(*it2,cm_list.front(),eps);
		
		TableContainerList<double>  temp;
		TS_ASSERT_EQUALS(temp.begin(),temp.end());
		const TableContainerList<double>  temp2;
		TS_ASSERT_EQUALS(temp2.begin(),temp2.end());
		
		TableContainerList<double>::iterator it3=m_list.insert(m_list.begin(),323.0);
		TS_ASSERT_DELTA(m_list.front(),323.0,eps);
		TS_ASSERT_DELTA(*it3,323.0,eps);
		++it3;
		TableContainerList<double>::iterator it4=m_list.erase(m_list.begin());
		TS_ASSERT_DELTA(m_list.front(),*it3,eps);
		TS_ASSERT_DELTA(*it4,m_list.front(),eps);
	}
	void TestIteratorArithmetique()
	{
		m_list.push_back(4.5);
		TS_ASSERT_DIFFERS(m_list.begin(),m_list.end());
		TS_ASSERT(m_list.begin()!=m_list.end());
		const TableContainerList<double> & cm_list=m_list;
		TS_ASSERT_DIFFERS(cm_list.begin(),cm_list.end());
		m_list.push_front(3.0);
		m_list.push_front(10.00);
		TableContainerList<double>::iterator it=m_list.begin();
		TS_ASSERT_DELTA(*it,10.0,eps);
		TableContainerList<double>::iterator it2=++it;
		TS_ASSERT_DELTA(*it,3.0,eps);
		TS_ASSERT_DELTA(*it2,3.0,eps);
		
		it=m_list.begin();
		it2=it++;
		TS_ASSERT_DELTA(*it,3.0,eps);
		TS_ASSERT_DELTA(*it2,10.0,eps);
		
		TableContainerList<double>::const_iterator it3=m_list.begin();
		TS_ASSERT_DELTA(*it3,10.0,eps);
		TableContainerList<double>::const_iterator it4=++it3;
		TS_ASSERT_DELTA(*it3,3.0,eps);
		TS_ASSERT_DELTA(*it4,3.0,eps);
		
		it3=m_list.begin();
		it4=it3++;
		TS_ASSERT_DELTA(*it3,3.0,eps);
		TS_ASSERT_DELTA(*it4,10.0,eps);
		
		const TableContainerList<double> & cm_list2=m_list;
		TS_ASSERT(cm_list2.begin()!=cm_list2.end());
		
		const list<double> m_lis;
		TableContainerList<double>::const_iterator it5(m_lis.begin());
		TS_ASSERT_EQUALS(it5.GetListIterator(),m_lis.begin());
		const TableContainerList<double>::const_iterator it6(m_lis.begin());
		TS_ASSERT_EQUALS(it6.GetListIterator(),m_lis.begin());
	}
};