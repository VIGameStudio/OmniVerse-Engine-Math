cmake_minimum_required(VERSION 3.2)

project(OVE_Math)
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_REVISION_VERSION 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_subdirectory(extern)
include_directories(src)

add_library(ove_math INTERFACE)
target_include_directories(ove_math INTERFACE src ${OVE_CORE_INCLUDE_DIR})

add_executable(math_demo demo/main.cpp)
target_link_libraries(math_demo ove_math ove_core)

enable_testing()

add_executable(vec_test test/vector_test.cpp)
add_test(Vec_test vector_test)
target_link_libraries(vec_test ove_math ove_core)