#include <cxxtest/TestSuite.h>
#include "../src/Math_Set2.h"
#include <iostream>

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
	void xtestbasic2d()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=3;++i)
		{
			for(int j=0;j<=3;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
		
		Math_Set2<2,int> B;
		k.Set(1,1);
		k.Set(2,1);
		B.Insert(k);
		k.Set(1,1);
		k.Set(2,2); 
		B.Insert(k);
		k.Set(1,2);
		k.Set(2,1);
		B.Insert(k);
		k.Set(1,2);
		k.Set(2,2);
		B.Insert(k);
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	void xtestavanced_1_2d()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;

		for(int i=0;i<=7;++i)
		{
			for(int j=0;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
		

		for(int i=0;i<=2;++i)
		{
			for(int j=7;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
		
		
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
		
		Math_Set2<2,int> B;
		for(int i=2;i<=5;++i)
		{
			for(int j=2;j<=4;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				B.Insert(k);
			}
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	
	void xtestavanced_2_2d()
	{
		Math_Set2<2,int> A;
		Physvector<2,int> k;
		
		for(int i=0;i<=2;++i)
		{
			for(int j=0;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}

		for(int i=3;i<=7;++i)
		{
			for(int j=0;j<=2;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
	
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				A.Insert(k);
			}
		}
		
		Math_Set2<2,int> B;
		for(int i=4;i<=10;++i)
		{
			for(int j=4;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				B.Insert(k);
			}
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
};
