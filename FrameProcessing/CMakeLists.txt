cmake_minimum_required (VERSION 2.6)

project(FrameProcessing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE ImageMarker.cpp ImageTransform.cpp VideoLoader.cpp State.cpp TransformContainer.cpp)

add_library(${PROJECT_NAME} ${SOURCE})

