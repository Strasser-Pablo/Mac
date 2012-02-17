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
#include "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestKeyTableMap.h"

static Test_KeyTableMap suite_Test_KeyTableMap;

static CxxTest::List Tests_Test_KeyTableMap = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_KeyTableMap( "/home/pablo/Bureau/uni/Jet_d_eau/MAC/test/TestKeyTableMap.h", 4, "Test_KeyTableMap", suite_Test_KeyTableMap, Tests_Test_KeyTableMap );

static class TestDescription_Test_KeyTableMap_testCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_KeyTableMap_testCreation() : CxxTest::RealTestDescription( Tests_Test_KeyTableMap, suiteDescription_Test_KeyTableMap, 14, "testCreation" ) {}
 void runTest() { suite_Test_KeyTableMap.testCreation(); }
} testDescription_Test_KeyTableMap_testCreation;

static class TestDescription_Test_KeyTableMap_testIterator : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_KeyTableMap_testIterator() : CxxTest::RealTestDescription( Tests_Test_KeyTableMap, suiteDescription_Test_KeyTableMap, 29, "testIterator" ) {}
 void runTest() { suite_Test_KeyTableMap.testIterator(); }
} testDescription_Test_KeyTableMap_testIterator;

static class TestDescription_Test_KeyTableMap_testConstIterator : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_KeyTableMap_testConstIterator() : CxxTest::RealTestDescription( Tests_Test_KeyTableMap, suiteDescription_Test_KeyTableMap, 60, "testConstIterator" ) {}
 void runTest() { suite_Test_KeyTableMap.testConstIterator(); }
} testDescription_Test_KeyTableMap_testConstIterator;

#include <cxxtest/Root.cpp>
