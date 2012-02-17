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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestExtrapolateCellFluid.h"

static Test_MacConvect suite_Test_MacConvect;

static CxxTest::List Tests_Test_MacConvect = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacConvect( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestExtrapolateCellFluid.h", 13, "Test_MacConvect", suite_Test_MacConvect, Tests_Test_MacConvect );

static class TestDescription_Test_MacConvect_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_test1d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 16, "test1d" ) {}
 void runTest() { suite_Test_MacConvect.test1d(); }
} testDescription_Test_MacConvect_test1d;

static class TestDescription_Test_MacConvect_test1dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_test1dvar() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 66, "test1dvar" ) {}
 void runTest() { suite_Test_MacConvect.test1dvar(); }
} testDescription_Test_MacConvect_test1dvar;

static class TestDescription_Test_MacConvect_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_test2d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 119, "test2d" ) {}
 void runTest() { suite_Test_MacConvect.test2d(); }
} testDescription_Test_MacConvect_test2d;

static class TestDescription_Test_MacConvect_test2dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_test2dvar() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 197, "test2dvar" ) {}
 void runTest() { suite_Test_MacConvect.test2dvar(); }
} testDescription_Test_MacConvect_test2dvar;

#include <cxxtest/Root.cpp>
