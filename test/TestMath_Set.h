#include <cxxtest/TestSuite.h>
#include "../src/Math_Set.h"
#include <iostream>

using namespace std;
#define eps 1e-10
class Test_ApplyToVectorElement : public CxxTest::TestSuite
{
	public:
	void testbasic1d()
	{
		Math_Set<1,int> A;
		Physvector<1,int> k;
		k.Set(1,3);
		A.Insert(k);
		k.Set(1,6);
		A.Insert(k);
		
		Math_Set<1,int> B;
		k.Set(1,4);
		B.Insert(k);
		k.Set(1,5);
		B.Insert(k);
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	
	void testbasic2_1d()
	{
		Math_Set<1,int> A;
		Physvector<1,int> k;
		k.Set(1,-2);
		A.Insert(k);
		k.Set(1,2);
		A.Insert(k);
		k.Set(1,3);
		A.Insert(k);
		k.Set(1,6);
		A.Insert(k);
		
		Math_Set<1,int> B;
		k.Set(1,4);
		B.Insert(k);
		k.Set(1,5);
		B.Insert(k);
		k.Set(1,-1);
		B.Insert(k);
		k.Set(1,1);
		B.Insert(k);
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	
	void testbasic3_1d()
	{
		Math_Set<1,int> A;
		Physvector<1,int> k;
		k.Set(1,-1);
		A.Insert(k);
		k.Set(1,1);
		A.Insert(k);
		
		Math_Set<1,int> B;
		k.Set(1,4);
		B.Insert(k);
		k.Set(1,8);
		B.Insert(k);
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
	void testJoin1d()
	{
		Math_Set<1,int> A;
		Physvector<1,int> k;
		k.Set(1,1);
		A.Insert(k);
		k.Set(1,2);
		A.Insert(k);
		k.Set(1,3);
		A.Insert(k);
		k.Set(1,4);
		A.Insert(k);
		
		Math_Set<1,int> B;
		k.Set(1,0);
		B.Insert(k);
		k.Set(1,5);
		B.Insert(k);
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::A_In_B);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::B_In_A);
	}
	void testbasic2d()
	{
		Math_Set<2,int> A;
		Physvector<2,int> k;
		k.Set(1,0);
		k.Set(2,0);
		A.Insert(k);
		k.Set(1,0);
		k.Set(2,1);
		A.Insert(k);
		k.Set(1,0);
		k.Set(2,2);
		A.Insert(k);
		k.Set(1,0);
		k.Set(2,3);
		A.Insert(k);
		k.Set(1,1);
		k.Set(2,3);
		A.Insert(k);
		k.Set(1,2);
		k.Set(2,3);
		A.Insert(k);
		k.Set(1,3);
		k.Set(2,3);
		A.Insert(k);
		k.Set(1,3);
		k.Set(2,2);
		A.Insert(k);
		k.Set(1,3);
		k.Set(2,1);
		A.Insert(k);
		k.Set(1,3);
		k.Set(2,0);
		A.Insert(k);
		k.Set(1,2);
		k.Set(2,0);
		A.Insert(k);
		k.Set(1,1);
		k.Set(2,0);
		A.Insert(k);
		
		Math_Set<2,int> B;
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
	void testavanced_1_2d()
	{
		Math_Set<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=11;++i)
		{
			k.Set(1,0);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=0;i<=7;++i)
		{
			k.Set(1,i);
			k.Set(2,11);
			A.Insert(k);
		}
		for(int i=11;i>=8;--i)
		{
			k.Set(1,7);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=7;i>=2;--i)
		{
			k.Set(1,i);
			k.Set(2,8);
			A.Insert(k);
		}
		for(int i=8;i>=6;--i)
		{
			k.Set(1,2);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=2;i<=7;++i)
		{
			k.Set(1,i);
			k.Set(2,6);
			A.Insert(k);
		}
		for(int i=6;i>=0;--i)
		{
			k.Set(1,7);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=7;i>=0;--i)
		{
			k.Set(1,i);
			k.Set(2,0);
			A.Insert(k);
		}
		
		
		Math_Set<2,int> B;
		for(int i=2;i<=5;++i)
		{
			k.Set(1,i);
			k.Set(2,4);
			B.Insert(k);
		}
		for(int i=4;i>=2;--i)
		{
			k.Set(1,5);
			k.Set(2,i);
			B.Insert(k);
		}
		for(int i=5;i>=2;--i)
		{
			k.Set(1,i);
			k.Set(2,2);
			B.Insert(k);
		}
		for(int i=2;i<=4;++i)
		{
			k.Set(1,2);
			k.Set(2,i);
			B.Insert(k);
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	
	void testavanced_2_2d()
	{
		Math_Set<2,int> A;
		Physvector<2,int> k;
		for(int i=0;i<=11;++i)
		{
			k.Set(1,0);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=0;i<=7;++i)
		{
			k.Set(1,i);
			k.Set(2,11);
			A.Insert(k);
		}
		for(int i=11;i>=8;--i)
		{
			k.Set(1,7);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=7;i>=2;--i)
		{
			k.Set(1,i);
			k.Set(2,8);
			A.Insert(k);
		}
		for(int i=8;i>=2;--i)
		{
			k.Set(1,2);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=2;i<=7;++i)
		{
			k.Set(1,i);
			k.Set(2,2);
			A.Insert(k);
		}
		for(int i=2;i>=0;--i)
		{
			k.Set(1,7);
			k.Set(2,i);
			A.Insert(k);
		}
		for(int i=7;i>=0;--i)
		{
			k.Set(1,i);
			k.Set(2,0);
			A.Insert(k);
		}
		
		
		Math_Set<2,int> B;
		for(int i=4;i<=10;++i)
		{
			k.Set(1,i);
			k.Set(2,6);
			B.Insert(k);
		}
		for(int i=6;i>=4;--i)
		{
			k.Set(1,10);
			k.Set(2,i);
			B.Insert(k);
		}
		for(int i=10;i>=4;--i)
		{
			k.Set(1,i);
			k.Set(2,4);
			B.Insert(k);
		}
		for(int i=4;i<=6;++i)
		{
			k.Set(1,4);
			k.Set(2,i);
			B.Insert(k);
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
	
	void testavanced_1_3d()
	{
		Math_Set<3,int> A;
		Physvector<3,int> k;
		for(int i=0;i<=11;++i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,0);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=0;i<=7;++i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,i);
				k.Set(2,11);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=11;i>=8;--i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,7);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=7;i>=2;--i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,i);
				k.Set(2,8);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=8;i>=6;--i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,2);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=2;i<=7;++i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,i);
				k.Set(2,6);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=6;i>=0;--i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,7);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int i=7;i>=0;--i)
		{
			for(int j=1;j<=9;++j)
			{
				k.Set(1,i);
				k.Set(2,0);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		
		for(int i=0;i<=7;++i)
		{
			for(int j=0;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=0;i<=7;++i)
		{
			for(int j=0;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		
		
		
		for(int i=0;i<=2;++i)
		{
			for(int j=7;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=0;i<=2;++i)
		{
			for(int j=7;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		
		
		
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		Math_Set<3,int> B;
		for(int i=2;i<=5;++i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,i);
				k.Set(2,4);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		for(int i=4;i>=2;--i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,5);
				k.Set(2,i);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		for(int i=5;i>=2;--i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,i);
				k.Set(2,2);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		for(int i=2;i<=4;++i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,2);
				k.Set(2,i);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		
		for(int i=2;i<=5;++i)
		{
			for(int j=2;j<=4;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,2);
				B.Insert(k);
			}
		}
		
		for(int i=2;i<=5;++i)
		{
			for(int j=2;j<=4;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,8);
				B.Insert(k);
			}
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::B_In_A);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::A_In_B);
	}
	
	
	void testavanced_2_3d()
	{
		Math_Set<3,int> A;
		Physvector<3,int> k;
		for(int j=1;j<=9;++j)
		{
			for(int i=0;i<=11;++i)
			{
				k.Set(1,0);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=0;i<=7;++i)
			{
				k.Set(1,i);
				k.Set(2,11);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=11;i>=8;--i)
			{
				k.Set(1,7);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=7;i>=2;--i)
			{
				k.Set(1,i);
				k.Set(2,8);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=8;i>=2;--i)
			{
				k.Set(1,2);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=2;i<=7;++i)
			{
				k.Set(1,i);
				k.Set(2,2);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=2;i>=0;--i)
			{
				k.Set(1,7);
				k.Set(2,i);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		for(int j=1;j<=9;++j)
		{
			for(int i=7;i>=0;--i)
			{
				k.Set(1,i);
				k.Set(2,0);
				k.Set(3,j);
				A.Insert(k);
			}
		}
		
		
		for(int i=0;i<=2;++i)
		{
			for(int j=0;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=0;i<=2;++i)
		{
			for(int j=0;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		
		
		
		
		for(int i=3;i<=7;++i)
		{
			for(int j=0;j<=2;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=3;i<=7;++i)
		{
			for(int j=0;j<=2;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		
		
		
		
		
		
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,0);
				A.Insert(k);
			}
		}
		
		for(int i=3;i<=7;++i)
		{
			for(int j=8;j<=11;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,10);
				A.Insert(k);
			}
		}
		
		Math_Set<3,int> B;
		
		for(int i=4;i<=10;++i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,i);
				k.Set(2,6);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		
		
		for(int i=6;i>=4;--i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,10);
				k.Set(2,i);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		
		for(int i=10;i>=4;--i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,i);
				k.Set(2,4);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		
		for(int i=4;i<=6;++i)
		{
			for(int j=3;j<=7;++j)
			{
				k.Set(1,4);
				k.Set(2,i);
				k.Set(3,j);
				B.Insert(k);
			}
		}
		
		
		
		
		
		for(int i=4;i<=10;++i)
		{
			for(int j=4;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,2);
				B.Insert(k);
			}
		}
		
		for(int i=4;i<=10;++i)
		{
			for(int j=4;j<=6;++j)
			{
				k.Set(1,i);
				k.Set(2,j);
				k.Set(3,8);
				B.Insert(k);
			}
		}
		
		TS_ASSERT(A.IsIn(B)==Rel_Ensemble::NONE);
		TS_ASSERT(B.IsIn(A)==Rel_Ensemble::NONE);
	}
};