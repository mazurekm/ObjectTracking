cmake_minimum_required (VERSION 2.6)

project(OpenTLD)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libconfig)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cvblobs)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libopentld)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} libconfig)
target_link_libraries(${PROJECT_NAME} libopentld)
