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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacGravity.h"

static Test_MacGravity suite_Test_MacGravity;

static CxxTest::List Tests_Test_MacGravity = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacGravity( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacGravity.h", 13, "Test_MacGravity", suite_Test_MacGravity, Tests_Test_MacGravity );

static class TestDescription_Test_MacGravity_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test1d() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 16, "test1d" ) {}
 void runTest() { suite_Test_MacGravity.test1d(); }
} testDescription_Test_MacGravity_test1d;

static class TestDescription_Test_MacGravity_test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test2d() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 53, "test2d" ) {}
 void runTest() { suite_Test_MacGravity.test2d(); }
} testDescription_Test_MacGravity_test2d;

static class TestDescription_Test_MacGravity_test1dneigh : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacGravity_test1dneigh() : CxxTest::RealTestDescription( Tests_Test_MacGravity, suiteDescription_Test_MacGravity, 94, "test1dneigh" ) {}
 void runTest() { suite_Test_MacGravity.test1dneigh(); }
} testDescription_Test_MacGravity_test1dneigh;

#include <cxxtest/Root.cpp>
