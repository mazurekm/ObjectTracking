cmake_minimum_required (VERSION 2.6)

project(OptFlow)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE OpticalFlow.cpp)

add_library(${PROJECT_NAME} ${SOURCE})


target_link_libraries(${PROJECT_NAME} Utils)

add_subdirectory(unittests)

