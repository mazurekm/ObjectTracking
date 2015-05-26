cmake_minimum_required (VERSION 2.6)

project(Utils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} NNMatcher.cpp)

