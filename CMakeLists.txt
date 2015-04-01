cmake_minimum_required (VERSION 2.6)

project(ObjectTracking)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(OpenCV)


add_executable(Main main.cpp)

target_link_libraries(Main OpenCV)

