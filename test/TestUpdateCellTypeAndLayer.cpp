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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellTypeAndLayer.h"

static Test_TestUpdateCellTypeAndLayer suite_Test_TestUpdateCellTypeAndLayer;

static CxxTest::List Tests_Test_TestUpdateCellTypeAndLayer = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_TestUpdateCellTypeAndLayer( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellTypeAndLayer.h", 11, "Test_TestUpdateCellTypeAndLayer", suite_Test_TestUpdateCellTypeAndLayer, Tests_Test_TestUpdateCellTypeAndLayer );

static class TestDescription_Test_TestUpdateCellTypeAndLayer_testUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_TestUpdateCellTypeAndLayer_testUpdate() : CxxTest::RealTestDescription( Tests_Test_TestUpdateCellTypeAndLayer, suiteDescription_Test_TestUpdateCellTypeAndLayer, 14, "testUpdate" ) {}
 void runTest() { suite_Test_TestUpdateCellTypeAndLayer.testUpdate(); }
} testDescription_Test_TestUpdateCellTypeAndLayer_testUpdate;

#include <cxxtest/Root.cpp>
