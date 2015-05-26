cmake_minimum_required (VERSION 2.6)

project(Algorithms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Utils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tld)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tld)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Feature)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Feature)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Kalman)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Kalman)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/OptFlow)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/OptFlow)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} Tld)
target_link_libraries(${PROJECT_NAME} Feature)
target_link_libraries(${PROJECT_NAME} Kalman)
target_link_libraries(${PROJECT_NAME} OptFlow)
