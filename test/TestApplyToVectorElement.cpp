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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestApplyToVectorElement.h"

static Test_ApplyToVectorElement suite_Test_ApplyToVectorElement;

static CxxTest::List Tests_Test_ApplyToVectorElement = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_ApplyToVectorElement( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestApplyToVectorElement.h", 5, "Test_ApplyToVectorElement", suite_Test_ApplyToVectorElement, Tests_Test_ApplyToVectorElement );

static class TestDescription_Test_ApplyToVectorElement_testapply : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ApplyToVectorElement_testapply() : CxxTest::RealTestDescription( Tests_Test_ApplyToVectorElement, suiteDescription_Test_ApplyToVectorElement, 8, "testapply" ) {}
 void runTest() { suite_Test_ApplyToVectorElement.testapply(); }
} testDescription_Test_ApplyToVectorElement_testapply;

#include <cxxtest/Root.cpp>
