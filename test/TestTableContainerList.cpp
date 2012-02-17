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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestTableContainerList.h"

static Test_ContainerList suite_Test_ContainerList;

static CxxTest::List Tests_Test_ContainerList = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_ContainerList( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestTableContainerList.h", 4, "Test_ContainerList", suite_Test_ContainerList, Tests_Test_ContainerList );

static class TestDescription_Test_ContainerList_testCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ContainerList_testCreation() : CxxTest::RealTestDescription( Tests_Test_ContainerList, suiteDescription_Test_ContainerList, 8, "testCreation" ) {}
 void runTest() { suite_Test_ContainerList.testCreation(); }
} testDescription_Test_ContainerList_testCreation;

static class TestDescription_Test_ContainerList_testIterator : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ContainerList_testIterator() : CxxTest::RealTestDescription( Tests_Test_ContainerList, suiteDescription_Test_ContainerList, 33, "testIterator" ) {}
 void runTest() { suite_Test_ContainerList.testIterator(); }
} testDescription_Test_ContainerList_testIterator;

static class TestDescription_Test_ContainerList_TestIteratorArithmetique : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_ContainerList_TestIteratorArithmetique() : CxxTest::RealTestDescription( Tests_Test_ContainerList, suiteDescription_Test_ContainerList, 56, "TestIteratorArithmetique" ) {}
 void runTest() { suite_Test_ContainerList.TestIteratorArithmetique(); }
} testDescription_Test_ContainerList_TestIteratorArithmetique;

#include <cxxtest/Root.cpp>
