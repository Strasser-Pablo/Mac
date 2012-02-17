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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacCell.h"

static Test_MacCell suite_Test_MacCell;

static CxxTest::List Tests_Test_MacCell = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacCell( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestMacCell.h", 4, "Test_MacCell", suite_Test_MacCell, Tests_Test_MacCell );

static class TestDescription_Test_MacCell_testcreation : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacCell_testcreation() : CxxTest::RealTestDescription( Tests_Test_MacCell, suiteDescription_Test_MacCell, 8, "testcreation" ) {}
 void runTest() { suite_Test_MacCell.testcreation(); }
} testDescription_Test_MacCell_testcreation;

#include <cxxtest/Root.cpp>
