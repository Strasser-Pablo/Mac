/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestParticleToKey.h"

static Test_ParticleToKey suite_Test_ParticleToKey;

static CxxTest::List Tests_Test_ParticleToKey = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_ParticleToKey( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestParticleToKey.h", 6, "Test_ParticleToKey", suite_Test_ParticleToKey, Tests_Test_ParticleToKey );

static class TestDescription_Test_ParticleToKey_testToKey : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ParticleToKey_testToKey() : CxxTest::RealTestDescription( Tests_Test_ParticleToKey, suiteDescription_Test_ParticleToKey, 9, "testToKey" ) {}
 void runTest() { suite_Test_ParticleToKey.testToKey(); }
} testDescription_Test_ParticleToKey_testToKey;

#include <cxxtest/Root.cpp>
