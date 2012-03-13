#include <cxxtest/TestSuite.h>
#include "../src/Math_Set2.h"
#include <iostream>
#include <functional>

using namespace std;
#define eps 1e-10
class Test_ApplyToVectorElement : public CxxTest::TestSuite
{
	public:
	void testbasic1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,1);
		A.InsertMin(k);
		k.Set(1,4);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,2);
		B.InsertMin(k);
		k.Set(1,3);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);

	}
	
	void testbasic2_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,2);
		A.InsertMin(k);
		k.Set(1,3);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,1);
		B.InsertMin(k);
		k.Set(1,5);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_In_B);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_In_A);
	}
	
	void testbasic3_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,3);
		A.InsertMax(k);
		k.Set(1,2);
		A.InsertMin(k);
			
		Math_Set2<1,int> B;
		k.Set(1,1);
		B.InsertMin(k);
		k.Set(1,5);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_In_B);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_In_A);
	}

	void testbasic4_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,3);
		A.InsertMax(k);
		k.Set(1,2);
		A.InsertMin(k);
			
		Math_Set2<1,int> B;
		k.Set(1,0);
		B.InsertMin(k);
		k.Set(1,1);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
	
	void testAdvanced1_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,7);
		A.InsertMin(k);
		k.Set(1,10);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,2);
		B.InsertMin(k);
		k.Set(1,3);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testAdvanced2_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,10);
		A.InsertMin(k);
		k.Set(1,15);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,6);
		B.InsertMin(k);
		k.Set(1,7);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}

	void testAdvanced3_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,10);
		A.InsertMin(k);
		k.Set(1,15);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,11);
		B.InsertMin(k);
		k.Set(1,14);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testAdvanced4_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,10);
		A.InsertMin(k);
		k.Set(1,15);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,11);
		B.InsertMin(k);
		k.Set(1,14);
		B.InsertMax(k);
		k.Set(1,2);
		B.InsertMin(k);
		k.Set(1,3);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testAdvanced5_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,10);
		A.InsertMin(k);
		k.Set(1,15);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,6);
		B.InsertMin(k);
		k.Set(1,7);
		B.InsertMax(k);
		k.Set(1,16);
		B.InsertMin(k);
		k.Set(1,17);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}

	void testAdvanced6_1d()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,0);
		A.InsertMin(k);
		k.Set(1,5);
		A.InsertMax(k);
		k.Set(1,10);
		A.InsertMin(k);
		k.Set(1,15);
		A.InsertMax(k);
		k.Set(1,20);
		A.InsertMin(k);
		k.Set(1,25);
		A.InsertMax(k);
			
		Math_Set2<1,int> B;
		k.Set(1,11);
		B.InsertMin(k);
		k.Set(1,12);
		B.InsertMax(k);
		k.Set(1,21);
		B.InsertMin(k);
		k.Set(1,22);
		B.InsertMax(k);

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testAdvanced7_1d()
	{
		Math_Set2<1,int> A;
			
		Math_Set2<1,int> B;

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::Both_Empty);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::Both_Empty);
	}

	void testAdvanced8_1d()
	{
		Math_Set2<1,int> A;
			
		Math_Set2<1,int> B;
		Physvector<1,int> k;
		k.Set(1,4);
		B.InsertMin(k);
		k.Set(1,5);
		B.InsertMax(k);
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_Empty);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_Empty);
	}

	void testbasic2d()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=3;++i)
		{
			k.Set(2,0);
			k.Set(1,i);
			A.InsertMin(k);
			k.Set(2,3);
			A.InsertMax(k);
		}
		
		Math_Set2<2,int> B;
		for(int i=1;i<=2;++i)
		{
			k.Set(2,1);
			k.Set(1,i);
			B.InsertMin(k);
			k.Set(2,2);
			B.InsertMax(k);
		}
			
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		//TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testbasic2d_2()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=3;++i)
		{
			k.Set(2,0);
			k.Set(1,i);
			A.InsertMin(k);
			k.Set(2,3);
			A.InsertMax(k);
		}
		
		Math_Set2<2,int> B;
		for(int i=5;i<=7;++i)
		{
			k.Set(2,1);
			k.Set(1,i);
			B.InsertMin(k);
			k.Set(2,2);
			B.InsertMax(k);
		}
			
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}


	void testbasic2d_3()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=10;++i)
		{
			k.Set(2,1);
			k.Set(1,i);
			A.InsertMin(k);
			k.Set(2,10);
			A.InsertMax(k);
			k.Set(2,9);
			A.InsertMin(k);
			k.Set(2,2);
			A.InsertMax(k);
		}
		
		Math_Set2<2,int> B;
		for(int i=0;i<=10;++i)
		{
			k.Set(2,-4);
			k.Set(1,i);
			B.InsertMin(k);
			k.Set(2,-2);
			B.InsertMax(k);
			k.Set(2,14);
			B.InsertMax(k);
			k.Set(2,12);
			B.InsertMin(k);
		}
		
		for(int i=3;i<=12;++i)
		{
			k.Set(2,6);
			k.Set(1,i);
			B.InsertMax(k);
			k.Set(2,4);
			B.InsertMin(k);
		}

		for(int i=13;i<=15;++i)
		{
			k.Set(2,11);
			k.Set(1,i);
			B.InsertMax(k);
			k.Set(2,-1);
			k.Set(1,i);
			B.InsertMin(k);
		}

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
	
	void testbasic3d()
	{
		Math_Set2<3,int> A;
		Physvector<3,int> k;
		for(int i=0;i<=3;++i)
			for(int j=0;j<=3;++j)
			{
				k.Set(3,0);
				k.Set(2,j);
				k.Set(1,i);
				A.InsertMin(k);
				k.Set(3,3);
				A.InsertMax(k);
			}
		
		Math_Set2<3,int> B;
		for(int i=1;i<=2;++i)
		{
			for(int j=1;j<=2;++j)
			{
				k.Set(3,1);
				k.Set(2,j);
				k.Set(1,i);
				B.InsertMin(k);
				k.Set(3,2);
				B.InsertMax(k);
			}
		}	
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}

	void testbasic3d_2()
	{
		Math_Set2<3,int> A;
		Physvector<3,int> k;
		for(int i=0;i<=3;++i)
		{
			for(int j=0;j<=3;++j)
			{
			k.Set(3,0);
			k.Set(2,j);
			k.Set(1,i);
			A.InsertMin(k);
			k.Set(3,3);
			A.InsertMax(k);
			}
		}
		
		Math_Set2<3,int> B;
		for(int i=5;i<=7;++i)
		{
			for(int j=5;j<=7;++j)
			{
				k.Set(3,1);
				k.Set(2,j);
				k.Set(1,i);
				B.InsertMin(k);
				k.Set(3,2);
				B.InsertMax(k);
			}
		}
			
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}


	void testbasic3d_3()
	{
		Math_Set2<3,int> A;
		Physvector<3,int> k;
		for(int i=0;i<=10;++i)
		{
			for(int j=0;j<=10;++j)
			{
				k.Set(3,1);
				k.Set(2,j);
				k.Set(1,i);
				A.InsertMin(k);
				k.Set(3,10);
				A.InsertMax(k);
				k.Set(3,9);
				A.InsertMin(k);
				k.Set(3,2);
				A.InsertMax(k);
			}
		}
		
		Math_Set2<3,int> B;
		for(int i=0;i<=10;++i)
		{
			for(int j=0;j<=10;++j)
			{
				k.Set(3,-4);
				k.Set(2,j);
				k.Set(1,i);
				B.InsertMin(k);
				k.Set(3,-2);
				B.InsertMax(k);
				k.Set(3,14);
				B.InsertMax(k);
				k.Set(3,12);
				B.InsertMin(k);
			}
		}
		for(int i=3;i<=12;++i)
		{
			for(int j=3;j<=12;++j)
			{
				k.Set(3,6);
				k.Set(2,j);
				k.Set(1,i);
				B.InsertMax(k);
				k.Set(3,4);
				B.InsertMin(k);
			}
		}

		for(int i=13;i<=15;++i)
		{
			for(int j=13;j<=15;++j)
			{
				k.Set(3,11);
				k.Set(2,j);
				k.Set(1,i);
				B.InsertMax(k);
				k.Set(3,-1);
				B.InsertMin(k);
			}
		}

		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}

	void testLaunchFunc()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,2);
		A.InsertMin(k);
		k.Set(1,4);
		A.InsertMax(k);
		int i=0;
		function<void(Physvector<1,int>)> f=[&i](Physvector<1,int> key)
		{
			TS_ASSERT_LESS_THAN(key.Get(1),4);
			TS_ASSERT(key.Get(1)>2);
			++i;
		};
		A.FillSet(f);
		TS_ASSERT_EQUALS(i,1);
	}
	

	void testLaunchFunc2()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		k.Set(1,1);
		k.Set(2,2);
		A.InsertMin(k);
		k.Set(1,1);
		k.Set(2,4);
		A.InsertMax(k);
		int i=0;
		function<void(Physvector<2,int>)> f=[&i](Physvector<2,int> key)
		{
			TS_ASSERT_LESS_THAN(key.Get(2),4);
			TS_ASSERT(key.Get(2)>2);
			++i;
		};
		A.FillSet(f);
		TS_ASSERT_EQUALS(i,1);
	}

	void testFillBound()
	{
		Math_Set2<1,int> A;
		Physvector<1,int> k;
		k.Set(1,2);
		A.InsertMin(k);
		k.Set(1,4);
		A.InsertMax(k);
		int i=0;
		function<void(Physvector<1,int>)> f=[&i](Physvector<1,int> key)
		{
			TS_ASSERT(key.Get(1)==2||key.Get(1)==4);
			++i;
		};
		A.FillBoundary(f);
		TS_ASSERT_EQUALS(i,2);
	}

	void testFillBound2d()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		k.Set(1,1);
		k.Set(2,2);
		A.InsertMin(k);
		k.Set(1,1);
		k.Set(2,4);
		A.InsertMax(k);
		k.Set(1,2);
		k.Set(2,3);
		A.InsertMin(k);
		k.Set(1,2);
		k.Set(2,8);
		A.InsertMax(k);
		int i=0;
		function<void(Physvector<2,int>)> f=[&i](Physvector<2,int> key)
		{
			TS_ASSERT((key.Get(1)==1&&(key.Get(2)==2||key.Get(2)==4))||(key.Get(1)==2&&(key.Get(2)==3||key.Get(2)==8)));
			++i;
		};
		A.FillBoundary(f);
		TS_ASSERT_EQUALS(i,4);
	}

	void testBasic2dIn()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;


		k.Set(1,6);
		k.Set(2,4);
		A.InsertMax(k);
		
		k.Set(1,7);
		k.Set(2,4);
		A.InsertMax(k);
		
		k.Set(1,6);
		k.Set(2,5);
		A.InsertMin(k);
		
		k.Set(1,7);
		k.Set(2,5);
		A.InsertMin(k);

		Math_Set2<2,int> B;

		k.Set(1,6);
		k.Set(2,8);
		B.InsertMax(k);
		
		k.Set(1,7);
		k.Set(2,8);
		B.InsertMax(k);
		
		k.Set(1,6);
		k.Set(2,-2);
		B.InsertMax(k);
		
		k.Set(1,7);
		k.Set(2,-2);
		B.InsertMax(k);
		
		
		k.Set(1,6);
		k.Set(2,-14);
		B.InsertMax(k);
		
		k.Set(1,7);
		k.Set(2,-14);
		B.InsertMax(k);
		
		k.Set(1,6);
		k.Set(2,-18);
		B.InsertMax(k);
		
		k.Set(1,7);
		k.Set(2,-18);
		B.InsertMax(k);
		
		k.Set(1,6);
		k.Set(2,-1);
		B.InsertMin(k);
		
		k.Set(1,7);
		k.Set(2,-1);
		B.InsertMin(k);
		
		k.Set(1,6);
		k.Set(2,-9);
		B.InsertMin(k);
		
		k.Set(1,7);
		k.Set(2,-9);
		B.InsertMin(k);
		
		k.Set(1,6);
		k.Set(2,-17);
		B.InsertMin(k);
		
		k.Set(1,7);
		k.Set(2,-17);
		B.InsertMin(k);

		k.Set(1,6);
		k.Set(2,-21);
		B.InsertMin(k);
		
		k.Set(1,7);
		k.Set(2,-21);
		B.InsertMin(k);
		
		k.Set(1,2);
		k.Set(2,-10);
		B.InsertMin(k);
		
		k.Set(1,2);
		k.Set(2,10);
		B.InsertMax(k);


		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_In_B);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_In_A);
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_In_B);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_In_A);
	}
};
