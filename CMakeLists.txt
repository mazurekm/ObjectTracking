cmake_minimum_required (VERSION 2.6)

project(ObjectTracking)

set(TEST_DIR ${PROJECT_BINARY_DIR}/Tests)
set(ALG_TEST alg_test)

option(CPP11 "CPP11 SUPPORT" ON)

if(CPP11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/OpenCV/include)

add_subdirectory(OpenCV)
add_subdirectory(FrameProcessing)
add_subdirectory(Algorithms)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenCV)
target_link_libraries(${PROJECT_NAME} FrameProcessing)
target_link_libraries(${PROJECT_NAME} Algorithms)

enable_testing()
add_test(${ALG_TEST} ${TEST_DIR}/${ALG_TEST})
