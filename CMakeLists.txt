cmake_minimum_required(VERSION 2.8)
project(MAC CXX)

include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/src" )

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

option (USE_LUSOL "Use LUSOL Fortran code" on)

option (USE_TEST_COMPILER_FLAG "Use Test Compiler Flag" on)

option (USE_PYTHON "Use Python" on)

include(CheckCXXCompilerFlag)
if (USE_TESTING)
 ENABLE_TESTING()
endif (USE_TESTING)

if(USE_LUSOL)
	enable_language(C)
	enable_language(Fortran)
	include(FortranCInterface)
	find_package( BLAS REQUIRED )
	FortranCInterface_VERIFY( CXX)
	FortranCInterface_HEADER(lusol_int.h SYMBOLS "lu1fac" "lu6sol" "lu8adc" "lu8adr" "lu8dlc" "lu8dlr" "lu8rpc" "lu8rpr" "testtest")
	add_library(lib_lusol src/lusol.f)
	target_link_libraries(lib_lusol ${BLAS_LIBRARIES})
	set_target_properties(lib_lusol PROPERTIES LINK_FLAGS "${BLAS_LINKER_FLAGS}")
endif(USE_LUSOL)

if(USE_PYTHON)
	find_package(Boost 1.50 COMPONENTS python REQUIRED)

	link_directories ( ${Boost_LIBRARY_DIRS} )
	set(Python_ADDITIONAL_VERSIONS 2.7)
	find_package(PythonLibs REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	include_directories(${PYTHON_INCLUDE_DIRS})
	include_directories(/usr/lib/python2.7/site-packages/numpy/core/include)
endif(USE_PYTHON)


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
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc/"
DEPENDS docqt)

add_custom_target(docqt COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/qtdoc/")
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
	set(COMPUTATION_COMPILE_FLAGS "${COMPUTATION_COMPILE_FLAGS} -Wextra -Wunsafe-loop-optimizations -Wdisabled-optimization -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wno-unused-parameter -funsafe-loop-optimizations -Wstrict-overflow=5 -Wtrampolines -Wcast-qual -Wcast-align -Wvector-operation-performance -Wdisabled-optimization ")
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
file(GLOB_RECURSE header_file src/*.tpp src/*.h test/*.tpp test/*.h)
add_library(lib_computation STATIC ${header_file})
set_target_properties(lib_computation PROPERTIES LINKER_LANGUAGE "CXX")
TARGET_LINK_LIBRARIES(lib_computation vtkHybrid ${Boost_LIBRARIES})

if(USE_UMFPACK)
	TARGET_LINK_LIBRARIES(lib_computation -lumfpack -lsuitesparseconfig -lrt -lamd -lcholmod -lcolamd -lblas -llapack)
endif(USE_UMFPACK)

if(USE_LUSOL)
	TARGET_LINK_LIBRARIES(lib_computation lib_lusol)
endif(USE_LUSOL)

if(USE_GOOGLE_PERF)
	TARGET_LINK_LIBRARIES(lib_computation -lprofiler)
endif(USE_GOOGLE_PERF)

if(USE_PYTHON)
	TARGET_LINK_LIBRARIES(lib_computation ${Boost_LIBRARIES} ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})
endif(USE_PYTHON)

if(USE_TEST_COMPILER_FLAG)
	set(COMPILER_FLAG "${COMPILER_NO_OPTIMISATION_FLAG} ${COMPILER_COVERAGE_FLAG}  ${CPP11_FLAG} -Wall -Wextra -Wstrict-aliasing=1 -fno-strict-aliasing")
endif(USE_TEST_COMPILER_FLAG)

#TARGET_LINK_LIBRARIES(computation lib_computation)
#install (TARGETS computation DESTINATION bin)


#add_executable(Diffusion_Jet ${CMAKE_CURRENT_SOURCE_DIR}/src/mainDiffusion.cpp)
#set_target_properties(Diffusion_Jet PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Diffusion_Jet lib_computation)


#add_executable(Container_Filling ${CMAKE_CURRENT_SOURCE_DIR}/src/Container_Filling.cpp)
#set_target_properties(Container_Filling PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Container_Filling lib_computation)

add_executable(Lateral_Jet ${CMAKE_CURRENT_SOURCE_DIR}/test/Lateral_jet.cpp)
set_target_properties(Lateral_Jet PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Lateral_Jet lib_computation)

add_executable(Lateral_Jet_3 ${CMAKE_CURRENT_SOURCE_DIR}/test/Lateral_jet_3.cpp)
set_target_properties(Lateral_Jet_3 PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Lateral_Jet_3 lib_computation)

add_executable(Jet ${CMAKE_CURRENT_SOURCE_DIR}/test/Jet.cpp)
set_target_properties(Jet PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Jet lib_computation)

add_executable(Jet3 ${CMAKE_CURRENT_SOURCE_DIR}/test/Jet3.cpp)
set_target_properties(Jet3 PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Jet3 lib_computation)

add_executable(test_lusol ${CMAKE_CURRENT_SOURCE_DIR}/test/test_lusol.cpp)
set_target_properties(test_lusol PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(test_lusol lib_computation)

add_executable(JetDEau_Basic_2_Depth ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Depth.cpp)
set_target_properties(JetDEau_Basic_2_Depth PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(JetDEau_Basic_2_Depth lib_computation)

add_executable(JetDEau_Basic_2_Updating ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Updating.cpp)
set_target_properties(JetDEau_Basic_2_Updating PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(JetDEau_Basic_2_Updating lib_computation)

add_executable(JetDEau_Basic_2_Pyamg ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Pyamg.cpp)
set_target_properties(JetDEau_Basic_2_Pyamg PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(JetDEau_Basic_2_Pyamg lib_computation)

add_executable(JetDEau_Basic_2_Pyamg_Simplified ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Pyamg_Simplified.cpp)
set_target_properties(JetDEau_Basic_2_Pyamg_Simplified PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(JetDEau_Basic_2_Pyamg_Simplified lib_computation)

#add_executable(FillingContainer2D_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer2D_Basic.cpp)
#set_target_properties(FillingContainer2D_Basic PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(FillingContainer2D_Basic lib_computation)

add_executable(Pool_Lin_Speed_2d ${CMAKE_CURRENT_SOURCE_DIR}/test/Pool_Lin_Speed_2d.cpp)
set_target_properties(Pool_Lin_Speed_2d PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Pool_Lin_Speed_2d lib_computation)


add_executable(solheat_2d ${CMAKE_CURRENT_SOURCE_DIR}/test/SolHeat_2d.cpp)
set_target_properties(solheat_2d PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(solheat_2d lib_computation)

add_executable(Irrotational_Flow ${CMAKE_CURRENT_SOURCE_DIR}/test/Irrotational_Flow.cpp)
set_target_properties(Irrotational_Flow PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Irrotational_Flow lib_computation)

add_executable(Vortex ${CMAKE_CURRENT_SOURCE_DIR}/test/Vortex.cpp)
set_target_properties(Vortex PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Vortex lib_computation)

add_executable(Pool_Constant_Speed_2d ${CMAKE_CURRENT_SOURCE_DIR}/test/Pool_Constant_Speed_2d.cpp)
set_target_properties(Pool_Constant_Speed_2d PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Pool_Constant_Speed_2d lib_computation)

#add_executable(FillingContainer_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer_Basic.cpp)
#set_target_properties(FillingContainer_Basic PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(FillingContainer_Basic lib_computation)

#add_executable(FillingContainer_Basic_Pyamg ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer_Basic_Pyamg.cpp)
#set_target_properties(FillingContainer_Basic_Pyamg PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(FillingContainer_Basic_Pyamg lib_computation)

add_executable(JetDEau_Basic_2 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2.cpp)
set_target_properties(JetDEau_Basic_2 PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(JetDEau_Basic_2 lib_computation)

#add_executable(JetDEau_Basic_3 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_3.cpp)
#set_target_properties(JetDEau_Basic_3 PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(JetDEau_Basic_3 lib_computation)

#add_executable(Performance ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPerformance_Without_Particle.cpp)
#set_target_properties(Performance PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Performance lib_computation)

add_executable(Convection ${CMAKE_CURRENT_SOURCE_DIR}/test/TestConvection.cpp)
set_target_properties(Convection PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Convection lib_computation)

#add_executable(Chunk_Hash_Table_Performance ${CMAKE_CURRENT_SOURCE_DIR}/test/TestChunk_Hash_Table_Performance.cpp)
#set_target_properties(Chunk_Hash_Table_Performance PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
#TARGET_LINK_LIBRARIES(Chunk_Hash_Table_Performance lib_computation)

add_executable(Gravity ${CMAKE_CURRENT_SOURCE_DIR}/test/TestGravity.cpp)
set_target_properties(Gravity PROPERTIES COMPILE_FLAGS ${COMPUTATION_COMPILE_FLAGS} LINK_FLAGS ${COMPUTATION_LINK_FLAGS})
TARGET_LINK_LIBRARIES(Gravity lib_computation)

if (USE_TESTING)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/test)


function(AddTestProperty target)
	set(COMPILER_FLAG "${COMPILER_NO_OPTIMISATION_FLAG} ${COMPILER_COVERAGE_FLAG}  ${CPP11_FLAG} -Wall -Wextra -Wstrict-aliasing=1 -fno-strict-aliasing ")
	set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMPILER_FLAG} LINK_FLAGS ${COMPILER_FLAG})
	Target_link_libraries(${target}  ${Boost_LIBRARIES})
	Target_link_libraries(${target} lib_computation)
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

#	CXXTEST_ADD_TEST(test_cov_Data_Grid test/TestData_Grid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid.h)
#	AddTestProperty(test_cov_Data_Grid)

	CXXTEST_ADD_TEST(test_cov_Data_Pressure_Data test/TestData_Pressure_Data.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Pressure_Data.h)
	AddTestProperty(test_cov_Data_Pressure_Data)

	CXXTEST_ADD_TEST(test_cov_Data_Speed_Data test/TestData_Speed_Data.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Speed_Data.h)
	AddTestProperty(test_cov_Data_Speed_Data)

#	CXXTEST_ADD_TEST(test_cov_Data_Grid_MacCell test/TestData_Grid_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_MacCell.h)
#	AddTestProperty(test_cov_Data_Grid_MacCell)

#	CXXTEST_ADD_TEST(test_cov_Data_Grid_Speed test/TestData_Grid_Speed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_Speed.h)
#	AddTestProperty(test_cov_Data_Grid_Speed)

	CXXTEST_ADD_TEST(test_cov_Data_Grid_Pressure test/TestData_Grid_Pressure.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Grid_Pressure.h)
	AddTestProperty(test_cov_Data_Grid_Pressure)

	CXXTEST_ADD_TEST(test_cov_Data_Neighbour_List test/TestData_Neighbour_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Neighbour_List.h)
	AddTestProperty(test_cov_Data_Neighbour_List)

	CXXTEST_ADD_TEST(test_cov_Data_Hookable_Hash_Table test/TestHookable_Hash_Table.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestHookable_Hash_Table.h)
	AddTestProperty(test_cov_Data_Hookable_Hash_Table)

	CXXTEST_ADD_TEST(test_cov_Data_Hook_Neighbour_List test/TestData_Hook_Neighbour_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Hook_Neighbour_List.h)
	AddTestProperty(test_cov_Data_Hook_Neighbour_List)

        #CXXTEST_ADD_TEST(test_cov_Data_Hook_Neighbour_List_Key test/TestData_Hook_Neighbour_List_Key.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Hook_Neighbour_List_Key.h)
        #AddTestProperty(test_cov_Data_Hook_Neighbour_List_Key)

#	CXXTEST_ADD_TEST(test_cov_Data_Interface_Fluid_Air test/TestData_Interface_Fluid_Air.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Interface_Fluid_Air.h)
#	AddTestProperty(test_cov_Data_Interface_Fluid_Air)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Domain_Fluid test/Test_Data_CellType_Domain_Fluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Data_CellType_Domain_Fluid.h)
	AddTestProperty(test_cov_Data_CellType_Domain_Fluid)

#	CXXTEST_ADD_TEST(test_cov_Data_Interface_Domain_Rho_Fluid test/TestData_Interface_Domain_Rho_Fluid.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Interface_Domain_Rho_Fluid.h)
#	AddTestProperty(test_cov_Data_Interface_Domain_Rho_Fluid)

#	CXXTEST_ADD_TEST(test_cov_Data_CellType_Interface_Constant test/Test_Data_CellType_Interface_Constant.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Data_CellType_Interface_Constant.h)
#	AddTestProperty(test_cov_Data_CellType_Interface_Constant)

	CXXTEST_ADD_TEST(test_cov_Data_Particles_List test/TestData_Particles_List.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Particles_List.h)
	AddTestProperty(test_cov_Data_Particles_List)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Initialize_MacCell test/TestAlgorithm_Initialize_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Initialize_MacCell.h)
	AddTestProperty(test_cov_Algorithm_Initialize_MacCell)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Delete_MacCell test/TestAlgorithm_Delete_MacCell.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Delete_MacCell.h)
	AddTestProperty(test_cov_Algorithm_Delete_MacCell)

	CXXTEST_ADD_TEST(test_cov_Algorithm_Layer_Initial_With_Particle test/TestAlgorithm_Layer_Initial_With_Particle.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Layer_Initial_With_Particle.h)
	AddTestProperty(test_cov_Algorithm_Layer_Initial_With_Particle)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Create_Fluid_Particle test/TestAlgorithms_Create_Fluid_Particle.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Create_Fluid_Particle.h)
#	AddTestProperty(test_cov_Algorithms_Create_Fluid_Particle)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Update_CellType_Layer test/TestAlgorithms_Update_CellType_Layer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Update_CellType_Layer.h)
	AddTestProperty(test_cov_Algorithms_Update_CellType_Layer)

#	CXXTEST_ADD_TEST(test_cov_Algorithm_Speed_Constant_Mirror test/TestAlgorithm_Speed_Constant_Mirror.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Speed_Constant_Mirror.h)
#	AddTestProperty(test_cov_Algorithm_Speed_Constant_Mirror)

#	CXXTEST_ADD_TEST(test_cov_Algorithm_Calculate_Time_Step test/TestAlgorithm_Calculate_Time_Step.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Calculate_Time_Step.h)
#	AddTestProperty(test_cov_Algorithm_Calculate_Time_Step)

#	CXXTEST_ADD_TEST(test_cov_Policy_Speed_Interpolation_Linear test/TestPolicy_Speed_Interpolation_Linear.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Speed_Interpolation_Linear.h)
#	AddTestProperty(test_cov_Policy_Speed_Interpolation_Linear)

#	CXXTEST_ADD_TEST(test_cov_Policy_Upwind_1_Order test/TestPolicy_Upwind_1_Order.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Upwind_1_Order.h)
#	AddTestProperty(test_cov_Policy_Upwind_1_Order)

#	CXXTEST_ADD_TEST(test_cov_Policy_Laplacian_Speed test/TestPolicy_Laplacian_Speed.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Laplacian_Speed.h)
#	AddTestProperty(test_cov_Policy_Laplacian_Speed)

#	CXXTEST_ADD_TEST(test_cov_Policy_Divergence test/TestPolicy_Divergence.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Divergence.h)
#	AddTestProperty(test_cov_Policy_Divergence)

#	CXXTEST_ADD_TEST(test_cov_Policy_Gradiant test/TestPolicy_Gradiant.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Gradiant.h)
#	AddTestProperty(test_cov_Policy_Gradiant)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Gravity test/TestAlgorithms_Gravity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Gravity.h)
#	AddTestProperty(test_cov_Algorithms_Gravity)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Viscosity test/TestAlgorithms_Viscosity.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Viscosity.h)
#	AddTestProperty(test_cov_Algorithms_Viscosity)

#	CXXTEST_ADD_TEST(test_cov_Policy_Solve_Linear_Umfpack test/TestPolicy_Solve_Linear_Umfpack.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Solve_Linear_Umfpack.h)
#	AddTestProperty(test_cov_Policy_Solve_Linear_Umfpack)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Solve_Pressure test/TestAlgorithms_Solve_Pressure.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Solve_Pressure.h)
#	AddTestProperty(test_cov_Algorithms_Solve_Pressure)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Move_Particles test/TestAlgorithms_Move_Particles.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Move_Particles.h)
#	AddTestProperty(test_cov_Algorithms_Move_Particles)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Output test/TestAlgorithms_Output.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Output.h)
#	AddTestProperty(test_cov_Algorithms_Output)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Extrapolate test/TestAlgorithms_Extrapolate.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Extrapolate.h)
#	AddTestProperty(test_cov_Algorithms_Extrapolate)

	add_executable(test_cov_JetDEau_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic.cpp)
	AddTestProperty(test_cov_JetDEau_Basic)
        #add_test(NAME test_JetDEau_Basic COMMAND test_cov_JetDEau_Basic)

#	CXXTEST_ADD_TEST(test_cov_Algorithms_Convection test/TestAlgorithms_Convection.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithms_Convection.h)
#	AddTestProperty(test_cov_Algorithms_Convection)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air_Solid_Inflow test/TestData_CellType_Fluid_Air_Solid_Inflow.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air_Solid_Inflow.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air_Solid_Inflow)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_0_Pres test/TestData_CellType_Fluid_Air_Solid_Inflow_0_Pres.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air_Solid_Inflow_0_Pres.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_0_Pres)

#	add_executable(test_cov_FillingContainer_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer_Basic.cpp)
#	AddTestProperty(test_cov_FillingContainer_Basic)
#	add_test(NAME test_cov_FillingContainer_Basic COMMAND test_cov_FillingContainer_Basic)

#	add_executable(test_cov_FillingContainer_Basic_Pyamg ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer_Basic_Pyamg.cpp)
#	AddTestProperty(test_cov_FillingContainer_Basic_Pyamg)
#	add_test(NAME test_cov_FillingContainer_Basic_Pyamg COMMAND test_cov_FillingContainer_Basic_Pyamg)

	#add_executable(test_cov_FillingContainer2D_Basic ${CMAKE_CURRENT_SOURCE_DIR}/test/TestFillingContainer2D_Basic.cpp)
	#AddTestProperty(test_cov_FillingContainer2D_Basic)
	#add_test(NAME test_cov_FillingContainer2D_Basic COMMAND test_cov_FillingContainer2D_Basic)

	add_executable(test_cov_Convection ${CMAKE_CURRENT_SOURCE_DIR}/test/TestConvection.cpp)
	AddTestProperty(test_cov_Convection)
        #add_test(NAME test_cov_Convection COMMAND test_cov_Convection)

#	add_executable(test_cov_ConvectionDiag ${CMAKE_CURRENT_SOURCE_DIR}/test/TestConvectionDiag.cpp)
#	AddTestProperty(test_cov_ConvectionDiag)
#	add_test(NAME test_cov_ConvectionDiag COMMAND test_cov_ConvectionDiag)

#	add_executable(test_cov_ConvectionDiagCenter ${CMAKE_CURRENT_SOURCE_DIR}/test/TestConvectionDiagCenter.cpp)
#	AddTestProperty(test_cov_ConvectionDiagCenter)
#	add_test(NAME test_cov_ConvectionDiagCenter COMMAND test_cov_ConvectionDiagCenter)

#	CXXTEST_ADD_TEST(test_cov_Policy_Speed_Interpolation_Linear_Symmetric test/TestPolicy_Speed_Interpolation_Linear_Symmetric.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPolicy_Speed_Interpolation_Linear_Symmetric.h)
#	AddTestProperty(test_cov_Policy_Speed_Interpolation_Linear_Symmetric)

	add_executable(test_cov_JetDEau_Basic_2 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2.cpp)
	AddTestProperty(test_cov_JetDEau_Basic_2)
        #add_test(NAME test_JetDEau_Basic_2 COMMAND test_cov_JetDEau_Basic_2)

#	add_executable(test_cov_JetDEau_Basic_3 ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_3.cpp)
#	AddTestProperty(test_cov_JetDEau_Basic_3)
#	TARGET_LINK_LIBRARIES(test_cov_JetDEau_Basic_3 lib_computation)
#	add_test(NAME test_JetDEau_Basic_3 COMMAND test_cov_JetDEau_Basic_3)

	CXXTEST_ADD_TEST(test_cov_Data_Neighbour_List_Empty test/TestData_Neighbour_List_Empty.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Neighbour_List_Empty.h)
	AddTestProperty(test_cov_Data_Neighbour_List_Empty)

#	CXXTEST_ADD_TEST(test_cov_Data_Chunk test/TestData_Chunk.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_Chunk.h)
#	AddTestProperty(test_cov_Data_Chunk)

#	add_executable(test_cov_TestPerformance_Without_Particle ${CMAKE_CURRENT_SOURCE_DIR}/test/TestPerformance_Without_Particle.cpp)
#	AddTestProperty(test_cov_TestPerformance_Without_Particle)
#	add_test(NAME test_TestPerformance_Without_Particle COMMAND test_cov_TestPerformance_Without_Particle)

	CXXTEST_ADD_TEST(test_cov_Offset test/Test_Offset.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Offset.h)
	AddTestProperty(test_cov_Offset)

	CXXTEST_ADD_TEST(test_cov_Offset_Base test/Test_Offset_Base.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Offset_Base.h)
	AddTestProperty(test_cov_Offset_Base)

        CXXTEST_ADD_TEST(test_cov_ChunkHashTable test/TestChunkHashTable.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestChunkHashTable.h)
        AddTestProperty(test_cov_ChunkHashTable)

	#add_executable(test_cov_TestChunk_Hash_Table_Performance ${CMAKE_CURRENT_SOURCE_DIR}/test/TestChunk_Hash_Table_Performance.cpp)
	#AddTestProperty(test_cov_TestChunk_Hash_Table_Performance)
	#add_test(NAME test_cov_TestChunk_Hash_Table_Performance COMMAND test_cov_TestChunk_Hash_Table_Performance)

#	CXXTEST_ADD_TEST(test_cov_MacCell2 test/Test_MacCell2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_MacCell2.h)
#	AddTestProperty(test_cov_MacCell2)

#	CXXTEST_ADD_TEST(test_cov_Algorithm_Apply_Wind test/TestAlgorithm_Apply_Wind.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestAlgorithm_Apply_Wind.h)
#	AddTestProperty(test_cov_Algorithm_Apply_Wind)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_Interior test/TestData_CellType_Fluid_Air_Solid_Inflow_Interior.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air_Solid_Inflow_Interior.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_Interior)

	CXXTEST_ADD_TEST(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres test/TestData_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/TestData_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres.h)
	AddTestProperty(test_cov_Data_CellType_Fluid_Air_Solid_Inflow_Interior_0_Pres)

	add_executable(test_cov_JetDEau_Basic_2_Depth ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Depth.cpp)
	AddTestProperty(test_cov_JetDEau_Basic_2_Depth)
        #add_test(NAME test_JetDEau_Basic_2_Depth COMMAND test_cov_JetDEau_Basic_2_Depth)

	add_executable(test_cov_JetDEau_Basic_2_Updating ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Updating.cpp)
	AddTestProperty(test_cov_JetDEau_Basic_2_Updating)
        #add_test(NAME test_JetDEau_Basic_2_Updating COMMAND test_cov_JetDEau_Basic_2_Updating)


	add_executable(test_cov_JetDEau_Basic_2_Pyamg ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Pyamg.cpp)
	AddTestProperty(test_cov_JetDEau_Basic_2_Pyamg)
        #add_test(NAME test_JetDEau_Basic_2_Pyamg COMMAND test_cov_JetDEau_Basic_2_Pyamg)

	add_executable(test_cov_JetDEau_Basic_2_Pyamg_Simplified ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJetDEau_Basic_2_Pyamg_Simplified.cpp)
	AddTestProperty(test_cov_JetDEau_Basic_2_Pyamg_Simplified)
        #add_test(NAME test_JetDEau_Basic_2_Pyamg_Simplified COMMAND test_cov_JetDEau_Basic_2_Pyamg_Simplified)

	add_executable(test_cov_Gravity ${CMAKE_CURRENT_SOURCE_DIR}/test/TestGravity.cpp)
	AddTestProperty(test_cov_Gravity)
        #add_test(NAME test_Gravity COMMAND test_cov_Gravity)

	add_executable(test_cov_Update_Pressure ${CMAKE_CURRENT_SOURCE_DIR}/test/TestUpdate_Pressure.cpp)
	AddTestProperty(test_cov_Update_Pressure)
	add_test(NAME test_Update_Pressure COMMAND test_cov_Update_Pressure)

	CXXTEST_ADD_TEST(test_cov_Algorithms_Solve_Pressure_Neumann_Var test/Test_Algorithms_Solve_Pressure_Neumann_Var.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/Test_Algorithms_Solve_Pressure_Neumann_Var.h)
	AddTestProperty(test_cov_Algorithms_Solve_Pressure_Neumann_Var)

        CXXTEST_ADD_TEST(test_cov_extrapolate_boundary test/Test_Extrapolate_Boundary.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/test_Extrapolate_Boundary.h)
        AddTestProperty(test_cov_extrapolate_boundary)

        add_executable(test_cov_Single_Particle ${CMAKE_CURRENT_SOURCE_DIR}/test/Single_Particle.cpp)
        AddTestProperty(test_cov_Single_Particle)
        #add_test(NAME test_single_particle COMMAND test_cov_Single_Particle)

        add_executable(test_cov_Lateral_Jet ${CMAKE_CURRENT_SOURCE_DIR}/test/Lateral_jet.cpp)
        AddTestProperty(test_cov_Lateral_Jet)
        #add_test(NAME test_lateral_jet COMMAND test_cov_Lateral_Jet)

endif(USE_TESTING)
