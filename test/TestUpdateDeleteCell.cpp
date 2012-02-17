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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateDeleteCell.h"

static Test_TestUpdateDeleteCell suite_Test_TestUpdateDeleteCell;

static CxxTest::List Tests_Test_TestUpdateDeleteCell = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_TestUpdateDeleteCell( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateDeleteCell.h", 11, "Test_TestUpdateDeleteCell", suite_Test_TestUpdateDeleteCell, Tests_Test_TestUpdateDeleteCell );

static class TestDescription_Test_TestUpdateDeleteCell_testUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_TestUpdateDeleteCell_testUpdate() : CxxTest::RealTestDescription( Tests_Test_TestUpdateDeleteCell, suiteDescription_Test_TestUpdateDeleteCell, 14, "testUpdate" ) {}
 void runTest() { suite_Test_TestUpdateDeleteCell.testUpdate(); }
} testDescription_Test_TestUpdateDeleteCell_testUpdate;

#include <cxxtest/Root.cpp>
