#include <cxxtest/TestSuite.h>
#include "../src/Data_Base_Dim_Type.h"
#include "../src/Data_Staggered_Left.h"
#include "../src/Data_Particle.h"
#include "../src/Data_Particles_List.h"
#define eps 1e-10
class TestData_Particles_List : public CxxTest::TestSuite  //LCOV_EXCL_LINE 
{
	public:
	void test1()
	{
		typedef Data_Base_Dim_Type<double,3> DataBase0;
		DataBase0 base0;
		typedef Data_Staggered_Left<DataBase0> DataBase;
		DataBase base(base0);
		typedef Data_Particle<DataBase> type_particle;
		typedef Data_Particles_List<type_particle,DataBase> type_list;
		type_list m_list(base);
		type_particle part;
		part.GetParticlePosRef().Set(1,2.0);
		part.GetParticlePosRef().Set(2,5.0);
		part.GetParticlePosRef().Set(3,3.0);
		m_list.GetRefToParticleList().push_back(part);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePosRef().Get(1),2.0,eps);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePosRef().Get(2),5.0,eps);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePosRef().Get(3),3.0,eps);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePos().Get(1),2.0,eps);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePos().Get(2),5.0,eps);
		TS_ASSERT_DELTA(m_list.GetRefToParticleList().back().GetParticlePos().Get(3),3.0,eps);
	}
};
