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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacGetVelocity.h"

static Test_MacGetVelocity suite_Test_MacGetVelocity;

static CxxTest::List Tests_Test_MacGetVelocity = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacGetVelocity( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacGetVelocity.h", 13, "Test_MacGetVelocity", suite_Test_MacGetVelocity, Tests_Test_MacGetVelocity );

static class TestDescription_Test_MacGetVelocity_test1dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGetVelocity_test1dconst() : CxxTest::RealTestDescription( Tests_Test_MacGetVelocity, suiteDescription_Test_MacGetVelocity, 16, "test1dconst" ) {}
 void runTest() { suite_Test_MacGetVelocity.test1dconst(); }
} testDescription_Test_MacGetVelocity_test1dconst;

static class TestDescription_Test_MacGetVelocity_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGetVelocity_test1d() : CxxTest::RealTestDescription( Tests_Test_MacGetVelocity, suiteDescription_Test_MacGetVelocity, 49, "test1d" ) {}
 void runTest() { suite_Test_MacGetVelocity.test1d(); }
} testDescription_Test_MacGetVelocity_test1d;

static class TestDescription_Test_MacGetVelocity_test2dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGetVelocity_test2dconst() : CxxTest::RealTestDescription( Tests_Test_MacGetVelocity, suiteDescription_Test_MacGetVelocity, 82, "test2dconst" ) {}
 void runTest() { suite_Test_MacGetVelocity.test2dconst(); }
} testDescription_Test_MacGetVelocity_test2dconst;

static class TestDescription_Test_MacGetVelocity_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGetVelocity_test2d() : CxxTest::RealTestDescription( Tests_Test_MacGetVelocity, suiteDescription_Test_MacGetVelocity, 128, "test2d" ) {}
 void runTest() { suite_Test_MacGetVelocity.test2d(); }
} testDescription_Test_MacGetVelocity_test2d;

#include <cxxtest/Root.cpp>
