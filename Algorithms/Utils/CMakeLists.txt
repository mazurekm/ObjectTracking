cmake_minimum_required (VERSION 2.6)

project(Utils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} NNMatcher.cpp State.cpp MeasuredData.cpp PointContainer.cpp)


find_package (Boost COMPONENTS filesystem REQUIRED)

target_link_libraries (${PROJECT_NAME} ${BOOST_FILESYSTEM_LIBRARY})
