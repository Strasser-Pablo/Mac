/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestPhysvector.h"

static Test_Physvector suite_Test_Physvector;

static CxxTest::List Tests_Test_Physvector = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_Physvector( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestPhysvector.h", 5, "Test_Physvector", suite_Test_Physvector, Tests_Test_Physvector );

static class TestDescription_Test_Physvector_testassignement : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Physvector_testassignement() : CxxTest::RealTestDescription( Tests_Test_Physvector, suiteDescription_Test_Physvector, 16, "testassignement" ) {}
 void runTest() { suite_Test_Physvector.testassignement(); }
} testDescription_Test_Physvector_testassignement;

static class TestDescription_Test_Physvector_testarithmetic : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Physvector_testarithmetic() : CxxTest::RealTestDescription( Tests_Test_Physvector, suiteDescription_Test_Physvector, 27, "testarithmetic" ) {}
 void runTest() { suite_Test_Physvector.testarithmetic(); }
} testDescription_Test_Physvector_testarithmetic;

static class TestDescription_Test_Physvector_testOutofBound : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Physvector_testOutofBound() : CxxTest::RealTestDescription( Tests_Test_Physvector, suiteDescription_Test_Physvector, 54, "testOutofBound" ) {}
 void runTest() { suite_Test_Physvector.testOutofBound(); }
} testDescription_Test_Physvector_testOutofBound;

#include <cxxtest/Root.cpp>
