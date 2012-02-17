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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMaximalSpeed.h"

static Test_MaximalSpeed suite_Test_MaximalSpeed;

static CxxTest::List Tests_Test_MaximalSpeed = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MaximalSpeed( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMaximalSpeed.h", 10, "Test_MaximalSpeed", suite_Test_MaximalSpeed, Tests_Test_MaximalSpeed );

static class TestDescription_Test_MaximalSpeed_Test_Max : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MaximalSpeed_Test_Max() : CxxTest::RealTestDescription( Tests_Test_MaximalSpeed, suiteDescription_Test_MaximalSpeed, 14, "Test_Max" ) {}
 void runTest() { suite_Test_MaximalSpeed.Test_Max(); }
} testDescription_Test_MaximalSpeed_Test_Max;

#include <cxxtest/Root.cpp>
