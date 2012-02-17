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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacConvect.h"

static Test_MacConvect suite_Test_MacConvect;

static CxxTest::List Tests_Test_MacConvect = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacConvect( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacConvect.h", 15, "Test_MacConvect", suite_Test_MacConvect, Tests_Test_MacConvect );

static class TestDescription_Test_MacConvect_testconst1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_testconst1d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 18, "testconst1d" ) {}
 void runTest() { suite_Test_MacConvect.testconst1d(); }
} testDescription_Test_MacConvect_testconst1d;

static class TestDescription_Test_MacConvect_testconst2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_testconst2d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 63, "testconst2d" ) {}
 void runTest() { suite_Test_MacConvect.testconst2d(); }
} testDescription_Test_MacConvect_testconst2d;

static class TestDescription_Test_MacConvect_testvar1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_testvar1d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 118, "testvar1d" ) {}
 void runTest() { suite_Test_MacConvect.testvar1d(); }
} testDescription_Test_MacConvect_testvar1d;

static class TestDescription_Test_MacConvect_testvar2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_testvar2d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 163, "testvar2d" ) {}
 void runTest() { suite_Test_MacConvect.testvar2d(); }
} testDescription_Test_MacConvect_testvar2d;

#include <cxxtest/Root.cpp>
