cmake_minimum_required (VERSION 2.6)

project(Algorithms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tld)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tld)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Feature)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Feature)

add_library(${PROJECT_NAME} link.cpp)
target_link_libraries(${PROJECT_NAME} Tld)
target_link_libraries(${PROJECT_NAME} Feature)
