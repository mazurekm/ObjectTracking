cmake_minimum_required (VERSION 2.8)

project (OpenTLD)

file(GLOB binaries ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(OpenTLD link.cpp)

target_link_libraries(OpenTLD ${binaries})
