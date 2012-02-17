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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestOutputVectorSpeed.h"

static Test_OutputVectorSpeed suite_Test_OutputVectorSpeed;

static CxxTest::List Tests_Test_OutputVectorSpeed = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_OutputVectorSpeed( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestOutputVectorSpeed.h", 15, "Test_OutputVectorSpeed", suite_Test_OutputVectorSpeed, Tests_Test_OutputVectorSpeed );

static class TestDescription_Test_OutputVectorSpeed_testOutput1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_OutputVectorSpeed_testOutput1d() : CxxTest::RealTestDescription( Tests_Test_OutputVectorSpeed, suiteDescription_Test_OutputVectorSpeed, 18, "testOutput1d" ) {}
 void runTest() { suite_Test_OutputVectorSpeed.testOutput1d(); }
} testDescription_Test_OutputVectorSpeed_testOutput1d;

static class TestDescription_Test_OutputVectorSpeed_testOutput1dPart : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_OutputVectorSpeed_testOutput1dPart() : CxxTest::RealTestDescription( Tests_Test_OutputVectorSpeed, suiteDescription_Test_OutputVectorSpeed, 60, "testOutput1dPart" ) {}
 void runTest() { suite_Test_OutputVectorSpeed.testOutput1dPart(); }
} testDescription_Test_OutputVectorSpeed_testOutput1dPart;

static class TestDescription_Test_OutputVectorSpeed_testOutput2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_OutputVectorSpeed_testOutput2d() : CxxTest::RealTestDescription( Tests_Test_OutputVectorSpeed, suiteDescription_Test_OutputVectorSpeed, 104, "testOutput2d" ) {}
 void runTest() { suite_Test_OutputVectorSpeed.testOutput2d(); }
} testDescription_Test_OutputVectorSpeed_testOutput2d;

static class TestDescription_Test_OutputVectorSpeed_testOutput2dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_OutputVectorSpeed_testOutput2dvar() : CxxTest::RealTestDescription( Tests_Test_OutputVectorSpeed, suiteDescription_Test_OutputVectorSpeed, 161, "testOutput2dvar" ) {}
 void runTest() { suite_Test_OutputVectorSpeed.testOutput2dvar(); }
} testDescription_Test_OutputVectorSpeed_testOutput2dvar;

static class TestDescription_Test_OutputVectorSpeed_testOutput3dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_OutputVectorSpeed_testOutput3dvar() : CxxTest::RealTestDescription( Tests_Test_OutputVectorSpeed, suiteDescription_Test_OutputVectorSpeed, 227, "testOutput3dvar" ) {}
 void runTest() { suite_Test_OutputVectorSpeed.testOutput3dvar(); }
} testDescription_Test_OutputVectorSpeed_testOutput3dvar;

#include <cxxtest/Root.cpp>
