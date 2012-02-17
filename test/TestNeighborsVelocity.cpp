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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNeighborsVelocity.h"

static Test_MacCell suite_Test_MacCell;

static CxxTest::List Tests_Test_MacCell = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacCell( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNeighborsVelocity.h", 4, "Test_MacCell", suite_Test_MacCell, Tests_Test_MacCell );

static class TestDescription_Test_MacCell_Test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacCell_Test1d() : CxxTest::RealTestDescription( Tests_Test_MacCell, suiteDescription_Test_MacCell, 7, "Test1d" ) {}
 void runTest() { suite_Test_MacCell.Test1d(); }
} testDescription_Test_MacCell_Test1d;

static class TestDescription_Test_MacCell_Test2d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacCell_Test2d() : CxxTest::RealTestDescription( Tests_Test_MacCell, suiteDescription_Test_MacCell, 24, "Test2d" ) {}
 void runTest() { suite_Test_MacCell.Test2d(); }
} testDescription_Test_MacCell_Test2d;

#include <cxxtest/Root.cpp>
