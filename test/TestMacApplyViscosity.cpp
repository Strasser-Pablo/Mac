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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacApplyViscosity.h"

static Test_MacApplyViscosity suite_Test_MacApplyViscosity;

static CxxTest::List Tests_Test_MacApplyViscosity = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacApplyViscosity( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacApplyViscosity.h", 11, "Test_MacApplyViscosity", suite_Test_MacApplyViscosity, Tests_Test_MacApplyViscosity );

static class TestDescription_Test_MacApplyViscosity_test1dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacApplyViscosity_test1dconst() : CxxTest::RealTestDescription( Tests_Test_MacApplyViscosity, suiteDescription_Test_MacApplyViscosity, 14, "test1dconst" ) {}
 void runTest() { suite_Test_MacApplyViscosity.test1dconst(); }
} testDescription_Test_MacApplyViscosity_test1dconst;

static class TestDescription_Test_MacApplyViscosity_test2dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacApplyViscosity_test2dconst() : CxxTest::RealTestDescription( Tests_Test_MacApplyViscosity, suiteDescription_Test_MacApplyViscosity, 49, "test2dconst" ) {}
 void runTest() { suite_Test_MacApplyViscosity.test2dconst(); }
} testDescription_Test_MacApplyViscosity_test2dconst;

static class TestDescription_Test_MacApplyViscosity_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacApplyViscosity_test1d() : CxxTest::RealTestDescription( Tests_Test_MacApplyViscosity, suiteDescription_Test_MacApplyViscosity, 97, "test1d" ) {}
 void runTest() { suite_Test_MacApplyViscosity.test1d(); }
} testDescription_Test_MacApplyViscosity_test1d;

static class TestDescription_Test_MacApplyViscosity_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacApplyViscosity_test2d() : CxxTest::RealTestDescription( Tests_Test_MacApplyViscosity, suiteDescription_Test_MacApplyViscosity, 134, "test2d" ) {}
 void runTest() { suite_Test_MacApplyViscosity.test2d(); }
} testDescription_Test_MacApplyViscosity_test2d;

#include <cxxtest/Root.cpp>
