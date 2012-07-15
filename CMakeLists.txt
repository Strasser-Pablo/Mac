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
#add_executable(computation ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
#set_target_properties(computation PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
add_library(lib_computation STATIC)
set_target_properties(lib_computation PROPERTIES LINKER_LANGUAGE "CXX")
TARGET_LINK_LIBRARIES(lib_computation vtkHybrid ${Boost_LIBRARIES} )
if(USE_UMFPACK)
	TARGET_LINK_LIBRARIES(lib_computation -lumfpack -lamd -lcholmod -lcolamd -lblas -llapack)
endif(USE_UMFPACK)

if(USE_GOOGLE_PERF)
	TARGET_LINK_LIBRARIES(lib_computation -lprofiler)
endif(USE_GOOGLE_PERF)
#TARGET_LINK_LIBRARIES(computation lib_computation)
#install (TARGETS computation DESTINATION bin)


#add_executable(Diffusion_Jet ${CMAKE_CURRENT_SOURCE_DIR}/src/mainDiffusion.cpp)
#set_target_properties(Diffusion_Jet PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Diffusion_Jet lib_computation)


#add_executable(Container_Filling ${CMAKE_CURRENT_SOURCE_DIR}/src/Container_Filling.cpp)
#set_target_properties(Container_Filling PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Container_Filling lib_computation)

if (USE_TESTING)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/test)


function(AddTestProperty target)
	set(COMPILER_FLAG "${COMPILER_NO_OPTIMISATION_FLAG} ${COMPILER_COVERAGE_FLAG}  ${CPP11_FLAG} -Wall -Wextra -Wstrict-aliasing=1 -fno-strict-aliasing")
	set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMPILER_FLAG} LINK_FLAGS ${COMPILER_FLAG})
	Target_link_libraries(${target}  ${Boost_LIBRARIES})
endfunction(AddTestProperty)
	CXXTEST_ADD_TEST(test_cov_physvector test/TestPhysvector.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPhysvector.h)
	AddTestProperty(test_cov_physvector)

	CXXTEST_ADD_TEST(test_cov_KeyTableUnorderedMap test/TestKeyTableUnorderedMap.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestKeyTableUnorderedMap.h)
	AddTestProperty(test_cov_KeyTableUnorderedMap)

	CXXTEST_ADD_TEST(test_cov_Inversible_Value test/TestInversible_Value.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestInversible_Value.h)
	AddTestProperty(test_cov_Inversible_Value)

	#CXXTEST_ADD_TEST(test_cov_GetCellType test/TestGetCellType.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestGetCellType.h)
	#AddTestProperty(test_cov_GetCellType)

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

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Domain_Fluid test/Test_Data_CellType_Domain_Fluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Data_CellType_Domain_Fluid.h)
	AddTestProperty(test_cov_Data_CellType_Domain_Fluid)

	CXXTEST_ADD_TEST(test_cov_Data_Interface_Domain_Rho_Fluid test/TestData_Interface_Domain_Rho_Fluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Interface_Domain_Rho_Fluid.h)
	AddTestProperty(test_cov_Data_Interface_Domain_Rho_Fluid)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Interface_Constant test/Test_Data_CellType_Interface_Constant.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Data_CellType_Interface_Constant.h)
	AddTestProperty(test_cov_Data_CellType_Interface_Constant)

	CXXTEST_ADD_TEST(test_cov_Data_Particles_List test/TestData_Particles_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Particles_List.h)
	AddTestProperty(test_cov_Data_Particles_List)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Initialize_MacCell test/TestAlgorithm_Initialize_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Initialize_MacCell.h)
	AddTestProperty(test_cov_Algorithm_Initialize_MacCell)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Delete_MacCell test/TestAlgorithm_Delete_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Delete_MacCell.h)
	AddTestProperty(test_cov_Algorithm_Delete_MacCell)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Layer_Initial_With_Particle test/TestAlgorithm_Layer_Initial_With_Particle.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Layer_Initial_With_Particle.h)
	AddTestProperty(test_cov_Algorithm_Layer_Initial_With_Particle)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Create_Fluid_Particle test/TestAlgorithms_Create_Fluid_Particle.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Create_Fluid_Particle.h)
	AddTestProperty(test_cov_Algorithms_Create_Fluid_Particle)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Update_CellType_Layer test/TestAlgorithms_Update_CellType_Layer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Update_CellType_Layer.h)
	AddTestProperty(test_cov_Algorithms_Update_CellType_Layer)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Speed_Constant_Mirror test/TestAlgorithm_Speed_Constant_Mirror.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Speed_Constant_Mirror.h)
	AddTestProperty(test_cov_Algorithm_Speed_Constant_Mirror)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Calculate_Time_Step test/TestAlgorithm_Calculate_Time_Step.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Calculate_Time_Step.h)
	AddTestProperty(test_cov_Algorithm_Calculate_Time_Step)

	CXXTEST_ADD_TEST(test_cov_Policy_Speed_Interpolation_Linear test/TestPolicy_Speed_Interpolation_Linear.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Speed_Interpolation_Linear.h)
	AddTestProperty(test_cov_Policy_Speed_Interpolation_Linear)

	CXXTEST_ADD_TEST(test_cov_Policy_Upwind_1_Order test/TestPolicy_Upwind_1_Order.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Upwind_1_Order.h)
	AddTestProperty(test_cov_Policy_Upwind_1_Order)

	CXXTEST_ADD_TEST(test_cov_Policy_Laplacian_Speed test/TestPolicy_Laplacian_Speed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Laplacian_Speed.h)
	AddTestProperty(test_cov_Policy_Laplacian_Speed)

	CXXTEST_ADD_TEST(test_cov_Policy_Divergence test/TestPolicy_Divergence.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Divergence.h)
	AddTestProperty(test_cov_Policy_Divergence)

	CXXTEST_ADD_TEST(test_cov_Policy_Gradiant test/TestPolicy_Gradiant.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Gradiant.h)
	AddTestProperty(test_cov_Policy_Gradiant)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Gravity test/TestAlgorithms_Gravity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Gravity.h)
	AddTestProperty(test_cov_Algorithms_Gravity)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Viscosity test/TestAlgorithms_Viscosity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Viscosity.h)
	AddTestProperty(test_cov_Algorithms_Viscosity)

	CXXTEST_ADD_TEST(test_cov_Policy_Solve_Linear_Umfpack test/TestPolicy_Solve_Linear_Umfpack.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Solve_Linear_Umfpack.h)
	AddTestProperty(test_cov_Policy_Solve_Linear_Umfpack)
	TARGET_LINK_LIBRARIES(test_cov_Policy_Solve_Linear_Umfpack lib_computation)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Solve_Pressure test/TestAlgorithms_Solve_Pressure.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Solve_Pressure.h)
	AddTestProperty(test_cov_Algorithms_Solve_Pressure)
	TARGET_LINK_LIBRARIES(test_cov_Algorithms_Solve_Pressure lib_computation)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Move_Particles test/TestAlgorithms_Move_Particles.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Move_Particles.h)
	AddTestProperty(test_cov_Algorithms_Move_Particles)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Output test/TestAlgorithms_Output.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Output.h)
	AddTestProperty(test_cov_Algorithms_Output)
	TARGET_LINK_LIBRARIES(test_cov_Algorithms_Output lib_computation)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Extrapolate test/TestAlgorithms_Extrapolate.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Extrapolate.h)
	AddTestProperty(test_cov_Algorithms_Extrapolate)

	add_executable(test_cov_JetDEau_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic.cpp)
	AddTestProperty(test_cov_JetDEau_Basic)
	TARGET_LINK_LIBRARIES(test_cov_JetDEau_Basic lib_computation)
	add_test(NAME test_JetDEau_Basic COMMAND test_cov_JetDEau_Basic)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Convection test/TestAlgorithms_Convection.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Convection.h)
	AddTestProperty(test_cov_Algorithms_Convection)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air_Solid_Inflow test/TestData_CellType_Fluid_Air_Solid_Inflow.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air_Solid_Inflow.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air_Solid_Inflow)

	add_executable(test_cov_FillingContainer_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer_Basic.cpp)
	AddTestProperty(test_cov_FillingContainer_Basic)
	TARGET_LINK_LIBRARIES(test_cov_FillingContainer_Basic lib_computation)
	add_test(NAME test_cov_FillingContainer_Basic COMMAND TestFillingContainer_Basic)
endif(USE_TESTING)
