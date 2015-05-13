cmake_minimum_required (VERSION 2.6)

project(Feature)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE FeatureDetect.cpp)

add_library(${PROJECT_NAME} ${SOURCE})

add_subdirectory(unittests)

