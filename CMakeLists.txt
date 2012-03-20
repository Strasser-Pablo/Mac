cmake_minimum_required(VERSION 2.8)
project(MAC CXX)
option (USE_TESTING 
        "Build the test case?" ON) 
option(USE_DEB_INFO
	"Build with deb info" ON)
option(USE_GENERATE_PROFILE_BASED_OPTIMIZATION
	"Build with generation of profile based optimization",OFF)

option(USE_USE_PROFILE_BASED_OPTIMIZATION
	"Build with usage of previous profile based optimization",OFF)

option (USE_UMFPACK 
        "Link Umfpack to solve linear equation" ON) 

option (USE_DOXYGEN 
        "Build the documentation" ON) 
		
option (USE_INSTALLATION
		"Build installation" ON)

option (USE_GOOGLE_PERF
	"Build with Google Perf" OFF)
option (USE_COMPILER_OPTION_WALL "Build with -Wall option that will generate more warning" ON)

option (USE_COMPILER_OPTION_IGNORE_WARNING_REORDER "Build with -Wnoreorder to ignore reorder warning" on)

option (USE_COMPILER_EXTRA "Build with -WExtra" OFF)

option (USE_COMPILER_OPTIMISATION_FLAG "Optimize Code" on)
include(CheckCXXCompilerFlag)
find_package( Boost 1.46.0 COMPONENTS "serialization")
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )
if (USE_TESTING)
 ENABLE_TESTING()
endif (USE_TESTING)

if(USE_INSTALLATION)
include (InstallRequiredSystemLibraries)
include (CPack)
endif(USE_INSTALLATION)
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

CHECK_CXX_COMPILER_FLAG(-march=native COMPILER_NATIVE)
CHECK_CXX_COMPILER_FLAG(-std=c++0x COMPILER_CPP0x)

if(USE_COMPILER_OPTION_WALL)
	CHECK_CXX_COMPILER_FLAG(-Wall COMPILER_WALL)
endif(USE_COMPILER_OPTION_WALL)
if(USE_COMPILER_OPTION_WALL)
else()
	set(COMPILER_WALL false)
endif()

if(USE_COMPILER_EXTRA)
	CHECK_CXX_COMPILER_FLAG("-Wextra -Wunsafe-loop-optimizations -Wdisabled-optimization -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wno-unused-parameter" COMPILER_EXTRA)
endif()
if(USE_COMPILER_EXTRA)
else()
	set(COMPILER_EXTRA,false)
endif()



if(USE_COMPILER_OPTION_IGNORE_WARNING_REORDER)
	CHECK_CXX_COMPILER_FLAG(-Wno-reorder COMPILER_WNOREORDER)
endif(USE_COMPILER_OPTION_IGNORE_WARNING_REORDER)

if(USE_COMPILER_OPTION_IGNORE_WARNING_REORDER)
else()
	set(COMPILER_WNOREORDER false)
endif()

set(BACKUP_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
SET(CMAKE_REQUIRED_FLAGS "--coverage")
CHECK_CXX_COMPILER_FLAG("--coverage -g" COMPILER_COVERAGE)
set(CMAKE_REQUIRED_FLAGS ${BACKUP_REQUIRED_FLAGS})


if(USE_USE_PROFILE_BASED_OPTIMIZATION)
	CHECK_CXX_COMPILER_FLAG("-fprofile-use	-Wno-coverage-mismatch" COMPILER_USE_PROFILE_BASED_OPTIMIZATION)
endif()

if(USE_GENERATE_PROFILE_BASED_OPTIMIZATION)
	SET(CMAKE_REQUIRED_FLAGS "--coverage")
	CHECK_CXX_COMPILER_FLAG("-fprofile-generate -fipa-profile  --coverage -fbranch-probabilities" COMPILER_GENERATE_PROFILE_BASED_OPTIMIZATION)
	set(CMAKE_REQUIRED_FLAGS ${BACKUP_REQUIRED_FLAGS})
endif()
CHECK_CXX_COMPILER_FLAG(-o0 COMPILER_NO_OPTIMISATION)
if(COMPILER_COVERAGE)
	set(COMPILER_COVERAGE_FLAG "--coverage -g ")
endif(COMPILER_COVERAGE)
if(COMPILER_NO_OPTIMISATION)
	set(COMPILER_NO_OPTIMISATION_FLAG "-o0 ")
endif(COMPILER_NO_OPTIMISATION)
if(USE_COMPILER_OPTIMISATION_FLAG)
	CHECK_CXX_COMPILER_FLAG("-fwhole-program -flto " COMPILER_OPTIMISATION_FLAG)
endif()
if(USE_COMPILER_OPTIMISATION_FLAG)
else()
	set(COMPILER_OPTIMISATION_FLAG false)
endif()
if(USE_DEB_INFO)
	CHECK_CXX_COMPILER_FLAG("-g " COMPILER_DEB_INFO)
endif()
if(USE_DEB_INFO)
else()
	set(COMPILER_OPTIMISATION_FLAG false)
endif()



if(COMPILER_WALL)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -Wall" )
endif(COMPILER_WALL)
if(COMPILER_USE_PROFILE_BASED_OPTIMIZATION)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -fprofile-use -Wno-coverage-mismatch" )
endif()
if(COMPILER_GENERATE_PROFILE_BASED_OPTIMIZATION)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -fprofile-generate -fipa-profile   --coverage -fbranch-probabilities")
	set(COMPUTATION_LINK_FLAGS "${COMPUTATION_LINK_FLAGS} --coverage" )
endif()
if(USE_DEB_INFO)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -g" )
endif()

if(COMPILER_EXTRA)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -Wextra -Wunsafe-loop-optimizations -Wdisabled-optimization -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wno-unused-parameter " )
else()
endif()

if(COMPILER_WNOREORDER )
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -Wno-reorder" )
endif(COMPILER_WNOREORDER)

if(COMPILER_CPP0x)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -std=c++0x" )
	set(CPP0X_FLAG "-std=c++0x")
else()
endif(COMPILER_CPP0x)

if(COMPILER_NATIVE)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -march=native" )
endif(COMPILER_NATIVE)

if(COMPILER_OPTIMISATION_FLAG)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -flto -fwhole-program")
       	set(COMPUTATION_LINK_FLAGS "${COMPUTATION_LINK_FLAGS} -flto"  )
endif()
add_executable(computation ${source_files})
set_target_properties(computation PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(computation vtkHybrid ${Boost_LIBRARIES} )
if(USE_UMFPACK)
	TARGET_LINK_LIBRARIES(computation -lumfpack)
endif(USE_UMFPACK)

if(USE_GOOGLE_PERF)
	TARGET_LINK_LIBRARIES(computation -lprofiler)
endif(USE_GOOGLE_PERF)

install (TARGETS computation DESTINATION bin)

if (USE_TESTING)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/test)


function(AddTestProperty target)
	set(COMPILER_FLAG "${COMPILER_COVERAGE_FLAG} ${COMPILER_NO_OPTIMISATION_FLAG} ${CPP0X_FLAG}")
	set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMPILER_FLAG} LINK_FLAGS ${COMPILER_FLAG})
	Target_link_libraries(${target}  ${Boost_LIBRARIES})
endfunction(AddTestProperty)

CXXTEST_ADD_TEST(test_cov_physvector test/TestPhysvector.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPhysvector.h)
AddTestProperty(test_cov_physvector) 

CXXTEST_ADD_TEST(test_cov_KeyTableMap test/TestKeyTableMap.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestKeyTableMap.h)
AddTestProperty(test_cov_KeyTableMap) 

CXXTEST_ADD_TEST(test_cov_MacCell test/TestMacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacCell.h)
AddTestProperty(test_cov_MacCell) 

CXXTEST_ADD_TEST(test_cov_Particle test/TestParticle.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestParticle.h)
AddTestProperty(test_cov_Particle) 

CXXTEST_ADD_TEST(test_cov_TableContainerList test/TestTableContainerList.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestTableContainerList.h)
AddTestProperty(test_cov_TableContainerList) 

CXXTEST_ADD_TEST(test_cov_MaximalSpeed test/TestMaximalSpeed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMaximalSpeed.h)
AddTestProperty(test_cov_MaximalSpeed) 

CXXTEST_ADD_TEST(test_cov_CalculateTimeStep test/TestCalculateTimeStep.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestCalculateTimeStep.h)
AddTestProperty(test_cov_CalculateTimeStep) 

CXXTEST_ADD_TEST(test_cov_Rounding test/TestRounding.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestRounding.h)
AddTestProperty(test_cov_Rounding) 

CXXTEST_ADD_TEST(test_cov_ApplyToVectorElement test/TestApplyToVectorElement.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestApplyToVectorElement.h)
AddTestProperty(test_cov_ApplyToVectorElement) 

CXXTEST_ADD_TEST(test_cov_ParticleToKey test/TestParticleToKey.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestParticleToKey.h)
AddTestProperty(test_cov_ParticleToKey) 

CXXTEST_ADD_TEST(test_cov_UpdateCellFluid test/TestUpdateCellFluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellFluid.h)
AddTestProperty(test_cov_UpdateCellFluid) 

CXXTEST_ADD_TEST(test_cov_UpdateCellToInitialLayer test/TestUpdateCellToInitialLayer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellToInitialLayer.h)
AddTestProperty(test_cov_UpdateCellToInitialLayer) 

CXXTEST_ADD_TEST(test_cov_NeighborsPhysvector test/TestNeighborsPhysvector.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsPhysvector.h)
AddTestProperty(test_cov_NeighborsPhysvector) 

CXXTEST_ADD_TEST(test_cov_UpdateCellTypeAndLayer test/TestUpdateCellTypeAndLayer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellTypeAndLayer.h)
AddTestProperty(test_cov_UpdateCellTypeAndLayer) 

CXXTEST_ADD_TEST(test_cov_UpdateDeleteCell test/TestUpdateDeleteCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateDeleteCell.h)
AddTestProperty(test_cov_UpdateDeleteCell) 

CXXTEST_ADD_TEST(test_cov_MacInitializeCell test/TestMacInitializeCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacInitializeCell.h)
AddTestProperty(test_cov_MacInitializeCell) 

CXXTEST_ADD_TEST(test_cov_NLinearInterpolation test/TestNLinearInterpolation.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNLinearInterpolation.h)
AddTestProperty(test_cov_NLinearInterpolation) 

CXXTEST_ADD_TEST(test_cov_MacGetVelocity test/TestMacGetVelocity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacGetVelocity.h)
AddTestProperty(test_cov_MacGetVelocity) 

CXXTEST_ADD_TEST(test_cov_MacConvect test/TestMacConvect.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacConvect.h)
AddTestProperty(test_cov_MacConvect) 

CXXTEST_ADD_TEST(test_cov_MacGravity test/TestMacGravity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacGravity.h)
AddTestProperty(test_cov_MacGravity) 

CXXTEST_ADD_TEST(test_cov_ComputeSpeedLaplacien test/TestComputeSpeedLaplacien.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestComputeSpeedLaplacien.h)
AddTestProperty(test_cov_ComputeSpeedLaplacien) 

CXXTEST_ADD_TEST(test_cov_MacApplyViscosity test/TestMacApplyViscosity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacApplyViscosity.h)
AddTestProperty(test_cov_MacApplyViscosity) 

CXXTEST_ADD_TEST(test_cov_SolvePressureCG test/TestSolvePressureCG.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSolvePressureCG.h)
AddTestProperty(test_cov_SolvePressureCG) 

CXXTEST_ADD_TEST(test_cov_NeighborsVelocity test/TestNeighborsVelocity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsVelocity.h)
AddTestProperty(test_cov_NeighborsVelocity) 

CXXTEST_ADD_TEST(test_cov_SetLayerFluidCell test/TestSetLayerFluidCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSetLayerFluidCell.h)
AddTestProperty(test_cov_SetLayerFluidCell) 

CXXTEST_ADD_TEST(test_cov_ExtrapolateCellFluid test/TestExtrapolateCellFluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestExtrapolateCellFluid.h)
AddTestProperty(test_cov_ExtrapolateCellFluid) 

CXXTEST_ADD_TEST(test_cov_OutputVectorSpeed test/TestOutputVectorSpeed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestOutputVectorSpeed.h)
AddTestProperty(test_cov_OutputVectorSpeed)

CXXTEST_ADD_TEST(test_cov_SolvePressureUmfpack test/TestSolvePressureUmfpack.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSolvePressureUmfpack.h)
AddTestProperty(test_cov_SolvePressureUmfpack)

if(USE_UMFPACK)
TARGET_LINK_LIBRARIES(test_cov_SolvePressureUmfpack -lumfpack)
endif(USE_UMFPACK)

CXXTEST_ADD_TEST(test_cov_NeighborsDiagPhysvector test/TestNeighborsDiagPhysvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNeighborsDiagPhysvector.h)
AddTestProperty(test_cov_NeighborsDiagPhysvector)
CXXTEST_ADD_TEST(test_cov_Math_Set test/TestMath_Set.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMath_Set.h)
AddTestProperty(test_cov_Math_Set) 
CXXTEST_ADD_TEST(test_cov_NDFor test/TestNDFor.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNDFor.h)
AddTestProperty(test_cov_NDFor)

CXXTEST_ADD_TEST(test_cov_UpdateCellTypeAndLayer3 test/TestUpdateCellTypeAndLayer3.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellTypeAndLayer3.h)
AddTestProperty(test_cov_UpdateCellTypeAndLayer3)

CXXTEST_ADD_TEST(test_cov_Math_Set2 test/TestMath_Set2.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMath_Set2.h)
AddTestProperty(test_cov_Math_Set2)

CXXTEST_ADD_TEST(test_cov_Mac_1_Order_UpWindConvect test/TestMac_1_OrderUpWindConvect.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMac_1_OrderUpWindConvect.h)
AddTestProperty(test_cov_Mac_1_Order_UpWindConvect)

CXXTEST_ADD_TEST(test_cov_Serialization test/TestSerialization.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSerialization.h)
AddTestProperty(test_cov_Serialization)
	TARGET_LINK_LIBRARIES(test_cov_Serialization vtkHybrid )
	TARGET_LINK_LIBRARIES(test_cov_Serialization umfpack)

	
CXXTEST_ADD_TEST(test_cov_KeyTableUnorderedMap test/TestKeyTableUnorderedMap.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestKeyTableUnorderedMap.h)
AddTestProperty(test_cov_KeyTableUnorderedMap)
endif(USE_TESTING)
