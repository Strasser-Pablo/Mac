cmake_minimum_required(VERSION 2.8)
project(MAC CXX)
option (USE_TESTING
        "Build the test case?" ON)
option(USE_DEB_INFO
	"Build with deb info" OFF)
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

  find_package(MyCxxTest PATHS ${CMAKE_CURRENT_SOURCE_DIR})
if(NOT CXXTEST_FOUND)
	if(USE_TESTING)
		set(USE_TESTING  FALSE)
		MESSAGE(WARNING "CXXTEST not found, will not build testsuit")
	endif(USE_TESTING)
endif(NOT CXXTEST_FOUND)
if (USE_TESTING)
set(VALGRIND_COMMAND "valgrind ")
set(BUILD_DASHBOARD_REPORTS 1)
INCLUDE(CTest)
include_directories("${CXXTEST_INCLUDE_DIRS}")
endif(USE_TESTING)

if(USE_DOXYGEN)
add_custom_target(doc COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc/")
endif(USE_DOXYGEN)

CHECK_CXX_COMPILER_FLAG(-march=native COMPILER_NATIVE)
CHECK_CXX_COMPILER_FLAG(-std=c++11 COMPILER_CPP11)

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

set(COMPUTATION_LINK_FLAGS " ")
set(COMPUTATION_COMPILE_FLAGS " ")

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

if(COMPILER_CPP11)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -std=c++11" )
	set(CPP11_FLAG "-std=c++11")
else()
endif(COMPILER_CPP11)

if(COMPILER_NATIVE)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -march=native" )
endif(COMPILER_NATIVE)

if(COMPILER_OPTIMISATION_FLAG)
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -flto -fwhole-program")
       	set(COMPUTATION_LINK_FLAGS "${COMPUTATION_LINK_FLAGS} -flto"  )
endif()
add_executable(computation ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set_target_properties(computation PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
add_library(lib_computation STATIC)
set_target_properties(lib_computation PROPERTIES LINKER_LANGUAGE "CXX")
TARGET_LINK_LIBRARIES(lib_computation vtkHybrid ${Boost_LIBRARIES} )
if(USE_UMFPACK)
	TARGET_LINK_LIBRARIES(lib_computation -lumfpack -lamd -lcholmod -lcolamd -lblas -llapack)
endif(USE_UMFPACK)

if(USE_GOOGLE_PERF)
	TARGET_LINK_LIBRARIES(lib_computation -lprofiler)
endif(USE_GOOGLE_PERF)
TARGET_LINK_LIBRARIES(computation lib_computation)
install (TARGETS computation DESTINATION bin)


add_executable(Diffusion_Jet ${CMAKE_CURRENT_SOURCE_DIR}/src/mainDiffusion.cpp)
set_target_properties(Diffusion_Jet PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Diffusion_Jet lib_computation)


add_executable(Container_Filling ${CMAKE_CURRENT_SOURCE_DIR}/src/Container_Filling.cpp)
set_target_properties(Container_Filling PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Container_Filling lib_computation)

if (USE_TESTING)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/test)


function(AddTestProperty target)
	set(COMPILER_FLAG "${COMPILER_NO_OPTIMISATION_FLAG} ${COMPILER_COVERAGE_FLAG}  ${CPP11_FLAG} -Wall -Wextra -Wstrict-aliasing=1 -fno-strict-aliasing")
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

CXXTEST_ADD_TEST(test_cov_ExtrapolateCellFluid2 test/TestExtrapolateCellFluid2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestExtrapolateCellFluid2.h)
AddTestProperty(test_cov_ExtrapolateCellFluid2) 

CXXTEST_ADD_TEST(test_cov_OutputVectorSpeed test/TestOutputVectorSpeed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestOutputVectorSpeed.h)
AddTestProperty(test_cov_OutputVectorSpeed)

CXXTEST_ADD_TEST(test_cov_SolvePressureUmfpack test/TestSolvePressureUmfpack.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSolvePressureUmfpack.h)
AddTestProperty(test_cov_SolvePressureUmfpack)

TARGET_LINK_LIBRARIES(test_cov_SolvePressureUmfpack lib_computation)

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

# CXXTEST_ADD_TEST(test_cov_Serialization test/TestSerialization.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSerialization.h)
# AddTestProperty(test_cov_Serialization)
#	TARGET_LINK_LIBRARIES(test_cov_Serialization lib_computation)

	
CXXTEST_ADD_TEST(test_cov_KeyTableUnorderedMap test/TestKeyTableUnorderedMap.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestKeyTableUnorderedMap.h)
AddTestProperty(test_cov_KeyTableUnorderedMap)

# 	No test in it.
#	CXXTEST_ADD_TEST(test_cov_Symmetry test/TestSymmetry.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSymmetry.h)
#	AddTestProperty(test_cov_Symmetry)
#	TARGET_LINK_LIBRARIES(test_cov_Symmetry lib_computation)


# 	Broken because of change in output that use boundary instead of particle.
#	CXXTEST_ADD_TEST(test_cov_Stationar test/TestStationar.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestStationar.h)
#	AddTestProperty(test_cov_Stationar)
#	TARGET_LINK_LIBRARIES(test_cov_Stationar lib_computation)

	CXXTEST_ADD_TEST(test_cov_MacWorld2 test/TestMacWorld2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacWorld2.h)
	AddTestProperty(test_cov_MacWorld2)

# 	Remove because broken and will not be needed when we use level set.
#	CXXTEST_ADD_TEST(test_cov_UpdateCellFluid3 test/TestUpdateCellFluid3.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdateCellFluid3.h)
#	AddTestProperty(test_cov_UpdateCellFluid3)

	CXXTEST_ADD_TEST(test_cov_MacCirculation test/TestMacCirculation.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMacCirculation.h)
	AddTestProperty(test_cov_MacCirculation)

	CXXTEST_ADD_TEST(test_cov_Inversible_Value test/TestInversible_Value.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestInversible_Value.h)
	AddTestProperty(test_cov_Inversible_Value)

	CXXTEST_ADD_TEST(test_cov_GetCellType test/TestGetCellType.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestGetCellType.h)
	AddTestProperty(test_cov_GetCellType)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air test/TestData_CellType_Fluid_Air.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air)

	CXXTEST_ADD_TEST(test_cov_Data_Grid test/TestData_Grid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid.h)
	AddTestProperty(test_cov_Data_Grid)

	CXXTEST_ADD_TEST(test_cov_Data_Pressure_Data test/TestData_Pressure_Data.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Pressure_Data.h)
	AddTestProperty(test_cov_Data_Pressure_Data)


	CXXTEST_ADD_TEST(test_cov_Data_Speed_Data test/TestData_Speed_Data.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Speed_Data.h)
	AddTestProperty(test_cov_Data_Speed_Data)

	CXXTEST_ADD_TEST(test_cov_Data_Grid_MacCell test/TestData_Grid_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_MacCell.h)
	AddTestProperty(test_cov_Data_Grid_MacCell)

	CXXTEST_ADD_TEST(test_cov_Data_Grid_Speed test/TestData_Grid_Speed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_Speed.h)
	AddTestProperty(test_cov_Data_Grid_Speed)

	CXXTEST_ADD_TEST(test_cov_Data_Grid_Pressure test/TestData_Grid_Pressure.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_Pressure.h)
	AddTestProperty(test_cov_Data_Grid_Pressure)

	CXXTEST_ADD_TEST(test_cov_Data_Neighbour_List test/TestData_Neighbour_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Neighbour_List.h)
	AddTestProperty(test_cov_Data_Neighbour_List)

	CXXTEST_ADD_TEST(test_cov_Data_Hookable_Hash_Table test/TestHookable_Hash_Table.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestHookable_Hash_Table.h)
	AddTestProperty(test_cov_Data_Hookable_Hash_Table)

	CXXTEST_ADD_TEST(test_cov_Data_Hook_Neighbour_List test/TestData_Hook_Neighbour_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Hook_Neighbour_List.h)
	AddTestProperty(test_cov_Data_Hook_Neighbour_List)

	CXXTEST_ADD_TEST(test_cov_Data_Interface_Fluid_Air test/TestData_Interface_Fluid_Air.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Interface_Fluid_Air.h)
	AddTestProperty(test_cov_Data_Interface_Fluid_Air)
endif(USE_TESTING)
