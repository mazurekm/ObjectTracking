cmake_minimum_required (VERSION 2.6)

project(ObjectTracking)

#option(BOOST "BOOST_LIBRARY" OFF)
option(CPP11 "CPP11 SUPPORT" OFF)


if(CPP11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(OpenCV)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenCV)

#if(BOOST)
#find_package(Boost 1.49.0 COMPONENTS system filesystem unit_test_framework REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}) 
#endif()



