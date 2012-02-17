#include <cxxtest/TestSuite.h>
#include "../src/MacCell.h"
#define eps 1e-10
class Test_MacCell : public CxxTest::TestSuite
{
	MacCell<3,double,double> m_mac;
public:
	void testcreation(){
		Physvector<3,double> v;
		v.Set(USEELLIPSE,2.0,3.0,5.0);
		Physvector<3,double> v2;
		MacCell<3,double,double> temp(v,4.0);
		double p;
		temp.GetPressure(p);
		TS_ASSERT_DELTA(p,4.0,eps);
	    
		temp.GetSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		temp.SetPressure(10.0);
		temp.GetPressure(p);
		TS_ASSERT_DELTA(p,10.0,eps);
		
		v.Set(USEELLIPSE,1.0,6.0,7.0);
		temp.SetSpeed(v);
		temp.GetSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		
		v.Set(USEELLIPSE,89.0,32.0,54.0);
		temp.SetTempSpeed(v);
		temp.GetTempSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		
		v.Set(USEELLIPSE,89.0,32.0,54.0);
		temp.SetTempSpeed(v);
		temp.TempToSpeed();
		temp.GetSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		
		v.Set(USEELLIPSE,89.0,32.0,54.0);
		temp.SetSpeed(v);
		temp.SpeedToTemp();
		temp.GetTempSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		
		temp.SetCellType(2.0);
		temp.GetCellType(p);
		TS_ASSERT_DELTA(2.0,p,eps);
		
		v.Set(USEELLIPSE,2.0,3.0,5.0);
		MacCell<3,double,double> temp2(v,4.0,5.0);
		temp2.GetPressure(p);
		TS_ASSERT_DELTA(p,4.0,eps);
	    
		temp2.GetSpeed(v2);
		TS_ASSERT_EQUALS(v,v2);
		
		temp2.GetCellType(p);
		
		TS_ASSERT_DELTA(p,5.0,eps);
	}
	
};