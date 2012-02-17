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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestComputeSpeedLaplacien.h"

static Test_ComputeSpeedLaplacien suite_Test_ComputeSpeedLaplacien;

static CxxTest::List Tests_Test_ComputeSpeedLaplacien = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_ComputeSpeedLaplacien( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestComputeSpeedLaplacien.h", 11, "Test_ComputeSpeedLaplacien", suite_Test_ComputeSpeedLaplacien, Tests_Test_ComputeSpeedLaplacien );

static class TestDescription_Test_ComputeSpeedLaplacien_test1dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ComputeSpeedLaplacien_test1dconst() : CxxTest::RealTestDescription( Tests_Test_ComputeSpeedLaplacien, suiteDescription_Test_ComputeSpeedLaplacien, 14, "test1dconst" ) {}
 void runTest() { suite_Test_ComputeSpeedLaplacien.test1dconst(); }
} testDescription_Test_ComputeSpeedLaplacien_test1dconst;

static class TestDescription_Test_ComputeSpeedLaplacien_test2dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ComputeSpeedLaplacien_test2dconst() : CxxTest::RealTestDescription( Tests_Test_ComputeSpeedLaplacien, suiteDescription_Test_ComputeSpeedLaplacien, 49, "test2dconst" ) {}
 void runTest() { suite_Test_ComputeSpeedLaplacien.test2dconst(); }
} testDescription_Test_ComputeSpeedLaplacien_test2dconst;

static class TestDescription_Test_ComputeSpeedLaplacien_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ComputeSpeedLaplacien_test1d() : CxxTest::RealTestDescription( Tests_Test_ComputeSpeedLaplacien, suiteDescription_Test_ComputeSpeedLaplacien, 96, "test1d" ) {}
 void runTest() { suite_Test_ComputeSpeedLaplacien.test1d(); }
} testDescription_Test_ComputeSpeedLaplacien_test1d;

static class TestDescription_Test_ComputeSpeedLaplacien_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ComputeSpeedLaplacien_test2d() : CxxTest::RealTestDescription( Tests_Test_ComputeSpeedLaplacien, suiteDescription_Test_ComputeSpeedLaplacien, 132, "test2d" ) {}
 void runTest() { suite_Test_ComputeSpeedLaplacien.test2d(); }
} testDescription_Test_ComputeSpeedLaplacien_test2d;

#include <cxxtest/Root.cpp>
