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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestRounding.h"

static Test_Rounding suite_Test_Rounding;

static CxxTest::List Tests_Test_Rounding = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_Rounding( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestRounding.h", 4, "Test_Rounding", suite_Test_Rounding, Tests_Test_Rounding );

static class TestDescription_Test_Rounding_testRound : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Rounding_testRound() : CxxTest::RealTestDescription( Tests_Test_Rounding, suiteDescription_Test_Rounding, 7, "testRound" ) {}
 void runTest() { suite_Test_Rounding.testRound(); }
} testDescription_Test_Rounding_testRound;

static class TestDescription_Test_Rounding_testCeil : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Rounding_testCeil() : CxxTest::RealTestDescription( Tests_Test_Rounding, suiteDescription_Test_Rounding, 22, "testCeil" ) {}
 void runTest() { suite_Test_Rounding.testCeil(); }
} testDescription_Test_Rounding_testCeil;

static class TestDescription_Test_Rounding_testFloor : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Rounding_testFloor() : CxxTest::RealTestDescription( Tests_Test_Rounding, suiteDescription_Test_Rounding, 37, "testFloor" ) {}
 void runTest() { suite_Test_Rounding.testFloor(); }
} testDescription_Test_Rounding_testFloor;

#include <cxxtest/Root.cpp>
