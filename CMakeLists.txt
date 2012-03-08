cmake_minimum_required(VERSION 2.8)

option (USE_TESTING 
        "Build the test case?" ON) 
	
option (USE_UMFPACK 
        "Link Umfpack to solve linear equation" ON) 

option (USE_DOXYGEN 
        "Build the documentation" ON) 
		
option (USE_INSTALLATION
		"Build installation" ON)

option (USE_GOOGLE_PERF
		"Build with Google Perf" ON)

if (USE_TESTING)
 ENABLE_TESTING()
endif (USE_TESTING)

if(USE_INSTALLATION)
include (InstallRequiredSystemLibraries)
include (CPack)
endif(USE_INSTALLATION)

ADD_DEFINITIONS(-march=native -std=c++0x)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

if(USE_DOXYGEN)
find_package (Doxygen)
endif(USE_DOXYGEN)

file(
	GLOB_RECURSE
	source_files
	 ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

if(USE_GOOGLE_PERF)
Set(USE_GOOGLE_PERF_DEFINE 1)
 else(USE_GOOGLE_PERF)
 Set(USE_GOOGLE_PERF_DEFINE 0)
endif(USE_GOOGLE_PERF)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )
  
  include_directories("${PROJECT_BINARY_DIR}")

if (USE_TESTING)
set(VALGRIND_COMMAND "valgrind ")
set(BUILD_DASHBOARD_REPORTS 1)
INCLUDE(CTest)
find_package(CxxTest)
endif(USE_TESTING)

if(USE_DOXYGEN)
add_custom_target(doc COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc/")
endif(USE_DOXYGEN)

add_executable(computation ${source_files})
TARGET_LINK_LIBRARIES(computation vtkHybrid)
if(USE_UMFPACK)
	TARGET_LINK_LIBRARIES(computation -lumfpack)
endif(USE_UMFPACK)

if(USE_GOOGLE_PERF)
	TARGET_LINK_LIBRARIES(computation -lprofiler)
endif(USE_GOOGLE_PERF)

install (TARGETS computation DESTINATION bin)

if (USE_TESTING)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/test)
CXXTEST_ADD_TEST(test_cov_physvector test/TestPhysvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPhysvector.h)
set_target_properties(test_cov_physvector PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs  --coverage -o0" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs  --coverage -o0")

CXXTEST_ADD_TEST(test_cov_KeyTableMap test/TestKeyTableMap.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestKeyTableMap.h)
set_target_properties(test_cov_KeyTableMap PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_MacCell test/TestMacCell.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacCell.h)
set_target_properties(test_cov_MacCell PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_Particle test/TestParticle.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestParticle.h)
set_target_properties(test_cov_Particle PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_TableContainerList test/TestTableContainerList.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestTableContainerList.h)
set_target_properties(test_cov_TableContainerList PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_MaximalSpeed test/TestMaximalSpeed.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMaximalSpeed.h)
set_target_properties(test_cov_MaximalSpeed PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_CalculateTimeStep test/TestCalculateTimeStep.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestCalculateTimeStep.h)
set_target_properties(test_cov_CalculateTimeStep PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_Rounding test/TestRounding.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestRounding.h)
set_target_properties(test_cov_Rounding PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_ApplyToVectorElement test/TestApplyToVectorElement.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestApplyToVectorElement.h)
set_target_properties(test_cov_ApplyToVectorElement PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_ParticleToKey test/TestParticleToKey.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestParticleToKey.h)
set_target_properties(test_cov_ParticleToKey PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_UpdateCellFluid test/TestUpdateCellFluid.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellFluid.h)
set_target_properties(test_cov_UpdateCellFluid PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_UpdateCellToInitialLayer test/TestUpdateCellToInitialLayer.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellToInitialLayer.h)
set_target_properties(test_cov_UpdateCellToInitialLayer PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_NeighborsPhysvector test/TestNeighborsPhysvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsPhysvector.h)
set_target_properties(test_cov_NeighborsPhysvector PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_UpdateCellTypeAndLayer test/TestUpdateCellTypeAndLayer.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellTypeAndLayer.h)
set_target_properties(test_cov_UpdateCellTypeAndLayer PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_UpdateDeleteCell test/TestUpdateDeleteCell.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateDeleteCell.h)
set_target_properties(test_cov_UpdateDeleteCell PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_MacInitializeCell test/TestMacInitializeCell.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacInitializeCell.h)
set_target_properties(test_cov_MacInitializeCell PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")




CXXTEST_ADD_TEST(test_cov_NLinearInterpolation test/TestNLinearInterpolation.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNLinearInterpolation.h)
set_target_properties(test_cov_NLinearInterpolation PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_MacGetVelocity test/TestMacGetVelocity.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacGetVelocity.h)
set_target_properties(test_cov_MacGetVelocity PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_MacConvect test/TestMacConvect.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacConvect.h)
set_target_properties(test_cov_MacConvect PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_MacGravity test/TestMacGravity.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacGravity.h)
set_target_properties(test_cov_MacGravity PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_ComputeSpeedLaplacien test/TestComputeSpeedLaplacien.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestComputeSpeedLaplacien.h)
set_target_properties(test_cov_ComputeSpeedLaplacien PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_MacApplyViscosity test/TestMacApplyViscosity.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacApplyViscosity.h)
set_target_properties(test_cov_MacApplyViscosity PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_SolvePressureCG test/TestSolvePressureCG.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSolvePressureCG.h)
set_target_properties(test_cov_SolvePressureCG PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_NeighborsVelocity test/TestNeighborsVelocity.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsVelocity.h)
set_target_properties(test_cov_NeighborsVelocity PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")



CXXTEST_ADD_TEST(test_cov_SetLayerFluidCell test/TestSetLayerFluidCell.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSetLayerFluidCell.h)
set_target_properties(test_cov_SetLayerFluidCell PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_ExtrapolateCellFluid test/TestExtrapolateCellFluid.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestExtrapolateCellFluid.h)
set_target_properties(test_cov_ExtrapolateCellFluid PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


CXXTEST_ADD_TEST(test_cov_OutputVectorSpeed test/TestOutputVectorSpeed.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestOutputVectorSpeed.h)
set_target_properties(test_cov_OutputVectorSpeed PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_SolvePressureUmfpack test/TestSolvePressureUmfpack.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSolvePressureUmfpack.h)
set_target_properties(test_cov_OutputVectorSpeed PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
if(USE_UMFPACK)
TARGET_LINK_LIBRARIES(test_cov_SolvePressureUmfpack -lumfpack)
endif(USE_UMFPACK)

CXXTEST_ADD_TEST(test_cov_NeighborsDiagPhysvector test/TestNeighborsDiagPhysvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsDiagPhysvector.h)
set_target_properties(test_cov_NeighborsDiagPhysvector PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_Math_Set test/TestMath_Set.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMath_Set.h)
set_target_properties(test_cov_Math_Set PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_NDFor test/TestNDFor.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNDFor.h)
set_target_properties(test_cov_NDFor PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_UpdateCellTypeAndLayer3 test/TestUpdateCellTypeAndLayer3.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellTypeAndLayer3.h)
set_target_properties(test_cov_UpdateCellTypeAndLayer3 PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_Math_Set2 test/TestMath_Set2.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMath_Set2.h)
set_target_properties(test_cov_Math_Set2 PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

endif(USE_TESTING)
