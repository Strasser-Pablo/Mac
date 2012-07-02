#include <cxxtest/TestSuite.h>
#include "../src/RundingFunction.h"
#define eps 1e-10
class Test_Rounding : public CxxTest::TestSuite
{
public:
	void testRound(){
		TS_ASSERT_EQUALS((round<double,int>(4.4)),4);
		TS_ASSERT_EQUALS((round<double,int>(4.6)),5);
		TS_ASSERT_EQUALS((round<double,long>(4.4)),4);
		TS_ASSERT_EQUALS((round<double,long>(4.6)),5);
		
		TS_ASSERT_EQUALS((round<float,int>(4.4)),4);
		TS_ASSERT_EQUALS((round<float,int>(4.6)),5);
		TS_ASSERT_EQUALS((round<float,long>(4.4)),4);
		TS_ASSERT_EQUALS((round<float,long>(4.6)),5);
		
		Round<double,int> R;
		TS_ASSERT_EQUALS((R(4.4)),4);
		TS_ASSERT_EQUALS((R(4.6)),5);
	}
	void testCeil(){
		TS_ASSERT_EQUALS((ceil<double,int>(4.4)),5);
		TS_ASSERT_EQUALS((ceil<double,int>(4.6)),5);
		TS_ASSERT_EQUALS((ceil<double,long>(4.4)),5);
		TS_ASSERT_EQUALS((ceil<double,long>(4.6)),5);
		
		TS_ASSERT_EQUALS((ceil<float,int>(4.4)),5);
		TS_ASSERT_EQUALS((ceil<float,int>(4.6)),5);
		TS_ASSERT_EQUALS((ceil<float,long>(4.4)),5);
		TS_ASSERT_EQUALS((ceil<float,long>(4.6)),5);
		
		Ceil<double,int> R;
		TS_ASSERT_EQUALS((R(4.4)),5);
		TS_ASSERT_EQUALS((R(4.6)),5);
	}
	void testFloor(){
		TS_ASSERT_EQUALS((floor<double,int>(4.4)),4);
		TS_ASSERT_EQUALS((floor<double,int>(4.6)),4);
		TS_ASSERT_EQUALS((floor<double,long>(4.4)),4);
		TS_ASSERT_EQUALS((floor<double,long>(4.6)),4);
		
		TS_ASSERT_EQUALS((floor<float,int>(4.4)),4);
		TS_ASSERT_EQUALS((floor<float,int>(4.6)),4);
		TS_ASSERT_EQUALS((floor<float,long>(4.4)),4);
		TS_ASSERT_EQUALS((floor<float,long>(4.6)),4);
		
		Floor<double,int> R;
		TS_ASSERT_EQUALS((R(4.4)),4);
		TS_ASSERT_EQUALS((R(4.6)),4);
	}
};