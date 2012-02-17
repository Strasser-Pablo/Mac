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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestParticle.h"

static Test_Partice suite_Test_Partice;

static CxxTest::List Tests_Test_Partice = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_Partice( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestParticle.h", 4, "Test_Partice", suite_Test_Partice, Tests_Test_Partice );

static class TestDescription_Test_Partice_testCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Partice_testCreation() : CxxTest::RealTestDescription( Tests_Test_Partice, suiteDescription_Test_Partice, 8, "testCreation" ) {}
 void runTest() { suite_Test_Partice.testCreation(); }
} testDescription_Test_Partice_testCreation;

#include <cxxtest/Root.cpp>
