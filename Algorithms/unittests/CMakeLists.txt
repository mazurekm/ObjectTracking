cmake_minimum_required (VERSION 2.6) 

project(algorithms_unittest)

set( EXECUTABLE_OUTPUT_PATH ${TEST_DIR} )

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (${ALG_TEST} algorithms_unittests.cpp)


target_link_libraries (${ALG_TEST}
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_SYSTEM_LIBRARY}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

target_link_libraries(${ALG_TEST} Algorithms)
target_link_libraries(${ALG_TEST} FrameProcessing)
target_link_libraries(${ALG_TEST} OpenCV)
