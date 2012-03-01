#include <cxxtest/TestSuite.h>
#include "../src/NDFor.h"
#include <functional>
#include <iostream>

using namespace std;
#define eps 1e-10
class TestNDFor : public CxxTest::TestSuite
{
public:
	void test1d()
	{
		Physvector<1,int> vect;
		vect.Set(1,0);
		int sum=0;
		int max=10;
		std::function<void(Physvector<1,int>)> f=[&sum](Physvector<1,int> k){sum+=k.Get(1); };
		NDFor<std::function<void(Physvector<1,int>)>,int,1> m_For(vect,max,f);
		m_For.Calculate();
		TS_ASSERT_EQUALS(sum,55);
	}
	void test2d()
	{
		Physvector<2,int> vect;
		vect.Set(1,0);
		vect.Set(2,0);
		int sum1=0;
		int sum2=0;
		int max=10;
		std::function<void(Physvector<2,int>)> f=[&sum1,&sum2](Physvector<2,int> k){sum1+=k.Get(1);sum2+=k.Get(2); };
		NDFor<std::function<void(Physvector<2,int>)>,int,2> m_For(vect,max,f);
		m_For.Calculate();
		TS_ASSERT_EQUALS(sum1,605);
		TS_ASSERT_EQUALS(sum2,605);
	}
	
	void test3d()
	{
		Physvector<3,int> vect;
		vect.Set(1,0);
		vect.Set(2,0);
		vect.Set(3,0);
		int sum1=0;
		int sum2=0;
		int sum3=0;
		int max=10;
		std::function<void(Physvector<3,int>)> f=[&sum1,&sum2,&sum3](Physvector<3,int> k){sum1+=k.Get(1);sum2+=k.Get(2); sum3+=k.Get(3);};
		NDFor<std::function<void(Physvector<3,int>)>,int,3> m_For(vect,max,f);
		m_For.Calculate();
		TS_ASSERT_EQUALS(sum1,6655);
		TS_ASSERT_EQUALS(sum2,6655);
	}
};