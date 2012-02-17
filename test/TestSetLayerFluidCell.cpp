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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestSetLayerFluidCell.h"

static Test_MacConvect suite_Test_MacConvect;

static CxxTest::List Tests_Test_MacConvect = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_MacConvect( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestSetLayerFluidCell.h", 13, "Test_MacConvect", suite_Test_MacConvect, Tests_Test_MacConvect );

static class TestDescription_Test_MacConvect_test1d : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_MacConvect_test1d() : CxxTest::RealTestDescription( Tests_Test_MacConvect, suiteDescription_Test_MacConvect, 16, "test1d" ) {}
 void runTest() { suite_Test_MacConvect.test1d(); }
} testDescription_Test_MacConvect_test1d;

#include <cxxtest/Root.cpp>
