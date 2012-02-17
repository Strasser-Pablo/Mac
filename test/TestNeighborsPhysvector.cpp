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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNeighborsPhysvector.h"

static Test_NeighborsPhysvector suite_Test_NeighborsPhysvector;

static CxxTest::List Tests_Test_NeighborsPhysvector = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_NeighborsPhysvector( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestNeighborsPhysvector.h", 5, "Test_NeighborsPhysvector", suite_Test_NeighborsPhysvector, Tests_Test_NeighborsPhysvector );

static class TestDescription_Test_NeighborsPhysvector_testneigh : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_NeighborsPhysvector_testneigh() : CxxTest::RealTestDescription( Tests_Test_NeighborsPhysvector, suiteDescription_Test_NeighborsPhysvector, 8, "testneigh" ) {}
 void runTest() { suite_Test_NeighborsPhysvector.testneigh(); }
} testDescription_Test_NeighborsPhysvector_testneigh;

#include <cxxtest/Root.cpp>
