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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestSolvePressureCG.h"

static Test_MacGravity suite_Test_MacGravity;

static CxxTest::List Tests_Test_MacGravity = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacGravity( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestSolvePressureCG.h", 11, "Test_MacGravity", suite_Test_MacGravity, Tests_Test_MacGravity );

static class TestDescription_Test_MacGravity_test1dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test1dconst() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 14, "test1dconst" ) {}
 void runTest() { suite_Test_MacGravity.test1dconst(); }
} testDescription_Test_MacGravity_test1dconst;

static class TestDescription_Test_MacGravity_test1dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test1dvar() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 65, "test1dvar" ) {}
 void runTest() { suite_Test_MacGravity.test1dvar(); }
} testDescription_Test_MacGravity_test1dvar;

static class TestDescription_Test_MacGravity_test1dvarspeed : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test1dvarspeed() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 114, "test1dvarspeed" ) {}
 void runTest() { suite_Test_MacGravity.test1dvarspeed(); }
} testDescription_Test_MacGravity_test1dvarspeed;

static class TestDescription_Test_MacGravity_test2dconst : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test2dconst() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 163, "test2dconst" ) {}
 void runTest() { suite_Test_MacGravity.test2dconst(); }
} testDescription_Test_MacGravity_test2dconst;

static class TestDescription_Test_MacGravity_test2dvar : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test2dvar() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 214, "test2dvar" ) {}
 void runTest() { suite_Test_MacGravity.test2dvar(); }
} testDescription_Test_MacGravity_test2dvar;

static class TestDescription_Test_MacGravity_test2dvarspeed : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test2dvarspeed() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 265, "test2dvarspeed" ) {}
 void runTest() { suite_Test_MacGravity.test2dvarspeed(); }
} testDescription_Test_MacGravity_test2dvarspeed;

#include <cxxtest/Root.cpp>
