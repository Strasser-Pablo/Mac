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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellFluid.h"

static Test_UpdateCellFluid suite_Test_UpdateCellFluid;

static CxxTest::List Tests_Test_UpdateCellFluid = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_UpdateCellFluid( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellFluid.h", 11, "Test_UpdateCellFluid", suite_Test_UpdateCellFluid, Tests_Test_UpdateCellFluid );

static class TestDescription_Test_UpdateCellFluid_testupdate : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_UpdateCellFluid_testupdate() : CxxTest::RealTestDescription( Tests_Test_UpdateCellFluid, suiteDescription_Test_UpdateCellFluid, 14, "testupdate" ) {}
 void runTest() { suite_Test_UpdateCellFluid.testupdate(); }
} testDescription_Test_UpdateCellFluid_testupdate;

#include <cxxtest/Root.cpp>
