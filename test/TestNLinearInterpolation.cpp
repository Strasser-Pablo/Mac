/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNLinearInterpolation.h"

static Test_NLinearInterpolation suite_Test_NLinearInterpolation;

static CxxTest::List Tests_Test_NLinearInterpolation = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_NLinearInterpolation( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNLinearInterpolation.h", 13, "Test_NLinearInterpolation", suite_Test_NLinearInterpolation, Tests_Test_NLinearInterpolation );

static class TestDescription_Test_NLinearInterpolation_test1dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NLinearInterpolation_test1dconst() : CxxTest::RealTestDescription( Tests_Test_NLinearInterpolation, suiteDescription_Test_NLinearInterpolation, 16, "test1dconst" ) {}
 void runTest() { suite_Test_NLinearInterpolation.test1dconst(); }
} testDescription_Test_NLinearInterpolation_test1dconst;

static class TestDescription_Test_NLinearInterpolation_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NLinearInterpolation_test1d() : CxxTest::RealTestDescription( Tests_Test_NLinearInterpolation, suiteDescription_Test_NLinearInterpolation, 47, "test1d" ) {}
 void runTest() { suite_Test_NLinearInterpolation.test1d(); }
} testDescription_Test_NLinearInterpolation_test1d;

static class TestDescription_Test_NLinearInterpolation_test2dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NLinearInterpolation_test2dconst() : CxxTest::RealTestDescription( Tests_Test_NLinearInterpolation, suiteDescription_Test_NLinearInterpolation, 79, "test2dconst" ) {}
 void runTest() { suite_Test_NLinearInterpolation.test2dconst(); }
} testDescription_Test_NLinearInterpolation_test2dconst;

static class TestDescription_Test_NLinearInterpolation_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NLinearInterpolation_test2d() : CxxTest::RealTestDescription( Tests_Test_NLinearInterpolation, suiteDescription_Test_NLinearInterpolation, 125, "test2d" ) {}
 void runTest() { suite_Test_NLinearInterpolation.test2d(); }
} testDescription_Test_NLinearInterpolation_test2d;

static class TestDescription_Test_NLinearInterpolation_testInternalException : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NLinearInterpolation_testInternalException() : CxxTest::RealTestDescription( Tests_Test_NLinearInterpolation, suiteDescription_Test_NLinearInterpolation, 177, "testInternalException" ) {}
 void runTest() { suite_Test_NLinearInterpolation.testInternalException(); }
} testDescription_Test_NLinearInterpolation_testInternalException;

#include <cxxtest/Root.cpp>
