cmake_minimum_required (VERSION 2.6)

project(Algorithms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE TldAlgorithm.cpp)

add_library(${PROJECT_NAME} ${SOURCE})

add_subdirectory(unittests)

