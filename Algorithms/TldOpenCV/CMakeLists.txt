cmake_minimum_required (VERSION 2.6)

project(TldOpenCV)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE TldOpenCVAlgorithm.cpp)

add_library(${PROJECT_NAME} ${SOURCE})


target_link_libraries(${PROJECT_NAME} Utils)
target_link_libraries(${PROJECT_NAME} FrameProcessing)

add_subdirectory(unittests)

