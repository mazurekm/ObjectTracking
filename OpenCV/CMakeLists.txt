cmake_minimum_required (VERSION 2.8)

project (OpenCV)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(OpenCV link.cpp)

target_link_libraries(OpenCV libopencv_core.so)
target_link_libraries(OpenCV libopencv_highgui.so)
target_link_libraries(OpenCV libopencv_imgproc.so)
