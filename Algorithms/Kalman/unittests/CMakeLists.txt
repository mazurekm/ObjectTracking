cmake_minimum_required (VERSION 2.6) 

project(kalman_unittest)

set( EXECUTABLE_OUTPUT_PATH ${TEST_DIR} )

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (${KALMAN_TEST} kalman_unittests.cpp)

target_link_libraries (${KALMAN_TEST}
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_SYSTEM_LIBRARY}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )


target_link_libraries(${KALMAN_TEST} Kalman)
target_link_libraries(${KALMAN_TEST} FrameProcessing)
target_link_libraries(${KALMAN_TEST} OpenCV)
