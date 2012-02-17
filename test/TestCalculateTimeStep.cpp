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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestCalculateTimeStep.h"

static Test_CalculateTimeStep suite_Test_CalculateTimeStep;

static CxxTest::List Tests_Test_CalculateTimeStep = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_CalculateTimeStep( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestCalculateTimeStep.h", 12, "Test_CalculateTimeStep", suite_Test_CalculateTimeStep, Tests_Test_CalculateTimeStep );

static class TestDescription_Test_CalculateTimeStep_testCalculate : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_CalculateTimeStep_testCalculate() : CxxTest::RealTestDescription( Tests_Test_CalculateTimeStep, suiteDescription_Test_CalculateTimeStep, 17, "testCalculate" ) {}
 void runTest() { suite_Test_CalculateTimeStep.testCalculate(); }
} testDescription_Test_CalculateTimeStep_testCalculate;

#include <cxxtest/Root.cpp>
