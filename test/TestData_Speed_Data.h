#include <cxxtest/TestSuite.h>
#include "../src/Data_Speed_Data.h"
#include <utility>
#define eps 1e-10
class Test_Data_Speed_Data : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:

		void test_arithmetic()
		{
			typedef Data_Speed_Data<3,double> type_speed;
			type_speed s1;
			type_speed s2;
			s1.Set(1,3);
			s1.Set(2,6);
			s1.Set(3,1);

			s2.Set(1,4);
			s2.Set(2,2);
			s2.Set(3,4);
			type_speed s3=s1+s2;
			TS_ASSERT_DELTA(s3.Get(1),7,eps);
			TS_ASSERT_DELTA(s3.Get(2),8,eps);
			TS_ASSERT_DELTA(s3.Get(3),5,eps);

			s3=s1-s2;
			TS_ASSERT_DELTA(s3.Get(1),-1,eps);
			TS_ASSERT_DELTA(s3.Get(2),4,eps);
			TS_ASSERT_DELTA(s3.Get(3),-3,eps);

			s3=s1;
			s3+=s2;
			TS_ASSERT_DELTA(s3.Get(1),7,eps);
			TS_ASSERT_DELTA(s3.Get(2),8,eps);
			TS_ASSERT_DELTA(s3.Get(3),5,eps);

			s3=s1;
			s3-=s2;
			TS_ASSERT_DELTA(s3.Get(1),-1,eps);
			TS_ASSERT_DELTA(s3.Get(2),4,eps);
			TS_ASSERT_DELTA(s3.Get(3),-3,eps);

			double c=4;
			s3=s1*c;
			TS_ASSERT_DELTA(s3.Get(1),12,eps);
			TS_ASSERT_DELTA(s3.Get(2),24,eps);
			TS_ASSERT_DELTA(s3.Get(3),4,eps);

			s3=c*s1;
			TS_ASSERT_DELTA(s3.Get(1),12,eps);
			TS_ASSERT_DELTA(s3.Get(2),24,eps);
			TS_ASSERT_DELTA(s3.Get(3),4,eps);

			s3=s1/c;
			TS_ASSERT_DELTA(s3.Get(1),0.75,eps);
			TS_ASSERT_DELTA(s3.Get(2),1.5,eps);
			TS_ASSERT_DELTA(s3.Get(3),0.25,eps);

			s3=s1;
			s3*=c;
			TS_ASSERT_DELTA(s3.Get(1),12,eps);
			TS_ASSERT_DELTA(s3.Get(2),24,eps);
			TS_ASSERT_DELTA(s3.Get(3),4,eps);
			
			s3=s1;
			s3/=c;
			TS_ASSERT_DELTA(s3.Get(1),0.75,eps);
			TS_ASSERT_DELTA(s3.Get(2),1.5,eps);
			TS_ASSERT_DELTA(s3.Get(3),0.25,eps);
		}

		void test_Relation()
		{
			typedef Data_Speed_Data<3,double> type_speed;
			type_speed s1;
			type_speed s2;
			s1.Set(1,3);
			s1.Set(2,6);
			s1.Set(3,1);

			s2.Set(1,4);
			s2.Set(2,2);
			s2.Set(3,4);

			TS_ASSERT(!(s1==s2));
			TS_ASSERT((s1==s1));
			TS_ASSERT(!(s1!=s1));
			TS_ASSERT(s1!=s2);
		}
};
