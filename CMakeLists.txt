cmake_minimum_required (VERSION 2.6)

project(ObjectTracking)

option(BOOST "BOOST_LIBRARY" OFF)
option(CPP11 "CPP11 SUPPORT" ON)


if(CPP11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(OpenCV)
add_subdirectory(FrameProcessing)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenCV)
target_link_libraries(${PROJECT_NAME} FrameProcessing)

if(BOOST)
		find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
	include_directories(${Boost_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}) 
endif()



