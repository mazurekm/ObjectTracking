cmake_minimum_required (VERSION 2.6)

project(ObjectTracking)

set(TEST_DIR ${PROJECT_BINARY_DIR}/Tests)
set(SAMPLE_DIR ${TEST_DIR}/bin)
set(TLD_TEST tld_test)
set(FEATURE_TEST feature_test)
set(KALMAN_TEST kalman_test)
set(OPTFLOW_TEST optflow_test)

option(CPP11 "CPP11 SUPPORT" ON)

if(CPP11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/OpenCV/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/OpenTLD/libopentld)

add_subdirectory(OpenCV)
add_subdirectory(OpenTLD)
add_subdirectory(FrameProcessing)
add_subdirectory(Algorithms)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenCV)
target_link_libraries(${PROJECT_NAME} OpenTLD)
target_link_libraries(${PROJECT_NAME} FrameProcessing)
target_link_libraries(${PROJECT_NAME} Algorithms)

enable_testing()
add_test(${TLD_TEST} ${TEST_DIR}/${TLD_TEST})
add_test(${FEATURE_TEST} ${TEST_DIR}/${FEATURE_TEST})
add_test(${KALMAN_TEST} ${TEST_DIR}/${KALMAN_TEST})
add_test(${OPTFLOW_TEST} ${TEST_DIR}/${OPTFLOW_TEST})


file(GLOB Data ${CMAKE_CURRENT_SOURCE_DIR}/samples/*)

file(COPY ${Data} DESTINATION ${SAMPLE_DIR})
