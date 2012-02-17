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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellToInitialLayer.h"

static Test_UpdateCellToInitialLayer suite_Test_UpdateCellToInitialLayer;

static CxxTest::List Tests_Test_UpdateCellToInitialLayer = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_UpdateCellToInitialLayer( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestUpdateCellToInitialLayer.h", 10, "Test_UpdateCellToInitialLayer", suite_Test_UpdateCellToInitialLayer, Tests_Test_UpdateCellToInitialLayer );

static class TestDescription_Test_UpdateCellToInitialLayer_testupdate : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_UpdateCellToInitialLayer_testupdate() : CxxTest::RealTestDescription( Tests_Test_UpdateCellToInitialLayer, suiteDescription_Test_UpdateCellToInitialLayer, 13, "testupdate" ) {}
 void runTest() { suite_Test_UpdateCellToInitialLayer.testupdate(); }
} testDescription_Test_UpdateCellToInitialLayer_testupdate;

#include <cxxtest/Root.cpp>
